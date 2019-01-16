#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QString>

#include "Core/Data/dbset.hpp"

#include "Core/Data/Entities/administrator.hpp"
#include "Core/Data/Entities/registrator.hpp"
#include "Core/Data/Entities/doctor.hpp"
#include "Core/Data/Entities/patient.hpp"

#include "Core/Data/Entities/appointment.hpp"
#include "Core/Data/Entities/medicalcard.hpp"

class Database
{
private:
    Database() = default;

    LinkedList<Administrator> mAdminTable;
    LinkedList<Registrator> mRegistratorTable;
    LinkedList<Doctor> mDoctorTable;
    LinkedList<Patient> mPatientTable;

    LinkedList<Appointment> mAppointmentTable;
    LinkedList<MedicalCard> mMedicalCard;

public:
    LinkedList<Administrator> * adminTable();
    LinkedList<Registrator> * registratorTable();
    LinkedList<Doctor> * doctorTable();
    LinkedList<Patient> * patientTable();

    LinkedList<Appointment> * appointmentTable();
    LinkedList<MedicalCard> * medicalCardTable();

    void save(QDataStream & stream);
    void load(QDataStream & stream);

    static Database * Instance();
};

#endif // DATABASE_HPP
