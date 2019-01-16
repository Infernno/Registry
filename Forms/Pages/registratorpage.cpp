#include "registratorpage.hpp"
#include "ui_registratorpage.h"

#include <QDebug>
#include <QMessageBox>

#include "Core/utils.h"
#include "Core/Data/database.hpp"
#include "Core/Managers/usermanager.h"

#include "Forms/Dialogs/addeditpatient.hpp"
#include "Forms/Dialogs/addeditappointment.hpp"

RegistratorPage::RegistratorPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistratorPage)
{
    ui->setupUi(this);

    initialize();
    refresh();
}

RegistratorPage::~RegistratorPage()
{
    delete ui;
}

void RegistratorPage::initialize()
{
    mAppointments = Database::Instance()->appointmentTable();
    mPatients = Database::Instance()->patientTable();

    Utils::InitializeTable(ui->PatientTableWidget, QStringList() << "Имя пользователя" << "Пароль" << "ФИО" << "Дата рождения" << "Адрес" << "Лечащий врач");
    Utils::InitializeTable(ui->AppointmentsTableWidget, QStringList() << "Пациент" << "Врач" << "Время");
}

void RegistratorPage::refresh()
{
    Utils::ClearTable(ui->PatientTableWidget);
    Utils::ClearTable(ui->AppointmentsTableWidget);

    TableData patients;
    TableData appointments;

    for(const Patient & item : mPatients->all())
    {
        TableRow row;

        row.push_back(new QTableWidgetItem(item.Username));
        row.push_back(new QTableWidgetItem(item.PasswordHash));
        row.push_back(new QTableWidgetItem(item.getFullName()));
        row.push_back(new QTableWidgetItem(item.Birthday.toString()));
        row.push_back(new QTableWidgetItem(item.Address));
        row.push_back(new QTableWidgetItem(item.Doctor));

        patients.push_back(row);
    }

    Utils::Update(ui->PatientTableWidget, patients);

    for(const Appointment & appointment : mAppointments->all())
    {
        TableRow row;

        row.push_back(new QTableWidgetItem(appointment.Patient));
        row.push_back(new QTableWidgetItem(appointment.Doctor));
        row.push_back(new QTableWidgetItem(appointment.Date.toString("dd.MM.yyyy HH:mm")));

        appointments.push_back(row);
    }

    Utils::Update(ui->AppointmentsTableWidget, appointments);
}

void RegistratorPage::addPatientButton()
{
    AddEditPatient dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        auto model = dialog.getPatient();

        UserManager::AddOrUpdate(model, true);

        refresh();
    }
}

void RegistratorPage::editPatientButton()
{
    auto selection = ui->PatientTableWidget->selectionModel();

    if(selection->hasSelection())
    {
        int row = selection->currentIndex().row();
        int column = 0;

        auto username = ui->PatientTableWidget->item(row, column)->text();
        auto user = mPatients->find([&username](const auto & item) { return item.Username == username;});

        qDebug() << "Editing: " << user->Username;

        AddEditPatient dialog;

        dialog.setData(*user);

        if(dialog.exec() == QDialog::Accepted)
        {
            auto model = dialog.getPatient();

            UserManager::AddOrUpdate(model);

            refresh();
        }
    }
}

void RegistratorPage::removePatientButton()
{
    auto selection = ui->PatientTableWidget->selectionModel();

    if(selection->hasSelection())
    {
        int row = selection->currentIndex().row();
        int column = 0;

        auto username = ui->PatientTableWidget->item(row, column)->text();

        qDebug() << "Remove: " << username;

        UserManager::RemoveUser(username);

        refresh();
    }
}

void RegistratorPage::addAppointmentButton()
{
    AddEditAppointment dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        auto data = dialog.getData();

        if(mAppointments->contains(data))
        {
            QMessageBox::warning(this, "Ошибка", "Такой талон уже существует!");
        }
        else
        {
            mAppointments->addAuto(data);
            refresh();
        }
    }
}

void RegistratorPage::removeAppointmentButton()
{
    auto selection = ui->AppointmentsTableWidget->selectionModel();

    if(selection->hasSelection() && mAppointments->size() > 0)
    {
        int row = selection->currentIndex().row();

        auto patient = ui->AppointmentsTableWidget->item(row, 0)->text();
        auto doctor =  ui->AppointmentsTableWidget->item(row, 1)->text();
        auto time =  ui->AppointmentsTableWidget->item(row, 2)->text();

        Appointment appointment;

        appointment.Patient = patient;
        appointment.Doctor = doctor;
        appointment.Date = QDateTime::fromString(time, "dd.MM.yyyy HH:mm");

        qDebug() << "Appointment count:" << mAppointments->all().size();

        if(mAppointments->contains(appointment))
        {
            qDebug() << "Found appointment to delete";

            QMessageBox::information(this, "Удалено", "Талон на запись успешно удален!");

            mAppointments->remove(appointment);
            refresh();
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Ошибка при удалении: талон не найден!");
        }
    }
}


