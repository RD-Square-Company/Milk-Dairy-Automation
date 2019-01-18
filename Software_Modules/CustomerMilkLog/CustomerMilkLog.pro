#-------------------------------------------------
#
# Project created by QtCreator 2018-07-28T08:07:33
#
#-------------------------------------------------

QT       += core gui
QT += xml
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CustomerMilkLog
TEMPLATE = app


SOURCES += main.cpp\
        customermilklog.cpp\
        ../AdditionalCustomer/additionalcustomer.cpp\
        ../MyDetail/mydetail.cpp\
        ../MyDetail/onlinedetail.cpp\
        ../MyDetail/graphicdetail.cpp \
        ../AdditionalCustomer/customerofflineentry.cpp\
        ../CustomerRegistration/offlinecustregistration.cpp \
    offlinecustomerlog.cpp \
    message.cpp \
    syncmilklog.cpp

HEADERS  += customermilklog.h\
        ../AdditionalCustomer/additionalcustomer.h\
        ../MyDetail/mydetail.h\
        ../MyDetail/onlinedetail.h\
        ../MyDetail/graphicdetail.h \
        ../AdditionalCustomer/customerofflineentry.h\
        ../CustomerRegistration/offlinecustregistration.h \
    offlinecustomerlog.h \
    message.h \
    syncmilklog.h

FORMS    += customermilklog.ui\
        ../AdditionalCustomer/additionalcustomer.ui \
        message.ui \
        syncmilklog.ui

RESOURCES += \
    customermilklog.qrc\
    ../MyDetail/mydetail.qrc
