#ifndef REGISTRATOR_HPP
#define REGISTRATOR_HPP

#include <QDataStream>

#include "Core/Data/Entities/user.hpp"

struct Registrator : public User
{
    Registrator()
    {
        GroupID = 1;
    }
};

inline bool operator ==(const Registrator & a, const Registrator & b)
{
    return a.Username == b.Username && a.Firstname == b.Firstname && a.Lastname == b.Lastname && a.Patronymic == b.Patronymic;
}

inline QDataStream & operator<<(QDataStream & stream, const Registrator & value)
{
    stream << value.ID
           << value.Username
           << value.PasswordHash
           << value.GroupID
           << value.Firstname
           << value.Lastname
           << value.Patronymic;

    return stream;
}

inline QDataStream & operator>>(QDataStream & stream, Registrator & value)
{
    stream >> value.ID
           >> value.Username
           >> value.PasswordHash
           >> value.GroupID
           >> value.Firstname
           >> value.Lastname
           >> value.Patronymic;

    return stream;
}

#endif // REGISTRATOR_HPP
