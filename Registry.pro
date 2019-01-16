#-------------------------------------------------
#
# Project created by QtCreator 2018-09-06T15:14:14
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Registry
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
        Forms\Windows\mainwindow.cpp \
    Forms/Dialogs/signindialog.cpp \
    Core/Managers/authmanager.cpp \
    Forms/Pages/patientpage.cpp \
    Core/Data/database.cpp \
    Forms/Pages/registratorpage.cpp \
    Forms/Pages/doctorpage.cpp \
    Forms/Pages/administratorpage.cpp \
    Forms/Dialogs/addeditpatient.cpp \
    Forms/Dialogs/addeditdoctor.cpp \
    Forms/Dialogs/addeditregistrator.cpp \
    Forms/Dialogs/addeditadmin.cpp \
    Forms/Dialogs/addeditappointment.cpp \
    Forms/Dialogs/addeditcardrecord.cpp \
    Forms/Dialogs/changepassworddialog.cpp

HEADERS += \
        Forms\Windows\mainwindow.hpp \
    Forms/Dialogs/signindialog.hpp \
    Core/Data/dbset.hpp \
    Core/Data/entitybase.hpp \
    Core/Data/database.hpp \
    Core/Data/Entities/identity.hpp \
    Core/Data/Entities/administrator.hpp \
    Core/Data/Entities/appointment.hpp \
    Core/Data/Entities/doctor.hpp \
    Core/Data/Entities/group.hpp \
    Core/Data/Entities/medicalcard.hpp \
    Core/Data/Entities/patient.hpp \
    Core/Data/Entities/registrator.hpp \
    Core/Data/Entities/user.hpp \
    Core/utils.h \
    Core/Managers/authmanager.hpp \
    Core/bootstrap.h \
    Forms/Pages/patientpage.hpp \
    Forms/Pages/registratorpage.hpp \
    Forms/Pages/doctorpage.hpp \
    Forms/Pages/administratorpage.hpp \
    Forms/Dialogs/addeditpatient.hpp \
    Forms/Dialogs/addeditdoctor.hpp \
    Forms/Dialogs/addeditregistrator.hpp \
    Forms/Dialogs/addeditadmin.hpp \
    Core/Managers/usermanager.h \
    Forms/Dialogs/addeditappointment.hpp \
    Forms/Dialogs/addeditcardrecord.hpp \
    Forms/Dialogs/changepassworddialog.hpp

FORMS += \
        Forms\Windows\mainwindow.ui \
    Forms/Dialogs/signindialog.ui \
    Forms/Pages/patientpage.ui \
    Forms/Pages/registratorpage.ui \
    Forms/Pages/doctorpage.ui \
    Forms/Pages/administratorpage.ui \
    Forms/Dialogs/addeditpatient.ui \
    Forms/Dialogs/addeditdoctor.ui \
    Forms/Dialogs/addeditregistrator.ui \
    Forms/Dialogs/addeditadmin.ui \
    Forms/Dialogs/addeditappointment.ui \
    Forms/Dialogs/addeditcardrecord.ui \
    Forms/Dialogs/changepassworddialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Forms/Icons/app.svg

RESOURCES += \
    icons.qrc
