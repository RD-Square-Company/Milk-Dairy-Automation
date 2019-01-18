#-------------------------------------------------
#
# Project created by QtCreator 2018-04-19T20:37:49
#
#-------------------------------------------------

QT       += core gui
QT        += sql
QT += network
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = MyDairyEdit
TEMPLATE = app


SOURCES += main.cpp\
        mydairyedit.cpp \
    mydairy.cpp\
    ../CustomerRegistration/universalconst.cpp \
    ../CustomerRegistration/smtp.cpp \
    dairyupdate.cpp \
    dairypicture.cpp \
    ownerupdate.cpp \
    paymentupdate.cpp \
    newdepartment.cpp \
    newhead.cpp \
    employeedepartment.cpp\
    ../MyDetail/graphicdetail.cpp\
    ../MyDetail/mydetail.cpp\
    ../MyDetail/onlinedetail.cpp \
    offlinedepregistration.cpp \
    ../EmployeeEdit/offlineempedit.cpp \
    newtransport.cpp \
    offlinetransport.cpp \
    transportedit.cpp

HEADERS  += mydairyedit.h \
    mydairy.h\
    ../CustomerRegistration/universalconst.h \
    ../CustomerRegistration/smtp.h \
    dairyupdate.h \
    dairypicture.h \
    ownerupdate.h \
    paymentupdate.h \
    newdepartment.h \
    newhead.h \
    employeedepartment.h\
    ../MyDetail/graphicdetail.h\
    ../MyDetail/mydetail.h\
    ../MyDetail/onlinedetail.h \
    offlinedepregistration.h \
    ../EmployeeEdit/offlineempedit.h \
    newtransport.h \
    offlinetransport.h \
    transportedit.h

FORMS    += dairyupdate.ui\
            mydairy.ui\
            mydairyedit.ui\
            dairypicture.ui\
            ownerupdate.ui\
            ../CustomerEdit/paymentupdate.ui\
            newdepartment.ui\
            newhead.ui\
            departmentedit.ui\
            newtransport.ui\
            transport.ui
RESOURCES +=\
    ../MyDetail/mydetail.qrc
