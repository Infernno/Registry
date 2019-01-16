#ifdef IDENTITY_HPP
#define IDENTITY_HPP

#include <QString>
#include <QDataStream>
#include "Core/Data/entitybase.hpp"

struct Identity : public EntityBase
{
    QString Username;
    QString PasswordHash;

    int GroupID;
};

inline bool operator ==(const Identity & a, const Identity & b)
{
    return a.Username == b.Username && a.PasswordHash == b.PasswordHash && a.GroupID == b.GroupID;
}

inline QDataStream & operator<<(QDataStream & stream, const Identity & value)
{
    stream << value.ID
           << value.Username
           << value.PasswordHash
           << value.GroupID;

    return stream;
}

inline QDataStream & operator>>(QDataStream & stream, Identity & value)
{
    stream >> value.ID
           >> value.Username
           >> value.PasswordHash
           >> value.GroupID;

    return stream;
}

#endif // IDENTITY_HPP
