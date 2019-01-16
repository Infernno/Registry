#ifndef USER_HPP
#define USER_HPP

#include <QString>
#include <QDataStream>

#include "Core/Data/entitybase.hpp"

struct User : public EntityBase
{
    QString Username;
    QString PasswordHash;

    int GroupID;

    QString Firstname;
    QString Lastname;
    QString Patronymic;

    QString getFullName() const
    {
        return QString("%1 %2 %3").arg(Lastname, Firstname, Patronymic);
    }
};

#endif // USER_HPP
