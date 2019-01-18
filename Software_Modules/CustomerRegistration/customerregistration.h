#ifndef CUSTOMERREGISTRATION_H
#define CUSTOMERREGISTRATION_H

#include <QWidget>
#include "payment.h"
#include "registration.h"
#include "registrationcomplete.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QGridLayout>
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "offlinecustregistration.h"

/*
 * CustomerRegistration will handle
 * all the registration processes like connecting to database
 * querying database
 * generating username and password etc.
 *
*/

class CustomerRegistration : public QWidget
{
    Q_OBJECT
public:
    CustomerRegistration(QString type, QWidget *parent = 0);

private slots:
    void nextFromCRF();
    void regFromPay();
    void prevFromPay();
    void quit();
    void bye();
    void printSlip();
    void completionMessage();

public slots:

private:
    bool connectDatabase();
    void disconnectDatabase();
    bool generateCustId();
    void generateCustPass();
    void generateUserName();
    bool saveData();
    void sentMail(QString to, QString custName);

    Payment *paymentDialog;
    Registration *registrationDialog;
    RegistrationComplete *regCompDialog;
    QGridLayout *mainLayout;
    QSqlDatabase mydatabase;
    QString userName;
    QString userPass;
    QString custDairyID;
    QString type;
    QString highCustIDBack;
    MyDetail mDetail;
    OnlineDetail oDetail;
    QString bID;
};


#endif // CUSTOMERREGISTRATION_H
