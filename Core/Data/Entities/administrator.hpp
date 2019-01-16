#ifndef ADMINISTRATOR_HPP
#define ADMINISTRATOR_HPP

#include <QDataStream>

#include "Core/Data/Entities/user.hpp"

struct Administrator : public User
{
    Administrator()
    {
        GroupID = 0;
    }
};

inline bool operator ==(const Administrator & a, const Administrator & b)
{
    return a.Username == b.Username && a.Firstname == b.Firstname && a.Lastname == b.Lastname && a.Patronymic == b.Patronymic;
}

inline QDataStream & operator<<(QDataStream & stream, const Administrator & value)
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

inline QDataStream & operator>>(QDataStream & stream, Administrator & value)
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

#endif // ADMINISTRATOR_HPP
