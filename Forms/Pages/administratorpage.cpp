#include "administratorpage.hpp"
#include "ui_administratorpage.h"

#include <QMessageBox>
#include <QCompleter>

#include "Core/utils.h"
#include "Core/Data/database.hpp"
#include "Core/Managers/usermanager.h"

#include "Forms/Dialogs/addeditpatient.hpp"
#include "Forms/Dialogs/addeditregistrator.hpp"
#include "Forms/Dialogs/addeditdoctor.hpp"
#include "Forms/Dialogs/addeditappointment.hpp"
#include "Forms/Dialogs/addeditcardrecord.hpp"

AdministratorPage::AdministratorPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdministratorPage)
{
    ui->setupUi(this);

    initialize();
    refresh();
}

AdministratorPage::~AdministratorPage()
{
    delete ui;
}

void AdministratorPage::on_AddPatientButton_clicked()
{
    AddEditPatient dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        auto model = dialog.getPatient();

        UserManager::AddOrUpdate(model, true);

        refresh();
    }
}

void AdministratorPage::on_EditPatientButton_clicked()
{
    auto selection = ui->PatientTableView->selectionModel();

    if(selection->hasSelection())
    {
        int row = selection->currentIndex().row();
        int column = 0;

        auto username = ui->PatientTableView->item(row, column)->text();
        auto user = Database::Instance()->patientTable()->find([&username](const auto & item) { return item.Username == username;});

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

void AdministratorPage::on_RemovePatientButton_clicked()
{
    auto selection = ui->PatientTableView->selectionModel();

    if(selection->hasSelection())
    {
        int row = selection->currentIndex().row();
        int column = 0;

        auto username = ui->PatientTableView->item(row, column)->text();

        qDebug() << "Remove: " << username;

        UserManager::RemoveUser(username);

        refresh();
    }
}

void AdministratorPage::on_AddRegistratorButton_clicked()
{
    AddEditRegistrator dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        auto model = dialog.getData();

        UserManager::AddOrUpdate(model, true);

        refresh();
    }
}

void AdministratorPage::on_EditRegistratorButton_clicked()
{
    auto selection = ui->RegistratorTableView->selectionModel();

    if(selection->hasSelection())
    {
        int row = selection->currentIndex().row();
        int column = 0;

        auto username = ui->RegistratorTableView->item(row, column)->text();
        auto user = Database::Instance()->registratorTable()->find([&username](const auto & item) { return item.Username == username;});

        qDebug() << "Editing: " << user->Username;

        AddEditRegistrator dialog;

        dialog.setData(*user);

        if(dialog.exec() == QDialog::Accepted)
        {
            auto model = dialog.getData();

            UserManager::AddOrUpdate(model);

            refresh();
        }
    }
}

void AdministratorPage::on_RemoveRegistratorButton_clicked()
{
    auto selection = ui->RegistratorTableView->selectionModel();

    if(selection->hasSelection())
    {
        int row = selection->currentIndex().row();
        int column = 0;

        auto username = ui->RegistratorTableView->item(row, column)->text();

        qDebug() << "Remove: " << username;

        UserManager::RemoveUser(username);

        refresh();
    }
}

void AdministratorPage::on_AddDoctorButton_clicked()
{
    AddEditDoctor dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        auto model = dialog.getData();

        UserManager::AddOrUpdate(model, true);

        refresh();
    }
}

void AdministratorPage::on_EditDoctorButton_clicked()
{
    auto selection = ui->DoctorsTableView->selectionModel();

    if(selection->hasSelection())
    {
        int row = selection->currentIndex().row();
        int column = 0;

        auto username = ui->DoctorsTableView->item(row, column)->text();
        auto user = Database::Instance()->doctorTable()->find([&username](const auto & item) { return item.Username == username;});

        qDebug() << "Editing: " << user->Username;

        AddEditDoctor dialog;

        dialog.setData(*user);

        if(dialog.exec() == QDialog::Accepted)
        {
            auto model = dialog.getData();

            UserManager::AddOrUpdate(model);

            refresh();
        }
    }
}

void AdministratorPage::on_RemoveDoctorButton_clicked()
{
    auto selection = ui->DoctorsTableView->selectionModel();

    if(selection->hasSelection())
    {
        int row = selection->currentIndex().row();
        int column = 0;

        auto username = ui->DoctorsTableView->item(row, column)->text();

        qDebug() << "Remove: " << username;

        UserManager::RemoveUser(username);

        refresh();
    }
}

void AdministratorPage::on_AddAppointmentButton_clicked()
{
    AddEditAppointment dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        auto data = dialog.getData();

        if(Database::Instance()->appointmentTable()->contains(data))
        {
            QMessageBox::warning(this, "Ошибка", "Такой талон уже существует!");
        }
        else
        {
            Database::Instance()->appointmentTable()->addAuto(data);
            refresh();
        }
    }
}

void AdministratorPage::on_RemoveAppointmentButton_clicked()
{
    auto selection = ui->AppointmentTableView->selectionModel();
    auto mAppointments = Database::Instance()->appointmentTable();

    if(selection->hasSelection() && mAppointments->size() > 0)
    {
        int row = selection->currentIndex().row();

        auto patient = ui->AppointmentTableView->item(row, 0)->text();
        auto doctor =  ui->AppointmentTableView->item(row, 1)->text();
        auto time =  ui->AppointmentTableView->item(row, 2)->text();

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

void AdministratorPage::on_FindCardButton_clicked()
{
    auto patientName = ui->PatientFullNameField->text();
    auto mCards = Database::Instance()->medicalCardTable();

    auto patient = Database::Instance()->patientTable()->find([&patientName](const Patient & patient) {
        return patient.getFullName() == patientName;
    });

    if(patient != nullptr)
    {
        int id = patient->ID;
        auto card = mCards->find([&id](const MedicalCard & card) { return card.PatientOwner == id;});

        if(card != nullptr)
        {
            mCurrentCard = card;

            ui->AddCardRecordButton->setEnabled(true);
            ui->RemoveCardRecordButton->setEnabled(true);

            refresh();
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Пациент найден, но его карта не создана!");
        }
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Такой пациент не найден!");
    }
}

void AdministratorPage::on_RemoveCardRecordButton_clicked()
{
    auto selection = ui->CardRecordTableView->selectionModel();

    qDebug() << "Deleting!";

    if(selection->hasSelection())
    {
        int row = selection->currentIndex().row();
        auto dateText = ui->CardRecordTableView->item(row, 2)->text();
        auto date = QDateTime::fromString(dateText);

        qDebug() << "Selected row - " << row;

        for(auto it = mCurrentCard->Records.begin(); it != mCurrentCard->Records.end(); it++)
        {
            if(date.toString() == it->Date.toString())
            {
                mCurrentCard->Records.erase(it);

                QMessageBox::information(this, "Удалено", "Успешно удалено!");

                refresh();

                break;
            }
        }
    }
}

void AdministratorPage::on_AddCardRecordButton_clicked()
{
    AddEditCardRecord addEdit;

    if(addEdit.exec() == QDialog::Accepted)
    {
        auto record = addEdit.getRecord();

        mCurrentCard->Records.push_back(record);

        refresh();
    }
}

void AdministratorPage::initialize()
{
    Utils::InitializeTable(ui->AppointmentTableView, QStringList() << "Пациент" << "Врач" << "Время");
    Utils::InitializeTable(ui->PatientTableView, QStringList() << "Имя пользователя" << "Пароль" << "ФИО" << "Дата рождения" << "Адрес" << "Лечащий врач");
    Utils::InitializeTable(ui->RegistratorTableView, QStringList() << "Имя пользователя" << "Пароль" << "ФИО");
    Utils::InitializeTable(ui->DoctorsTableView, QStringList() << "Имя пользователя" << "Пароль" << "ФИО" << "Специальность" << "Дата найма");
    Utils::InitializeTable(ui->CardRecordTableView, QStringList() << "Симптомы" << "Диагноз" << "Время" << "Врач");

    setAutocomplete();
}

void AdministratorPage::setAutocomplete()
{
    QStringList patientsComplete;

    for(const auto & patient : Database::Instance()->patientTable()->all())
        patientsComplete << patient.getFullName();

    auto patients = new QCompleter(patientsComplete);

    patients->setCaseSensitivity(Qt::CaseInsensitive);
    patients->setCompletionMode(QCompleter::PopupCompletion);

    ui->PatientFullNameField->setCompleter(patients);
}

void AdministratorPage::refresh()
{
    Utils::ClearTable(ui->AppointmentTableView);
    Utils::ClearTable(ui->PatientTableView);
    Utils::ClearTable(ui->RegistratorTableView);
    Utils::ClearTable(ui->DoctorsTableView);
    Utils::ClearTable(ui->CardRecordTableView);

    TableData appointments;
    TableData patients;
    TableData registrators;
    TableData doctors;

    // Appointments
    for(const Appointment & appointment : Database::Instance()->appointmentTable()->all())
    {
        TableRow row;

        row.push_back(new QTableWidgetItem(appointment.Patient));
        row.push_back(new QTableWidgetItem(appointment.Doctor));
        row.push_back(new QTableWidgetItem(appointment.Date.toString("dd.MM.yyyy HH:mm")));

        appointments.push_back(row);
    }

    Utils::Update(ui->AppointmentTableView, appointments);

    // Patients
    for(const auto & item : Database::Instance()->patientTable()->all())
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

    Utils::Update(ui->PatientTableView, patients);


    // Registrators
    for(const auto & item : Database::Instance()->registratorTable()->all())
    {
        TableRow row;

        row.push_back(new QTableWidgetItem(item.Username));
        row.push_back(new QTableWidgetItem(item.PasswordHash));
        row.push_back(new QTableWidgetItem(item.getFullName()));

        registrators.push_back(row);
    }

    Utils::Update(ui->RegistratorTableView, registrators);

    // Doctors
    for(const auto & item : Database::Instance()->doctorTable()->all())
    {
        TableRow row;

        row.push_back(new QTableWidgetItem(item.Username));
        row.push_back(new QTableWidgetItem(item.PasswordHash));
        row.push_back(new QTableWidgetItem(item.getFullName()));
        row.push_back(new QTableWidgetItem(item.Speciality));
        row.push_back(new QTableWidgetItem(item.EmploymentDate.toString()));

        doctors.push_back(row);
    }

    Utils::Update(ui->DoctorsTableView, doctors);

    // Card
    if(mCurrentCard != nullptr)
    {
        TableData cards;

        Utils::ClearTable(ui->CardRecordTableView);

        for(const CardRecord & record : mCurrentCard->Records)
        {
            TableRow row;

            row.push_back(new QTableWidgetItem(record.Symptomns));
            row.push_back(new QTableWidgetItem(record.Diagnosis));
            row.push_back(new QTableWidgetItem(record.Date.toString()));
            row.push_back(new QTableWidgetItem(record.Doctor));

            cards.push_back(row);
        }

        Utils::Update(ui->CardRecordTableView, cards);
    }
}
