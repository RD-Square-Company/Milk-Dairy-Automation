#include "eregcomplete.h"

ERegComplete::ERegComplete(QWidget *parent)
    : QDialog (parent)
{
    setupUi(this);

    //connection setup
    connect(okButton, SIGNAL(clicked(bool)),
            this, SLOT(okPressed()));
}

void ERegComplete::setValue(QString empName, QString deptName, QString designation, QString dairyName)
{
    nameSLabel->setText(tr("<html><p>%1</p></html>").arg(empName));
    deptSLabel->setText(tr("<html><p>%1</p></html>").arg(deptName));
    desgSLabel->setText(tr("<html><p>%1</p></html>").arg(designation));
    dairyNameLabel->setText(tr("<html><center><p>%1</p></center></html>").arg(dairyName));
}

void ERegComplete::closeEvent(QCloseEvent *)
{
    emit okBye();
}

void ERegComplete::okPressed()
{
    emit okBye();
}
