#ifndef ADDEDITCARDRECORD_HPP
#define ADDEDITCARDRECORD_HPP

#include <QDialog>
#include "Core/Data/Entities/medicalcard.hpp"

namespace Ui {
class AddEditCardRecord;
}

class AddEditCardRecord : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditCardRecord(QWidget *parent = nullptr);
    ~AddEditCardRecord();

    CardRecord getRecord();

private slots:
    void accept();
    void reject();

private:
    Ui::AddEditCardRecord *ui;
};

#endif // ADDEDITCARDRECORD_HPP
