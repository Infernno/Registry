#ifndef ADDEDITAPPOINTMENT_HPP
#define ADDEDITAPPOINTMENT_HPP

#include <QDialog>
#include "Core/Data/Entities/appointment.hpp"

namespace Ui {
class AddEditAppointment;
}

class AddEditAppointment : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditAppointment(QWidget *parent = nullptr);
    ~AddEditAppointment();

    void setData(const Appointment & appointment);
    Appointment getData() const;

private slots:
    void accept();
    void reject();

private:
    void initialize();


    Ui::AddEditAppointment *ui;
};

#endif // ADDEDITAPPOINTMENT_HPP
