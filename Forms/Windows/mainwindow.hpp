#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "Core/Data/database.hpp"
#include "Core/Managers/authmanager.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

private slots:
    void on_changePasswordAction_triggered();

    void on_aboutProgramAction_triggered();

private:
    void closeEvent(QCloseEvent * event);

    void initialize();

    void setupInterface();

    void saveData();

    bool loadData();

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_HPP
