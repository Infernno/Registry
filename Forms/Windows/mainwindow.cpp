#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFile>
#include <QMap>
#include <QDebug>
#include <QTimer>
#include <QDataStream>
#include <QMessageBox>

#include "Core/utils.h"
#include "Core/bootstrap.h"

#include "Forms/Dialogs/signindialog.hpp"
#include "Forms/Pages/patientpage.hpp"
#include "Forms/Pages/registratorpage.hpp"
#include "Forms/Pages/doctorpage.hpp"
#include "Forms/Pages/administratorpage.hpp"
#include "Forms/Dialogs/changepassworddialog.hpp"

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    if(!loadData())
    {
        Bootstrap::Initialize(Database::Instance());
    }

    SignInDialog dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        setupInterface();
    }
    else
    {
        QTimer::singleShot(0, this, SLOT(close()));
    }
}

void MainWindow::setupInterface()
{
    QWidget * widget = nullptr;

    int group = AuthManager::Instance()->getUserGroup();


    switch (group) {
    case PATIENT_GROUP: widget = new PatientPage(); break;
    case REGISTRATOR_GROUP: widget = new RegistratorPage(); break;
    case DOCTOR_GROUP: widget = new DoctorPage(); break;
    case ADMIN_GROUP: widget = new AdministratorPage(); break;
    }

    QMap<int, QString> groupName = { {0, "Администратор"}, {1, "Регистратор"}, {2, "Врач"}, {3, "Пациент"} };

    ui->CurrentGroupLabel->setText(groupName[group]);
    ui->CurrentUserLabel->setText(AuthManager::Instance()->getFullName());

    ui->verticalLayout->addWidget(widget);
}

void MainWindow::saveData()
{
    try
    {
        QFile file("data.bin");

        file.open(QIODevice::WriteOnly);

        QDataStream stream(&file);

        Database::Instance()->save(stream);

        qDebug() << "Data saved to " << file.fileName();
    }
    catch (std::exception & ex)
    {
        qDebug() << "Failed to save data: " << ex.what();
    }
}

bool MainWindow::loadData()
{
    if(Utils::FileExists("data.bin"))
    {
        try
        {
            QFile file("data.bin");

            file.open(QIODevice::ReadOnly);

            QDataStream stream(&file);

            Database::Instance()->load(stream);

            qDebug() << "Data loaded from " << file.fileName();

            return true;
        }
        catch(std::exception & ex)
        {
            qDebug() << "Failed to load data: " << ex.what();
        }
    }

    qDebug() << "No saved data available";

    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    saveData();
}

void MainWindow::on_changePasswordAction_triggered()
{
    ChangePasswordDialog dialog;

    dialog.exec();
}

void MainWindow::on_aboutProgramAction_triggered()
{
    QMessageBox::information(this, "О программе", "Информационная система «Регистратура поликлиники»\n"
                                                  "Студент: Свиридов В.С.\n"
                                                  "Группа: КИ16-06Б\n"
                                                  "© 2018\n");
}
