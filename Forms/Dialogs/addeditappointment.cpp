#include "addeditappointment.hpp"
#include "ui_addeditappointment.h"

#include <QCompleter>
#include <QMessageBox>

#include "Core/Data/database.hpp"

AddEditAppointment::AddEditAppointment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditAppointment)
{
    ui->setupUi(this);

    initialize();
}

AddEditAppointment::~AddEditAppointment()
{
    delete ui;
}

void AddEditAppointment::setData(const Appointment &appointment)
{
    ui->DoctorField->setText(appointment.Doctor);
    ui->PatiendField->setText(appointment.Patient);
    ui->DateField->setDateTime(appointment.Date);
}

Appointment AddEditAppointment::getData() const
{
    Appointment data;

    data.Doctor = ui->DoctorField->text();
    data.Patient = ui->PatiendField->text();
    data.Date = ui->DateField->dateTime();

    return data;
}

void AddEditAppointment::accept()
{
    if(ui->PatiendField->text().isEmpty() || ui->DoctorField->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Не все поля заполнены!");
        return;
    }

    if(ui->DateField->dateTime() < QDateTime::currentDateTime()) {
        QMessageBox::warning(this, "Ошибка", "Время записи не может быть прошлым!");
        return;
    }

    QDialog::accept();
}

void AddEditAppointment::reject()
{
    QDialog::reject();
}

void AddEditAppointment::initialize()
{
    QStringList patientsComplete;
    QStringList doctorsComplete;

    for(const auto & doctor : Database::Instance()->doctorTable()->all())
        doctorsComplete << doctor.getFullName();

    for(const auto & patient : Database::Instance()->patientTable()->all())
        patientsComplete << patient.getFullName();

    auto doctors = new QCompleter(doctorsComplete);
    auto patients = new QCompleter(patientsComplete);

    doctors->setCaseSensitivity(Qt::CaseInsensitive);
    doctors->setCompletionMode(QCompleter::PopupCompletion);

    patients->setCaseSensitivity(Qt::CaseInsensitive);
    patients->setCompletionMode(QCompleter::PopupCompletion);

    ui->PatiendField->setCompleter(patients);
    ui->DoctorField->setCompleter(doctors);
}
