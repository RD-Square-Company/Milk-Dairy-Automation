#-------------------------------------------------
#
# Project created by QtCreator 2018-07-06T14:52:55
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DairyProduct
TEMPLATE = app


SOURCES += main.cpp\
        productregistration.cpp\
        ../MyDetail/mydetail.cpp\
        ../MyDetail/graphicdetail.cpp\
        ../MyDetail/onlinedetail.cpp \
    productdetail.cpp

HEADERS  += productregistration.h\
        ../MyDetail/mydetail.h\
        ../MyDetail/graphicdetail.h\
        ../MyDetail/onlinedetail.h \
    productdetail.h

FORMS    += productregistration.ui\
        productdetail.ui

RESOURCES += \
        ../MyDetail/mydetail.qrc
