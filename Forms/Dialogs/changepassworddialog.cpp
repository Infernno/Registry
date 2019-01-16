#include "changepassworddialog.hpp"
#include "ui_changepassworddialog.h"

#include <QMessageBox>
#include "Core/Managers/authmanager.hpp"

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePasswordDialog)
{
    ui->setupUi(this);

    setFixedSize(size());
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::on_pushButton_clicked()
{
    if(ui->CurrentPasswordField->text().isEmpty() || ui->NewPasswordField->text().isEmpty() || ui->RepeatPasswordField->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Не все поля заполнены!");
        return;
    }

    if(AuthManager::Instance()->getCurrentProfile()->PasswordHash != ui->CurrentPasswordField->text())
    {
        QMessageBox::warning(this, "Ошибка", "Текущий пароль неправильный!");
        return;
    }

    if(ui->NewPasswordField->text() != ui->RepeatPasswordField->text())
    {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают!");
        return;
    }

    AuthManager::Instance()->changePassword(ui->NewPasswordField->text());
    QMessageBox::information(this, "Изменение пароля", "Пароль успешно изменен!");
    QDialog::accept();
}
