#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QDebug>

#include "Core/Data/Entities/administrator.hpp"
#include "Core/Data/Entities/doctor.hpp"
#include "Core/Data/Entities/registrator.hpp"
#include "Core/Data/Entities/patient.hpp"

#include "Core/Data/database.hpp"

class UserManager
{
public:
    UserManager() = delete;

    static void AddOrUpdate(Administrator & administrator, bool updateId = false)
    {
        auto profile = Database::Instance()->adminTable()->find([&administrator](const auto & item)
        {
            return item.Username == administrator.Username;
        });

        if(profile == nullptr)
        {
            if(updateId)
            {
                Database::Instance()->adminTable()->addAuto(administrator);
            }
            else
            {
                Database::Instance()->adminTable()->add(administrator);
            }
        }
        else
        {
            Database::Instance()->adminTable()->update(*profile, administrator);
        }
    }

    static void AddOrUpdate(Doctor & doctor, bool updateId = false)
    {
        auto profile = Database::Instance()->doctorTable()->find([&doctor](const auto & item)
        {
            return item.Username == doctor.Username;
        });

        if(profile == nullptr)
        {
            if(updateId)
            {
                Database::Instance()->doctorTable()->addAuto(doctor);
            }
            else
            {
                Database::Instance()->doctorTable()->add(doctor);
            }
        }
        else
        {
            Database::Instance()->doctorTable()->update(*profile, doctor);
        }
    }

    static void AddOrUpdate(Registrator & registrator, bool updateId = false)
    {
        auto profile = Database::Instance()->registratorTable()->find([&registrator](const auto & item)
        {
            return item.Username == registrator.Username;
        });

        if(profile == nullptr)
        {
            if(updateId)
            {
                Database::Instance()->registratorTable()->addAuto(registrator);
            }
            else
            {
                Database::Instance()->registratorTable()->add(registrator);
            }
        }
        else
        {
            Database::Instance()->registratorTable()->update(*profile, registrator);
        }
    }

    static void AddOrUpdate(Patient & patient, bool updateId = false)
    {
        auto profile = Database::Instance()->patientTable()->find([&patient](const auto & item)
        {
            return item.Username == patient.Username;
        });

        if(profile == nullptr)
        {
            if(updateId)
            {
                Database::Instance()->patientTable()->addAuto(patient);
            }
            else
            {
                Database::Instance()->patientTable()->add(patient);
            }

            MedicalCard card;

            card.PatientOwner = patient.ID;

            Database::Instance()->medicalCardTable()->addAuto(card);
        }
        else
        {
            Database::Instance()->patientTable()->update(*profile, patient);
        }
    }

    static bool RemoveUser(const QString & username)
    {
        auto admin = Database::Instance()->adminTable()->find([&username](const auto & item)
        {
            return item.Username == username;
        });

        auto registrator = Database::Instance()->registratorTable()->find([&username](const auto & item)
        {
            return item.Username == username;
        });

        auto doctor = Database::Instance()->doctorTable()->find([&username](const auto & item)
        {
            return item.Username == username;
        });

        auto patient = Database::Instance()->patientTable()->find([&username](const auto & item)
        {
            return item.Username == username;
        });

        if(admin != nullptr)
        {
            return Database::Instance()->adminTable()->remove(*admin);
        }

        if(registrator != nullptr)
        {
            return Database::Instance()->registratorTable()->remove(*registrator);
        }

        if(doctor != nullptr)
        {
            return Database::Instance()->doctorTable()->remove(*doctor);
        }

        if(patient != nullptr)
        {
            int id = patient->ID;

            bool patientDeleted = Database::Instance()->patientTable()->remove(*patient);
            bool cardDeleted = Database::Instance()->medicalCardTable()->remove([&id](const MedicalCard & card) { return card.PatientOwner == id;});

            if(patientDeleted != cardDeleted)
            {
                qDebug() << "Warning! patientDeleted != cardDeleted (" << patient->getFullName() << ")";
            }

            return patientDeleted && cardDeleted;
        }

        return false;
    }
};


#endif // USERMANAGER_H
