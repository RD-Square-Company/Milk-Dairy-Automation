#-------------------------------------------------
#
# Project created by QtCreator 2018-03-24T03:56:49
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HigherBranchRegistration
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
        sendrequest.cpp\
../CustomerRegistration/universalconst.cpp \
../CustomerRegistration/smtp.cpp\
../LocalBranchRegistration/mysqlquery.cpp\
../LocalBranchRegistration/picloadingdelegate.cpp \
    acceptproposal.cpp\
../LocalBranchRegistration/sqlquerymodel.cpp\
../LocalBranchRegistration/picload.cpp \
    higherbranchregistration.cpp\
../MyDetail/graphicdetail.cpp\
../MyDetail/mydetail.cpp\
../MyDetail/onlinedetail.cpp\
../MyDetail/higherbranch.cpp

HEADERS += \
        sendrequest.h\
../CustomerRegistration/universalconst.h\
../CustomerRegistration/smtp.h\
../LocalBranchRegistration/mysqlquery.h\
../LocalBranchRegistration/picloadingdelegate.h \
    acceptproposal.h\
../LocalBranchRegistration/sqlquerymodel.h\
../LocalBranchRegistration/picload.h \
    higherbranchregistration.h\
../MyDetail/graphicdetail.h\
../MyDetail/mydetail.h\
../MyDetail/onlinedetail.h\
../MyDetail/higherbranch.h

FORMS += \
        sendrequest.ui\
../LocalBranchRegistration/sendproposal.ui\
         acceptproposal.ui

RESOURCES += \
../MyDetail/mydetail.qrc
