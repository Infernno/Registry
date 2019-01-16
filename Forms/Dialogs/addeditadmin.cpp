#include "addeditadmin.hpp"
#include "ui_addeditadmin.h"

AddEditAdmin::AddEditAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditAdmin)
{
    ui->setupUi(this);

    setFixedSize(size());
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
}

AddEditAdmin::~AddEditAdmin()
{
    delete ui;
}

void AddEditAdmin::on_AcceptButton_clicked()
{

}
