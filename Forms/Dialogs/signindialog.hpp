#ifndef SIGNINDIALOG_HPP
#define SIGNINDIALOG_HPP

#include <QDialog>

namespace Ui
{
class SignInDialog;
}

class SignInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignInDialog(QWidget * parent = nullptr);
    ~SignInDialog();

private slots:
    void signInClicked();

private:
    void closeEvent(QCloseEvent *event);

    Ui::SignInDialog *ui;
};

#endif // SIGNINDIALOG_HPP
