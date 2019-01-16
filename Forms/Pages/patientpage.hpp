#ifndef PATIENTPAGE_HPP
#define PATIENTPAGE_HPP

#include <QWidget>
#include <QVector>

#include "Core/Data/Entities/patient.hpp"
#include "Core/Data/Entities/appointment.hpp"
#include "Core/Data/Entities/medicalcard.hpp"

namespace Ui
{
class PatientPage;
}

class PatientPage : public QWidget
{
    Q_OBJECT

public:
    explicit PatientPage(QWidget * parent = nullptr);
    ~PatientPage();

private:
    void setHeader(const Patient & patient);

    void setMedicalCard(const MedicalCard & card);
    void setAppointments(const QVector<Appointment> & appointments);

    void initialize();

    Ui::PatientPage * ui;
};

#endif // PATIENTPAGE_HPP
