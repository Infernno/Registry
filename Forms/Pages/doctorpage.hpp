#ifndef DOCTORPAGE_HPP
#define DOCTORPAGE_HPP

#include <QWidget>

#include "Core/Data/dbset.hpp"
#include "Core/Data/database.hpp"

#include "Core/Data/Entities/medicalcard.hpp"

namespace Ui {
class DoctorPage;
}

class DoctorPage : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorPage(QWidget *parent = nullptr);
    ~DoctorPage();

private slots:
    void on_AcceptPatient_clicked();

    void on_SearchCardButton_clicked();

    void on_AddCardRecordButton_clicked();

    void on_RemoveCardRecordButtton_clicked();

private:
    void initialize();
    void setHeader();
    void setAutocomplete();
    void refresh();

    LinkedList<Appointment> * mAppointments;
    LinkedList<MedicalCard> * mCards;

    MedicalCard * mCurrentCard = nullptr;

    int mPatientId;

    Ui::DoctorPage *ui;

};

#endif // DOCTORPAGE_HPP
