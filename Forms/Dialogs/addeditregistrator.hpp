#ifndef ADDEDITREGISTRATOR_HPP
#define ADDEDITREGISTRATOR_HPP

#include <QDialog>

#include "Core/Data/Entities/registrator.hpp"

namespace Ui {
class AddEditRegistrator;
}

class AddEditRegistrator : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditRegistrator(QWidget *parent = nullptr);
    ~AddEditRegistrator();

    void setData(const Registrator & registrator);
    Registrator getData();

private slots:
    void on_AcceptButton_clicked();

private:
    Ui::AddEditRegistrator *ui;
};

#endif // ADDEDITREGISTRATOR_HPP
