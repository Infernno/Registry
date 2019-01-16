#ifndef ADDEDITDOCTOR_HPP
#define ADDEDITDOCTOR_HPP

#include <QDialog>

#include "Core/Data/Entities/doctor.hpp"

namespace Ui {
class AddEditDoctor;
}

class AddEditDoctor : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditDoctor(QWidget *parent = nullptr);
    ~AddEditDoctor();

    Doctor getData();
    void setData(const Doctor & data);

private slots:
    void on_AcceptButton_clicked();

private:
    Ui::AddEditDoctor *ui;
};

#endif // ADDEDITDOCTOR_HPP
