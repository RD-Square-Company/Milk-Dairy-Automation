#ifndef EMPLOYEEREGISTRATION_H
#define EMPLOYEEREGISTRATION_H

#include <QWidget>
#include "../CustomerRegistration/payment.h"
#include "eregistration.h"
#include "eregcomplete.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QGridLayout>
#include "../CustomerRegistration/universalconst.h"
#include <QStringList>

/*
 * EmployeeRegistration will handle
 * all the registration process of dairy employee like connecting
 * to  database, querying database
 * save to database
 *
 */

class EmployeeRegistration : public QWidget
{
    Q_OBJECT
public:
    EmployeeRegistration(QWidget *parent = nullptr);

signals:
    void sendDeptValues(QStringList deptValues);

private slots:
    void nextFromERF();
    void regFromPay();
    void prevFromPay();
    void quit();
    void bye();
    void completionMessage();
    void tempDBConnetion();

public slots:

private:
    bool connectDatabase();
    void disconnectDatabase();
    void registerEmployee();
    QString getDeptID();
    void sentMail(QString to, QString empName, QString deptName, QString designation, QString salary);

    Payment *paymentDialog;
    ERegistration *registrationDialog;
    ERegComplete *regCompDialog;
    QGridLayout *mainLayout;
    QSqlDatabase mydatabase;
    UniversalConst uc;
};

#endif // EMPLOYEEREGISTRATION_H
