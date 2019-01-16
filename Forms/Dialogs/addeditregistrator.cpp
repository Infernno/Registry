#include "addeditregistrator.hpp"
#include "ui_addeditregistrator.h"

AddEditRegistrator::AddEditRegistrator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditRegistrator)
{
    ui->setupUi(this);

    setFixedSize(size());
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
}

AddEditRegistrator::~AddEditRegistrator()
{
    delete ui;
}

void AddEditRegistrator::setData(const Registrator &registrator)
{
    ui->UsernameField->setText(registrator.Username);
    ui->PasswordField->setText(registrator.PasswordHash);
    ui->LastnameField->setText(registrator.Lastname);
    ui->FirstnameField->setText(registrator.Firstname);
    ui->PatronymicField->setText(registrator.Patronymic);
}

Registrator AddEditRegistrator::getData()
{
    Registrator reg;

    reg.Username = ui->UsernameField->text();
    reg.PasswordHash = ui->PasswordField->text();
    reg.Lastname = ui->LastnameField->text();
    reg.Firstname = ui->FirstnameField->text();
    reg.Patronymic = ui->PatronymicField->text();

    return reg;
}

void AddEditRegistrator::on_AcceptButton_clicked()
{
    QDialog::accept();
}
