#ifndef GROUP_HPP
#define GROUP_HPP

#include <QString>

#include "Core/Data/Entities/user.hpp"


struct Group : public EntityBase
{
    QString GroupName;
//    Permission Permissions;
};

/*
inline bool operator ==(const Group & a, const Group & b)
{
    return a.GroupName == b.GroupName && a.Permissions == b.Permissions;
}

inline QDataStream & operator<<(QDataStream & stream, const Group & value)
{
    stream << value.ID
           << value.GroupName
           << value.Permissions;

    return stream;
}

inline QDataStream & operator>>(QDataStream & stream, Group & value)
{
    stream >> value.ID
            >> value.GroupName
            >> value.Permissions;

    return stream;
}

*/

#endif // GROUP_HPP
