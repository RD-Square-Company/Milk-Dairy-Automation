#include "eregistration.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QDate>

ERegistration::ERegistration(QWidget *parent)
    : QDialog(parent)
{
    //setting ui to the ERegistration
    setupUi(this);

    //setting set variable for department box
    setDept = 0;

    //connections of ERegistration
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    connect(showButton, SIGNAL(clicked(bool)),
            this, SLOT(showPressed()));
    connect(prevButton, SIGNAL(clicked(bool)),
            this, SLOT(prevPressed()));
    connect(nextButton, SIGNAL(clicked(bool)),
            this, SLOT(nextPressed()));
    //connections of ERegistration is compeleted

    //hiding gender label and buttons
    genderLabel->hide();
    maleButton->hide();
    femaleButton->hide();

    setWidgets();
}

void ERegistration::setWidgets()
{
    //setting stylesheet for general information line edit
    firstNameEdit->setStyleSheet(uc.noError);
    middleNameEdit->setStyleSheet(uc.noError);
    lastNameEdit->setStyleSheet(uc.noError);
    ad1Edit->setStyleSheet(uc.noError);
    ad2Edit->setStyleSheet(uc.noError);
    ad3Edit->setStyleSheet(uc.noError);
    pContactEdit->setStyleSheet(uc.noError);
    sContactEdit->setStyleSheet(uc.noError);
    emailEdit->setStyleSheet(uc.noError);
    line1Edit->setStyleSheet(uc.noError);
    line2Edit->setStyleSheet(uc.noError);
    pincodeEdit->setStyleSheet(uc.noError);
    //setting of stylesheet is completed for general information

    //setting stylesheet for office information line edit
    designationEdit->setStyleSheet(uc.noError);
    salaryEdit->setStyleSheet(uc.noError);
    //setting of stylesheet for office information line edit is completed

    //setting validator for line edit of general information
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

    QRegExp contactRegExp("[0-9]{10,13}");
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
    //setting of validator of general information is compeleted

    //setting of  validator for office information
    QRegExp designationExp("[A-Za-z-,\\s]{50}");
    QRegExpValidator *designationValidator = new QRegExpValidator(designationExp, this);
    designationEdit->setValidator(designationValidator);

    QRegExp salaryExp("[0-9]{1,7}[.]{1}[0-9]{2}");
    QRegExpValidator *salaryValidator = new QRegExpValidator(salaryExp, this);
    salaryEdit->setValidator(salaryValidator);

    /*********
     *
     * set minimum date to establish date of dairy
     *
     */
    dojEdit->setDate(QDate::currentDate());
    dojEdit->setMaximumDate(QDate::currentDate());
    
    

    //hiding office information box and messages
    officeBox->hide();
    e1rrorLabel->hide();
}

void ERegistration::closeEvent(QCloseEvent *)
{
    closeByER();
}

void ERegistration::setDefault()
{
    //setting stylesheet for general information line edit
    firstNameEdit->setStyleSheet(uc.noError);
    middleNameEdit->setStyleSheet(uc.noError);
    lastNameEdit->setStyleSheet(uc.noError);
    ad1Edit->setStyleSheet(uc.noError);
    ad2Edit->setStyleSheet(uc.noError);
    ad3Edit->setStyleSheet(uc.noError);
    pContactEdit->setStyleSheet(uc.noError);
    sContactEdit->setStyleSheet(uc.noError);
    emailEdit->setStyleSheet(uc.noError);
    line1Edit->setStyleSheet(uc.noError);
    line2Edit->setStyleSheet(uc.noError);
    pincodeEdit->setStyleSheet(uc.noError);
    //setting of stylesheet is completed for general information

    //setting stylesheet for office information line edit
    designationEdit->setStyleSheet(uc.noError);
    salaryEdit->setStyleSheet(uc.noError);
    //setting of stylesheet for office information line edit is completed

    //set values to default
    //general info box
    firstNameEdit->setText("");
    middleNameEdit->setText("");
    lastNameEdit->setText("");
    ad1Edit->setText("");
    ad3Edit->setText("");
    ad2Edit->setText("");
    pContactEdit->setText("");
    sContactEdit->setText("");
    emailEdit->setText("");
    line1Edit->setText("");
    line2Edit->setText("");
    pincodeEdit->setText("");
    dobEdit->setDate(QDate(2000, 01,01));
    stateBox->setCurrentIndex(0);

    firstNameEdit->setEnabled(true);
    middleNameEdit->setEnabled(true);
    lastNameEdit->setEnabled(true);
    ad1Edit->setEnabled(true);
    ad3Edit->setEnabled(true);
    ad2Edit->setEnabled(true);
    pContactEdit->setEnabled(true);
    sContactEdit->setEnabled(true);
    emailEdit->setEnabled(true);
    line1Edit->setEnabled(true);
    line2Edit->setEnabled(true);
    pincodeEdit->setEnabled(true);
    dobEdit->setEnabled(true);
    stateBox->setEnabled(true);
    //show buttons of general information box
    cancelButton->show();
    showButton->show();

    //office info box
    designationEdit->setText("");
    salaryEdit->setText("");
    departmentBox->setCurrentIndex(0);
    hQBox->setCurrentIndex(0);
    //hide office box
    officeBox->hide();
}

void ERegistration::cancelPressed()
{
    closeByER();
}

bool ERegistration::checkGeneralInfo()
{
    QString error;
    if(pincodeEdit->text().isEmpty() || pincodeEdit->text().count() < 6) {
        error = tr("Pincode must be 6 digit number");
        pincodeEdit->setStyleSheet(uc.yesError);
    }
    if(stateBox->currentIndex() == 0) {
        error = tr("please select any state");
    }
    if(line1Edit->text().isEmpty() || line2Edit->text().isEmpty()) {
        error = tr("Please enter your address to address line");
        line1Edit->setStyleSheet(uc.yesError);
        line2Edit->setStyleSheet(uc.yesError);
    }

    if(! (emailEdit->text().isEmpty())) {
        if(!(emailEdit->text().contains('@')) || !(emailEdit->text().contains(".com"))){
            error = tr("Please enter valid email ID");
            emailEdit->setStyleSheet(uc.yesError);
        }
        if(emailEdit->text().count('@') > 1 || emailEdit->text().count('.') > 1) {
            error = tr("Please enter valid email ID");
            emailEdit->setStyleSheet(uc.yesError);
    }
    }
    if(!sContactEdit->text().isEmpty()){
        if (sContactEdit->text().count() != 10 && sContactEdit->text().count() != 13){
            error = tr("Enter valid mob no & not use 0 at starting");
            sContactEdit->setStyleSheet(uc.yesError);
        }
    }
    if((pContactEdit->text().count() != 10 && pContactEdit->text().count() != 13) || pContactEdit->text().isEmpty()){
        error = tr("Please enter any valid mob no");
        pContactEdit->setStyleSheet(uc.yesError);
    }
    if(ad1Edit->text().isEmpty() || ad1Edit->text().count() != 4) {
        error = tr("Please enter valid adhar card no");
        ad1Edit->setStyleSheet(uc.yesError);
    }
    if(ad2Edit->text().isEmpty() || ad2Edit->text().count() != 4) {
         error = tr("Please enter valid adhar card no");
         ad2Edit->setStyleSheet(uc.yesError);
    }
    if(ad3Edit->text().isEmpty() || ad3Edit->text().count() != 4) {
         error = tr("Please enter valid adhar card no");
         ad3Edit->setStyleSheet(uc.yesError);
    }
    if(firstNameEdit->text().isEmpty()) {
        error = tr("First name can not be empty");
        firstNameEdit->setStyleSheet(uc.yesError);
    }

    if(error.isEmpty()){
        e1rrorLabel->hide();
        return true;
    }else {
        e1rrorLabel->setText(tr("<html><p align=\"center\"><font color=\"red\" size=\"5\">%1</font></p></html>").arg(error));
        e1rrorLabel->show();
        return false;
    }
}

bool ERegistration::checkOfficeInfo()
{
    QString error;

    if(hQBox->currentIndex() == 0){
        error = tr("You must have to select highest qualification of employee");
    }
    if(salaryEdit->text().isEmpty()) {
        error = tr("You must have to give salary to your Employees");
        salaryEdit->setStyleSheet(uc.yesError);
    }
    if(designationEdit->text().isEmpty()){
        error = tr("You must have give designation of particular employee");
        designationEdit->setStyleSheet(uc.yesError);
    }

    if(!error.isEmpty()){
        e2rrorLabel->setText(tr("<html><p align=\"center\"><font color=\"red\" size=\"5\">%1</font></p></html>").arg(error));
        e2rrorLabel->show();
        return false;
    }
    return true;
}

void ERegistration::showPressed()
{
    if(checkGeneralInfo()){
        if(setDept == 0){
            //set connection to database and get value for departments
                setDept = 1;
                setConnection();
        }
        showOfficeBox();
    }
}

void ERegistration::showOfficeBox()
{
        //disable edits of general information box
        firstNameEdit->setEnabled(false);
        middleNameEdit->setEnabled(false);
        lastNameEdit->setEnabled(false);
        pContactEdit->setEnabled(false);
        sContactEdit->setEnabled(false);
        emailEdit->setEnabled(false);
        ad1Edit->setEnabled(false);
        ad2Edit->setEnabled(false);
        ad3Edit->setEnabled(false);
        line1Edit->setEnabled(false);
        line2Edit->setEnabled(false);
        pincodeEdit->setEnabled(false);
        stateBox->setEnabled(false);
        dobEdit->setEnabled(false);

        //hide buttons of general information box
        showButton->hide();
        cancelButton->hide();

        //show official information box
        officeBox->show();
        e2rrorLabel->hide();
}

void ERegistration::getDeptValues(QStringList depNames)
{
    if(depNames.count() > 1){
        for(int item= 0; item<departmentBox->count(); item++) {
            departmentBox->removeItem(0); //remove first item every time as next item will be first after deleting first item
        }

        for(int item = 0; item < depNames.count(); item++){
            departmentBox->addItem(depNames.at(item));
        }
        showOfficeBox();
    } else if (depNames.count() == 1){
        for(int item= 0; item<departmentBox->count(); item++) {
            departmentBox->removeItem(0); //remove first item every time as next item will be first after deleting first item
        }

        departmentBox->addItem(depNames.at(0));
        showOfficeBox();
    }
}

void ERegistration::prevPressed()
{
    //hide all office box items
    officeBox->hide();

    //set all general information box elements to enabled mode
    firstNameEdit->setEnabled(true);
    middleNameEdit->setEnabled(true);
    lastNameEdit->setEnabled(true);
    pContactEdit->setEnabled(true);
    sContactEdit->setEnabled(true);
    emailEdit->setEnabled(true);
    ad1Edit->setEnabled(true);
    ad2Edit->setEnabled(true);
    ad3Edit->setEnabled(true);
    line1Edit->setEnabled(true);
    line2Edit->setEnabled(true);
    pincodeEdit->setEnabled(true);
    stateBox->setEnabled(true);
    dobEdit->setEnabled(true);
    //all general informationn box elements are set to enabled mode

    //show buttons of general information box
    showButton->show();
    cancelButton->show();
}

void ERegistration::nextPressed()
{
    if(checkOfficeInfo())
        nextByER();
}
