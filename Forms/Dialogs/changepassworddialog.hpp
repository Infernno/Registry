#ifndef CHANGEPASSWORDDIALOG_HPP
#define CHANGEPASSWORDDIALOG_HPP

#include <QDialog>

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordDialog(QWidget *parent = nullptr);
    ~ChangePasswordDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangePasswordDialog *ui;
};

#endif // CHANGEPASSWORDDIALOG_HPP
