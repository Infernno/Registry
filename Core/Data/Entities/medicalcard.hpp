#ifndef MEDICALCARD_HPP
#define MEDICALCARD_HPP

#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QDataStream>

#include <list>

#include "Core/Data/entitybase.hpp"

struct CardRecord
{
    QString Symptomns;
    QString Diagnosis;
    QString Doctor;
    QDateTime Date;
};

struct MedicalCard : public EntityBase
{
    int PatientOwner;
    std::list<CardRecord> Records;

    MedicalCard()
    {
        Records.clear();
    }
};

inline bool operator ==(const CardRecord & a, const CardRecord & b)
{
    return a.Date == b.Date &&
            a.Diagnosis == b.Diagnosis &&
            a.Doctor == b.Doctor &&
            a.Symptomns == b.Symptomns;
}

inline QDataStream & operator<<(QDataStream & stream, const CardRecord & value)
{
    stream << value.Diagnosis
           << value.Doctor
           << value.Symptomns
           << value.Date;

    return stream;
}

inline QDataStream & operator>>(QDataStream & stream, CardRecord & value)
{
    stream >> value.Diagnosis
            >> value.Doctor
            >> value.Symptomns
            >> value.Date;

    return stream;
}

inline bool operator ==(const MedicalCard & a, const MedicalCard & b)
{
    return a.ID == b.ID && a.PatientOwner == b.PatientOwner && a.Records.size() == b.Records.size();
}

inline QDataStream & operator<<(QDataStream & stream, const MedicalCard & value)
{
    stream << value.ID
           << value.PatientOwner
           << value.Records.size();

    if(value.Records.size() > 0)
    {
        for(const auto & record : value.Records)
            stream << record;
    }

    return stream;
}

inline QDataStream & operator>>(QDataStream & stream, MedicalCard & value)
{
    size_t count = 0;
    CardRecord temp;

    stream >> value.ID
            >> value.PatientOwner
            >> count;

    value.Records.clear();

    if(count > 0)
    {
        while(count-- > 0)
        {
            stream >> temp;

            value.Records.push_back(temp);
        }
    }

    return stream;
}

#endif // MEDICALCARD_HPP
