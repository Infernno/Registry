#include "doctorpage.hpp"
#include "ui_doctorpage.h"

#include <QDebug>
#include <QMessageBox>
#include <QCompleter>

#include "Core/utils.h"
#include "Core/Managers/authmanager.hpp"
#include "Forms/Dialogs/addeditcardrecord.hpp"

DoctorPage::DoctorPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorPage),
    mCurrentCard(nullptr)
{
    ui->setupUi(this);

    initialize();
    refresh();
}

DoctorPage::~DoctorPage()
{
    delete ui;
}

void DoctorPage::initialize()
{
    mAppointments = Database::Instance()->appointmentTable();
    mCards = Database::Instance()->medicalCardTable();

    Utils::InitializeTable(ui->AppointmentsTableWidget, QStringList() << "Пациент" << "Врач" << "Время");
    Utils::InitializeTable(ui->CardRecordTableWidget, QStringList() << "Симптом" << "Диагноз" << "Дата" << "Врач");

    setAutocomplete();
    setHeader();

}
void DoctorPage::setHeader()
{
    auto headerData = (const Doctor*)AuthManager::Instance()->getCurrentProfile();

    ui->SpecialityLabel->setText(headerData->Speciality);
    ui->EmploymentDateLabel->setText(headerData->EmploymentDate.toString());
}

void DoctorPage::setAutocomplete()
{
    QStringList patientsComplete;

    for(const auto & patient : Database::Instance()->patientTable()->all())
        patientsComplete << patient.getFullName();

    auto patients = new QCompleter(patientsComplete);

    patients->setCaseSensitivity(Qt::CaseInsensitive);
    patients->setCompletionMode(QCompleter::PopupCompletion);

    ui->PatientNameField->setCompleter(patients);
}

void DoctorPage::refresh()
{
    Utils::ClearTable(ui->AppointmentsTableWidget);

    TableData appointments;

    auto items = mAppointments->all([](const Appointment & item){return item.Doctor == AuthManager::Instance()->getFullName();});

    for(const Appointment & appointment : items)
    {
        TableRow row;

        row.push_back(new QTableWidgetItem(appointment.Patient));
        row.push_back(new QTableWidgetItem(appointment.Doctor));
        row.push_back(new QTableWidgetItem(appointment.Date.toString("dd.MM.yyyy HH:mm")));

        appointments.push_back(row);
    }

    Utils::Update(ui->AppointmentsTableWidget, appointments);

    if(mCurrentCard != nullptr)
    {
        Utils::ClearTable(ui->CardRecordTableWidget);

        TableData records;

        for(const CardRecord & record : mCurrentCard->Records)
        {
            TableRow row;

            row.push_back(new QTableWidgetItem(record.Symptomns));
            row.push_back(new QTableWidgetItem(record.Diagnosis));
            row.push_back(new QTableWidgetItem(record.Date.toString()));
            row.push_back(new QTableWidgetItem(record.Doctor));

            records.push_back(row);
        }

        Utils::Update(ui->CardRecordTableWidget, records);
    }
}

void DoctorPage::on_AcceptPatient_clicked()
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


        if(mAppointments->contains(appointment))
        {
            QMessageBox::information(this, "Пациент принят", "Пациент принят!");

            mAppointments->remove(appointment);
            refresh();
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Ошибка при удалении: талон не найден!");
        }
    }
}

void DoctorPage::on_SearchCardButton_clicked()
{
    auto patientName = ui->PatientNameField->text();

    auto patient = Database::Instance()->patientTable()->find([&patientName](const Patient & patient) {
        return patient.getFullName() == patientName;
    });

    if(patient != nullptr)
    {
        mPatientId= patient->ID;

        mCurrentCard = mCards->find([this](const MedicalCard & card){
            return card.PatientOwner == mPatientId;
        });

        if(mCurrentCard != nullptr)
        {
            ui->AddCardRecordButton->setEnabled(true);
            ui->RemoveCardRecordButtton->setEnabled(true);

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

void DoctorPage::on_AddCardRecordButton_clicked()
{
    AddEditCardRecord addEdit;

    if(addEdit.exec() == QDialog::Accepted)
    {
        auto record = addEdit.getRecord();

        mCurrentCard->Records.push_back(record);

        refresh();
    }
}

void DoctorPage::on_RemoveCardRecordButtton_clicked()
{
    auto selection = ui->CardRecordTableWidget->selectionModel();

    qDebug() << "Deleting!";

    if(selection->hasSelection())
    {
        int row = selection->currentIndex().row();
        auto dateText = ui->CardRecordTableWidget->item(row, 2)->text();
        auto date = QDateTime::fromString(dateText);

        qDebug() << "Selected row - " << row;

        for(auto record = mCurrentCard->Records.begin(); record != mCurrentCard->Records.end(); record++)
        {
            if(date.toString() == record->Date.toString())
            {
                mCurrentCard->Records.erase(record);

                QMessageBox::information(this, "Удалено", "Успешно удалено!");

                refresh();

                break;
            }
        }
    }
}
