#ifndef REGISTRATORPAGE_HPP
#define REGISTRATORPAGE_HPP

#include <QWidget>

#include "Core/Data/dbset.hpp"
#include "Core/Data/Entities/patient.hpp"
#include "Core/Data/Entities/appointment.hpp"

namespace Ui
{
class RegistratorPage;
}

class RegistratorPage : public QWidget
{
    Q_OBJECT

public:
    explicit RegistratorPage(QWidget *parent = nullptr);
    ~RegistratorPage();

private slots:
    void addPatientButton();
    void editPatientButton();
    void removePatientButton();

    void addAppointmentButton();
    void removeAppointmentButton();

private:
    void initialize();
    void refresh();

    LinkedList<Patient> * mPatients;
    LinkedList<Appointment> * mAppointments;

    Ui::RegistratorPage *ui;
};

#endif // REGISTRATORPAGE_HPP
