#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#include "Core/utils.h"
#include "Core/Data/database.hpp"
#include "Core/Managers/usermanager.h"

namespace Bootstrap
{
static void CreatePatients(Database * database);
static void CreateRegistrators();
static void CreateDoctors();
static void CreateAdmin();

void Initialize(Database * database)
{
    CreatePatients(database);
    CreateRegistrators();
    CreateDoctors();
    CreateAdmin();
}

static void CreatePatients(Database * database)
{
    Patient patient;

    patient.Username = "test";
    patient.PasswordHash = "123456";
    patient.Lastname = "Пичугин";
    patient.Firstname = "Алексей";
    patient.Patronymic = "Борисович";
    patient.Doctor = "Манаева Оксана Владимировна";
    patient.Birthday = QDate(1998, 1, 22);
    patient.Address = "ул. Мира, дом 63, кв. 4";

    UserManager::AddOrUpdate(patient, true);

    Appointment appointment;

    appointment.Date = QDateTime::currentDateTime().addDays(6);
    appointment.Doctor = patient.Doctor;
    appointment.Patient = patient.getFullName();

    database->appointmentTable()->addAuto(appointment);
}

static void CreateRegistrators()
{
    Registrator registrator;

    registrator.Lastname = "Исмагилов";
    registrator.Firstname = "Антон";
    registrator.Patronymic = "Русланович";
    registrator.Username = "reg1";
    registrator.PasswordHash = "qwerty";

    UserManager::AddOrUpdate(registrator, true);
}

static void CreateDoctors()
{
    Doctor doc;

    doc.Username = "manaeva-oks";
    doc.PasswordHash = "123456";
    doc.Lastname = "Манаева";
    doc.Firstname = "Оксана";
    doc.Patronymic = "Владимировна";
    doc.Speciality = "Врач-терапевт";
    doc.EmploymentDate = QDate::currentDate().addYears(-2);

    UserManager::AddOrUpdate(doc);
}

static void CreateAdmin()
{
    Administrator admin;

    admin.Username = "admin";
    admin.PasswordHash = "1234";
    admin.Lastname = "Свиридов";
    admin.Firstname = "Владислав";
    admin.Patronymic = "Сергеевич";

    UserManager::AddOrUpdate(admin);
}
}

#endif // BOOTSTRAP_H
