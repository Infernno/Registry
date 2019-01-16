#include "addeditpatient.hpp"
#include "ui_addeditpatient.h"

#include <QCompleter>
#include "Core/Data/database.hpp"

AddEditPatient::AddEditPatient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditPatient)
{
    ui->setupUi(this);

    setFixedSize(size());
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    initialize();
}

AddEditPatient::~AddEditPatient()
{
    delete ui;
}

void AddEditPatient::setData(const Patient &patient)
{
    ui->UsernameField->setText(patient.Username);
    ui->PasswordField->setText(patient.PasswordHash);
    ui->LastnameField->setText(patient.Lastname);
    ui->FirstnameField->setText(patient.Firstname);
    ui->PatronymicField->setText(patient.Patronymic);
    ui->BirthdayField->setDate(patient.Birthday);
    ui->DoctorField->setText(patient.Doctor);
    ui->AddressField->setText(patient.Address);
}

Patient AddEditPatient::getPatient() const
{
    Patient patient;

    patient.Username = ui->UsernameField->text();
    patient.PasswordHash = ui->PasswordField->text();
    patient.Lastname = ui->LastnameField->text();
    patient.Firstname = ui->FirstnameField->text();
    patient.Patronymic = ui->PatronymicField->text();
    patient.Birthday = ui->BirthdayField->date();
    patient.Address = ui->AddressField->text();
    patient.Doctor = ui->DoctorField->text();

    return patient;
}


void AddEditPatient::on_AcceptButton_clicked()
{
    QDialog::accept();
}

void AddEditPatient::initialize()
{
    QStringList doctors;

    for(const Doctor & doctor : Database::Instance()->doctorTable()->all())
    {
        doctors << doctor.getFullName();
    }

    auto completer = new QCompleter(doctors);

    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);

    ui->DoctorField->setCompleter(completer);
}
