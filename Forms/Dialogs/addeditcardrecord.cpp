#include "addeditcardrecord.hpp"
#include "ui_addeditcardrecord.h"

#include <QDateTime>
#include <QMessageBox>

#include "Core/Managers/authmanager.hpp"

AddEditCardRecord::AddEditCardRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditCardRecord)
{
    ui->setupUi(this);
    ui->DateField->setDateTime(QDateTime::currentDateTime());
}

AddEditCardRecord::~AddEditCardRecord()
{
    delete ui;
}

CardRecord AddEditCardRecord::getRecord()
{
    CardRecord record;

    record.Symptomns = ui->SymptomsField->toPlainText();
    record.Diagnosis = ui->DyagnosField->toPlainText();
    record.Date = ui->DateField->dateTime();
    record.Doctor = AuthManager::Instance()->getFullName();

    return record;
}

void AddEditCardRecord::accept()
{
    if(ui->SymptomsField->toPlainText().isEmpty() || ui->DyagnosField->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Не все поля заполнены");
    }
    else
    {
        QDialog::accept();
    }
}

void AddEditCardRecord::reject()
{
    QDialog::reject();
}
