#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql
QT += printsupport
QT       += core gui charts
QT +=serialport

QT       += core gui sql printsupport
QT += core gui charts
QT += core gui multimedia multimediawidgets


QT       += core gui sql serialport

QT       += charts

QT += svg
QT       += core gui sql axcontainer printsupport network serialport multimedia multimediawidgets charts




QT       += core gui
QT       +=network
QT       +=sql
QT       +=printsupport axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

 QT += svg
QT       += core gui sql serialport
QT       += serialport
QT       += charts



TARGET = Atelier_Connexion
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

CONFIG += c++11

SOURCES += \
    dialog_mailing.cpp \
    dialog_statistiques.cpp \
    login.cpp \
    notification.cpp \
    qcustomplot2.cpp \
    reservation.cpp \
   smtp.cpp \
    arduino.cpp \
    client.cpp \
    employe.cpp \
    excel.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    qrcode.cpp \
    qrcodegeneratordemo.cpp \
    qrcodegenratorworker.cpp \
    qrwidget.cpp \
    smtp2.cpp \
    transport.cpp \
    voyage.cpp

HEADERS += \ \
    dialog_mailing.h \
    dialog_statistiques.h \
    login.h \
    notification.h \
    qcustomplot2.h \
    reservation.h \
    smtp.h \
    arduino.h \
    client.h \
    connection.h \
    employe.h \
    excel.h \
    exprtexel.h \
    mainwindow.h \
    qrcode.h \
    qrcodegenratorworker.h \
    qrwidget.h \
    smtp2.h \
    transport.h \
    voyage.h




FORMS += \
        dialog_mailing.ui \
        dialog_statistiques.ui \
        mainwindow.ui


QMAKE_CXXFLAGS += -std=gnu++14

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


