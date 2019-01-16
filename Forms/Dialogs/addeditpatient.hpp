#ifndef ADDEDITPATIENT_HPP
#define ADDEDITPATIENT_HPP

#include <QDialog>

#include "Core/Data/Entities/medicalcard.hpp"
#include "Core/Data/Entities/patient.hpp"

namespace Ui {
class AddEditPatient;
}

class AddEditPatient : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditPatient(QWidget *parent = nullptr);
    ~AddEditPatient();

    void setData(const Patient & patient);
    Patient getPatient() const;


private slots:
    void on_AcceptButton_clicked();

private:

    void initialize();

    Ui::AddEditPatient *ui;
};

#endif // ADDEDITPATIENT_HPP
