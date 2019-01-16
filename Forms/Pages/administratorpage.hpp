#ifndef ADMINISTRATORPAGE_HPP
#define ADMINISTRATORPAGE_HPP

#include <QWidget>

#include "Core/Data/Entities/medicalcard.hpp"

namespace Ui {
class AdministratorPage;
}

class AdministratorPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdministratorPage(QWidget *parent = nullptr);
    ~AdministratorPage();

private slots:
    void on_AddPatientButton_clicked();

    void on_EditPatientButton_clicked();

    void on_RemovePatientButton_clicked();

    void on_AddRegistratorButton_clicked();

    void on_EditRegistratorButton_clicked();

    void on_RemoveRegistratorButton_clicked();

    void on_AddDoctorButton_clicked();

    void on_EditDoctorButton_clicked();

    void on_RemoveDoctorButton_clicked();

    void on_AddAppointmentButton_clicked();

    void on_RemoveAppointmentButton_clicked();

    void on_FindCardButton_clicked();

    void on_RemoveCardRecordButton_clicked();

    void on_AddCardRecordButton_clicked();

private:
    void initialize();
    void setAutocomplete();

    void refresh();

    MedicalCard * mCurrentCard = nullptr;

    Ui::AdministratorPage *ui;
};

#endif // ADMINISTRATORPAGE_HPP
