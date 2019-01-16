#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <QDate>

#include "Core/Data/Entities/user.hpp"

struct Patient : public User
{
    QString Doctor;
    QString Address;
    QDate Birthday;

    Patient()
    {
        GroupID = 3;
    }
};

inline bool operator ==(const Patient & a, const Patient & b)
{
    return a.Username == b.Username;
}

inline QDataStream & operator<<(QDataStream & stream, const Patient & value)
{
    stream << value.ID
           << value.Username
           << value.PasswordHash
           << value.GroupID
           << value.Firstname
           << value.Lastname
           << value.Patronymic
           << value.Doctor
           << value.Birthday
           << value.Address;

    return stream;
}

inline QDataStream & operator>>(QDataStream & stream, Patient & value)
{
    stream >> value.ID
           >> value.Username
           >> value.PasswordHash
           >> value.GroupID
           >> value.Firstname
           >> value.Lastname
           >> value.Patronymic
           >> value.Doctor
           >> value.Birthday
           >> value.Address;

    return stream;
}

#endif // PATIENT_HPP
