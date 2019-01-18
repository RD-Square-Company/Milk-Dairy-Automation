#-------------------------------------------------
#
# Project created by QtCreator 2018-07-25T21:23:05
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += network
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AdditionalCustomer
TEMPLATE = app


SOURCES += main.cpp\
        additionalcustomer.cpp\
        ../MyDetail/mydetail.cpp\
        ../MyDetail/onlinedetail.cpp\
        ../MyDetail/graphicdetail.cpp \
        customerofflineentry.cpp

HEADERS  += additionalcustomer.h\
        ../MyDetail/mydetail.h\
        ../MyDetail/onlinedetail.h\
        ../MyDetail/graphicdetail.h \
        customerofflineentry.h

FORMS    += additionalcustomer.ui
