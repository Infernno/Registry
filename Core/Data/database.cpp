#include "database.hpp"

#include <QDebug>
#include <QFile>
#include <QDataStream>

#include "Core/utils.h"

LinkedList<Administrator> * Database::adminTable()
{
    return &mAdminTable;
}

LinkedList<Registrator> *Database::registratorTable()
{
    return &mRegistratorTable;
}

LinkedList<Doctor> *Database::doctorTable()
{
    return &mDoctorTable;
}

LinkedList<Appointment> *Database::appointmentTable()
{
    return &mAppointmentTable;
}

LinkedList<MedicalCard> * Database::medicalCardTable()
{
    return &mMedicalCard;
}

LinkedList<Patient> *Database::patientTable()
{
    return &mPatientTable;
}

void Database::save(QDataStream &stream)
{
    mAdminTable.save(stream);
    mRegistratorTable.save(stream);
    mDoctorTable.save(stream);
    mPatientTable.save(stream);
    mAppointmentTable.save(stream);
    mMedicalCard.save(stream);
}

void Database::load(QDataStream &stream)
{
    mAdminTable.load(stream);
    mRegistratorTable.load(stream);
    mDoctorTable.load(stream);
    mPatientTable.load(stream);
    mAppointmentTable.load(stream);

    for(const auto & card : mMedicalCard.all())
        qDebug() << card.PatientOwner << "|" << card.Records.size();

    mMedicalCard.load(stream);

    for(const auto & card : mMedicalCard.all())
        qDebug() << card.PatientOwner << "|" << card.Records.size();
}

Database *Database::Instance()
{
    static Database instance;

    return &instance;
}
