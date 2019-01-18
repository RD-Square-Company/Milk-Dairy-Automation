#include "registration.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>

Registration::Registration(QString title, QWidget *parent):
    QDialog(parent)
{
    setupUi(this);

    //setting connections
    connect(nextButton, SIGNAL(clicked(bool)),
            this, SLOT(nextPressed()) );
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    //connections are set

    //hide gender label and radio buttons
    genderLabel->hide();
    maleButton->hide();
    femaleButton->hide();

    setWidgets(title);
}

void Registration::setWidgets(QString title)
{
    //setting title text
    label->setText(tr("<html><center><p>%1 Registration Form</p></center></html>").arg(title));
    //setting title text completed

    //setting stylesheet for all line edit
    firstNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    middleNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    lastNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    ad1Edit->setStyleSheet(gDetail.getNormalStylesheet());
    ad2Edit->setStyleSheet(gDetail.getNormalStylesheet());
    ad3Edit->setStyleSheet(gDetail.getNormalStylesheet());
    pContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    sContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    emailEdit->setStyleSheet(gDetail.getNormalStylesheet());
    line1Edit->setStyleSheet(gDetail.getNormalStylesheet());
    line2Edit->setStyleSheet(gDetail.getNormalStylesheet());
    pincodeEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //setting of stylesheet is completed

    //setting validator for line edit
    QRegExp nameRegExp("[A-Za-z]{20}");
    QRegExpValidator *nameValidator = new QRegExpValidator(nameRegExp, this);
    firstNameEdit->setValidator(nameValidator);
    middleNameEdit->setValidator(nameValidator);
    lastNameEdit->setValidator(nameValidator);

    QRegExp adharRegExp("[0-9]{4}");
    QRegExpValidator *adharValidator = new QRegExpValidator(adharRegExp, this);
    ad1Edit->setValidator(adharValidator);
    ad2Edit->setValidator(adharValidator);
    ad3Edit->setValidator(adharValidator);

    QRegExp contactRegExp("[0-9]{10}");
    QRegExpValidator *contactValidator = new QRegExpValidator(contactRegExp, this);
    pContactEdit->setValidator(contactValidator);
    sContactEdit->setValidator(contactValidator);

    QRegExp emailRegExp("[A-Za-z0-9@.]{10,50}");
    QRegExpValidator *emailValidator = new QRegExpValidator(emailRegExp, this);
    emailEdit->setValidator(emailValidator);

    QRegExp pincodeExp("[0-9]{6}");
    QRegExpValidator *pincodeValidator = new QRegExpValidator(pincodeExp, this);
    pincodeEdit->setValidator(pincodeValidator);

    QRegExp streetExp("[A-Za-z-.*'\\s0-9]{40}");
    QRegExpValidator *streetValidator = new QRegExpValidator(streetExp, this);
    line1Edit->setValidator(streetValidator);

    QRegExp cityExp("[A-Za-z\\s]{20}");
    QRegExpValidator *cityValidator = new QRegExpValidator(cityExp, this);
    line2Edit->setValidator(cityValidator);

   //setting of all validator is completed
}

void Registration::nextPressed()
{
    QString error;
    if(pincodeEdit->text().isEmpty() || pincodeEdit->text().count() < 6) {
        error = tr("Pincode must be 6 digit number");
        pincodeEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(stateBox->currentIndex() == 0) {
        error = tr("please select any state");
    }
    if(line1Edit->text().isEmpty() || line2Edit->text().isEmpty()) {
        error = tr("Please enter your address to address line");
        line1Edit->setStyleSheet(gDetail.getErrorStylesheet());
        line2Edit->setStyleSheet(gDetail.getErrorStylesheet());
    }

    if(! (emailEdit->text().isEmpty())) {
        if(!(emailEdit->text().contains('@')) || !(emailEdit->text().contains(".com"))){
            error = tr("Please enter valid email ID");
            emailEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(emailEdit->text().count('@') > 1 || emailEdit->text().count('.') > 1) {
            error = tr("Please enter valid email ID");
            emailEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    }
    if(!sContactEdit->text().isEmpty()){
        if (sContactEdit->text().count() != 10){
            error = tr("Enter valid mob no & not use 0 at starting");
            sContactEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    }
    if((pContactEdit->text().count() != 10) || pContactEdit->text().isEmpty()){
        error = tr("Please enter any valid mob no");
        pContactEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(ad1Edit->text().isEmpty() || ad1Edit->text().count() != 4) {
        error = tr("Please enter valid adhar card no");
        ad1Edit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(ad2Edit->text().isEmpty() || ad2Edit->text().count() != 4) {
         error = tr("Please enter valid adhar card no");
         ad2Edit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(ad3Edit->text().isEmpty() || ad3Edit->text().count() != 4) {
         error = tr("Please enter valid adhar card no");
         ad3Edit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(firstNameEdit->text().isEmpty()) {
        error = tr("First name can not be empty");
        firstNameEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }

    errorLabel->setText(tr("<html><p align=\"center\"><font color=\"red\" size=\"5\">%1</font></p></html>").arg(error));

    if(error.isEmpty()){
        emit nextByCRF();
    }
}

void Registration::cancelPressed()
{
    emit cancelByCRF();
}

void Registration::closeEvent(QCloseEvent *)
{
    emit cancelByCRF();
}

void Registration::setDefault()
{
    firstNameEdit->setText("");
    middleNameEdit->setText("");
    lastNameEdit->setText("");
    ad1Edit->setText("");
    ad2Edit->setText("");
    ad3Edit->setText("");
    pincodeEdit->setText("");
    pContactEdit->setText("");
    sContactEdit->setText("");
    emailEdit->setText("");
    line1Edit->setText("");
    line2Edit->setText("");
    stateBox->setCurrentIndex(0);
    androidBox->setCurrentIndex(0);
    firstNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    middleNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    lastNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    ad1Edit->setStyleSheet(gDetail.getNormalStylesheet());
    ad2Edit->setStyleSheet(gDetail.getNormalStylesheet());
    ad3Edit->setStyleSheet(gDetail.getNormalStylesheet());
    pContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    sContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    emailEdit->setStyleSheet(gDetail.getNormalStylesheet());
    line1Edit->setStyleSheet(gDetail.getNormalStylesheet());
    line2Edit->setStyleSheet(gDetail.getNormalStylesheet());
    pincodeEdit->setStyleSheet(gDetail.getNormalStylesheet());
}
