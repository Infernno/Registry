#ifndef ADDEDITADMIN_HPP
#define ADDEDITADMIN_HPP

#include <QDialog>
#include "Core/Data/Entities/administrator.hpp"


namespace Ui {
class AddEditAdmin;
}

class AddEditAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditAdmin(QWidget *parent = nullptr);
    ~AddEditAdmin();

private slots:
    void on_AcceptButton_clicked();

private:
    Ui::AddEditAdmin *ui;
};

#endif // ADDEDITADMIN_HPP
