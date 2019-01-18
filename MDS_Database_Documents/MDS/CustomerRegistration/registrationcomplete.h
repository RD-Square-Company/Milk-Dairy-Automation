#ifndef REGISTRATIONCOMPLETE_H
#define REGISTRATIONCOMPLETE_H

#include <QDialog>
#include "ui_registrationcomplete.h"

/*
 * It will show the username, password and dairyuserID
 * to the customer
 *
*/

class RegistrationComplete : public QDialog, Ui::RegistrationComplete
{
    Q_OBJECT
public:
    RegistrationComplete(QWidget *parent = nullptr);
    void setValue(QString custName, QString userName, QString userPass, QString custId, QString dairyName, QString type);
    void closeEvent(QCloseEvent *);

private slots:
    void printPressed();
    void okPressed();

signals:
    void printSlip();
    void okBye();
};

#endif // REGISTRATIONCOMPLETE_H
