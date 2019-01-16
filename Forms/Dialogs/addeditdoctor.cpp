#include "addeditdoctor.hpp"
#include "ui_addeditdoctor.h"

AddEditDoctor::AddEditDoctor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditDoctor)
{
    ui->setupUi(this);

    setFixedSize(size());
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
}

AddEditDoctor::~AddEditDoctor()
{
    delete ui;
}

Doctor AddEditDoctor::getData()
{
    Doctor data;

    data.Username = ui->UsernameField->text();
    data.PasswordHash = ui->PasswordField->text();
    data.Lastname = ui->LastnameField->text();
    data.Firstname = ui->FirstnameField->text();
    data.Patronymic = ui->PatronymicField->text();
    data.Speciality = ui->SpecialityField->text();
    data.EmploymentDate = ui->EmploymentDateField->date();

    return data;
}

void AddEditDoctor::setData(const Doctor &data)
{
    ui->UsernameField->setText(data.Username);
    ui->PasswordField->setText(data.PasswordHash);
    ui->LastnameField->setText(data.Lastname);
    ui->FirstnameField->setText(data.Firstname);
    ui->PatronymicField->setText(data.Patronymic);
    ui->SpecialityField->setText(data.Speciality);
    ui->EmploymentDateField->setDate(data.EmploymentDate);
}

void AddEditDoctor::on_AcceptButton_clicked()
{
    QDialog::accept();
}
