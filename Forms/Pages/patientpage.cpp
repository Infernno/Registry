#include "patientpage.hpp"
#include "ui_patientpage.h"

#include "Core/utils.h"
#include "Core/Data/database.hpp"
#include "Core/Managers/authmanager.hpp"

PatientPage::PatientPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientPage)
{
    ui->setupUi(this);

    initialize();
}

PatientPage::~PatientPage()
{
    delete ui;
}

void PatientPage::setHeader(const Patient &patient)
{
    ui->Doctor->setText(patient.Doctor);
    ui->Birthday->setText(patient.Birthday.toString());
    ui->Address->setText(patient.Address);
}

void PatientPage::setMedicalCard(const MedicalCard &card)
{
    Utils::InitializeTable(ui->RecordsView, QStringList() << "Симптомы" << "Диагноз" << "Врач" << "Время");

    TableData data;

    for(const CardRecord & record : card.Records)
    {
        TableRow row;

        row.push_back(new QTableWidgetItem(record.Symptomns));
        row.push_back(new QTableWidgetItem(record.Diagnosis));
        row.push_back(new QTableWidgetItem(record.Doctor));
        row.push_back(new QTableWidgetItem(record.Date.toString()));

        data.push_back(row);
    }

    Utils::Update(ui->RecordsView, data);
}

void PatientPage::setAppointments(const QVector<Appointment> &appointments)
{
    Utils::InitializeTable(ui->AppointmentView, QStringList() << "Пациент" << "Врач" << "Время");

    TableData data;

    for(const Appointment & appointment : appointments)
    {
        TableRow row;

        row.push_back(new QTableWidgetItem(appointment.Patient));
        row.push_back(new QTableWidgetItem(appointment.Doctor));
        row.push_back(new QTableWidgetItem(appointment.Date.toString()));

        data.push_back(row);
    }

    Utils::Update(ui->AppointmentView, data);
}

void PatientPage::initialize()
{
    auto patient = Database::Instance()->patientTable()->find([](const auto & patient) {
        return patient.Username == AuthManager::Instance()->getUsername();
    });

    auto appointments = Database::Instance()->appointmentTable()->all([patient](const Appointment & appointment){
        return appointment.Patient == patient->getFullName();
    });

    auto card = Database::Instance()->medicalCardTable()->find([patient](const MedicalCard & card){
        return patient->ID == card.PatientOwner;
    });

    setHeader(*patient);
    setAppointments(appointments);
    setMedicalCard(*card);
}
