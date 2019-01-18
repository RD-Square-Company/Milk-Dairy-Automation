#include "registrationcomplete.h"

RegistrationComplete::RegistrationComplete(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    //connections setup
    connect(okButton, SIGNAL(clicked(bool)),
            this, SLOT(okPressed()));
    connect(printButton, SIGNAL(clicked(bool)),
            this, SLOT(printPressed()));
}

void RegistrationComplete::setValue(QString custName, QString userName, QString userPass, QString custId, QString dairyName, QString type)
{
    custLabel->setText(tr("<html><p>New %1 <b><i>%2<i></b> added</p></html>").arg(type).arg(custName));
    usernameshowLabel->setText(tr("<html><p>%1</p></html>").arg(userName));
    passwordShowLabel->setText(tr("<html><p>%1</p></html>").arg(userPass));
    custIDShowLabel->setText(tr("<html><p>%1</p></html>").arg(custId));
    dairyNameLabel->setText(tr("<html><center><p>%1</p></center></html>").arg(dairyName));
    custIDLabel->setText(tr("<html><p><b>%1 ID No: </b></p></html>").arg(type));
}

void RegistrationComplete::closeEvent(QCloseEvent *)
{
    emit okBye();
}

void RegistrationComplete::okPressed()
{
    emit okBye();
}

void RegistrationComplete::printPressed()
{
    emit printSlip();
}
