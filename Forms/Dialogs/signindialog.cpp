#include "signindialog.hpp"
#include "ui_signindialog.h"

#include <QMessageBox>

#include "Core/Managers/authmanager.hpp"
#include "Core/utils.h"

SignInDialog::SignInDialog(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::SignInDialog)
{
    ui->setupUi(this);

    setFixedSize(size());
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
}

SignInDialog::~SignInDialog()
{
    delete ui;
}

void SignInDialog::signInClicked()
{
    QString username = ui->UsernameField->text();
    QString passwordHash = ui->PasswordField->text();

    if(AuthManager::Instance()->Authenticate(username, passwordHash))
    {
        QDialog::accept();
    }
    else
    {
        QMessageBox::critical(nullptr, "Ошибка авторизации", "Введен неправильный логин или пароль!");
    }

}

void SignInDialog::closeEvent(QCloseEvent *)
{
    QDialog::reject();
}
