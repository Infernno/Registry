#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include <QDate>

#include "Core/Data/entitybase.hpp"
#include "Core/Data/Entities/user.hpp"

struct Doctor : public User
{
    QString Speciality;
    QDate EmploymentDate;

    Doctor()
    {
        GroupID = 2;
    }
};

inline bool operator ==(const Doctor & a, const Doctor & b)
{
    return a.Username == b.Username && a.Firstname == b.Firstname && a.Lastname == b.Lastname && a.Patronymic == b.Patronymic;
}

inline QDataStream & operator<<(QDataStream & stream, const Doctor & value)
{
    stream << value.ID
           << value.Username
           << value.PasswordHash
           << value.GroupID
           << value.Firstname
           << value.Lastname
           << value.Patronymic
           << value.Speciality
           << value.EmploymentDate;

    return stream;
}

inline QDataStream & operator>>(QDataStream & stream, Doctor & value)
{
    stream >> value.ID
           >> value.Username
           >> value.PasswordHash
           >> value.GroupID
           >> value.Firstname
           >> value.Lastname
           >> value.Patronymic
           >> value.Speciality
           >> value.EmploymentDate;;

    return stream;
}


#endif // DOCTOR_HPP
