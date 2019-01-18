#-------------------------------------------------
#
# Project created by QtCreator 2018-03-27T13:49:09
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += sql
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EmployeeEdit
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


SOURCES += \
        main.cpp \
../CustomerRegistration/universalconst.cpp \
        employeeupdate.cpp\
../CustomerRegistration/smtp.cpp \
    epaymentupdate.cpp\
../MyDetail/graphicdetail.cpp\
../MyDetail/mydetail.cpp\
../MyDetail/onlinedetail.cpp \
    offlineempedit.cpp

HEADERS += \
        employeeupdate.h\
../CustomerRegistration/universalconst.h\
../CustomerRegistration/smtp.h \
    epaymentupdate.h\
../MyDetail/graphicdetail.h\
../MyDetail/mydetail.h\
../MyDetail/onlinedetail.h \
    offlineempedit.h

FORMS += \
        employeeupdate.ui\
../CustomerEdit/paymentupdate.ui

RESOURCES += \
../MyDetail/mydetail.qrc
