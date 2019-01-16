#ifndef APPOINTMENT_HPP
#define APPOINTMENT_HPP

#include <QString>
#include <QDateTime>
#include <QDataStream>

#include "Core/Data/entitybase.hpp"

struct Appointment : public EntityBase
{
    QString Patient;
    QString Doctor;

    QDateTime Date;
};

inline bool operator ==(const Appointment & a, const Appointment & b)
{
    return a.Doctor == b.Doctor && a.Patient == b.Patient &&
            a.Date.toString("dd.MM.yyyy HH:mm") == b.Date.toString("dd.MM.yyyy HH:mm");
}

inline QDataStream & operator<<(QDataStream & stream, const Appointment & value)
{
    stream << value.ID
           << value.Date
           << value.Patient
           << value.Doctor;

    return stream;
}

inline QDataStream & operator>>(QDataStream & stream, Appointment & value)
{
    stream >> value.ID
            >> value.Date
            >> value.Patient
            >> value.Doctor;

    return stream;
}

#endif // APPOINTMENT_HPP
