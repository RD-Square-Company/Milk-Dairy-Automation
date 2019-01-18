#include "payment.h"
#include <QDate>
#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>

Payment::Payment(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    //loading
    loadingLabel = new QLabel(this);
    loading = new QMovie(uc.loadImage1);
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //setting connections for widgets
    connect(acTypeBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(accountTypeChanged(int)) );
    connect(registerButton, SIGNAL(clicked(bool)),
            this, SLOT(regPressed()));
    connect(prevButton, SIGNAL(clicked(bool)),
            this, SLOT(prevPressed()));
    connect(exitButton, SIGNAL(clicked(bool)),
            this, SLOT(exitPressed()));
    //connection completed

    setWidgets();
}

void Payment::setWidgets()
{
    //setting stylesheet to all line edit

    noaEdit->setStyleSheet(uc.noError);
    aNumberEdit->setStyleSheet(uc.noError);
    bNameEdit->setStyleSheet(uc.noError);
    ifscEdit->setStyleSheet(uc.noError);
    bAddEdit->setStyleSheet(uc.noError);
    cvvEdit->setStyleSheet(uc.noError);

    //setting of stylesheet is done

    //setting validator for payment
    QRegExp nameExp("[A-Za-z\\s]{30}");
    QRegExpValidator *nameValidator = new QRegExpValidator(nameExp, this);
    noaEdit->setValidator(nameValidator);
    bNameEdit->setValidator(nameValidator);

    QRegExp accNumber("[0-9]{20}");
    QRegExpValidator *accValidator = new QRegExpValidator(accNumber, this);
    aNumberEdit->setValidator(accValidator);

    QRegExp ifscExp("[A-Za-z0-9]{20}");
    QRegExpValidator *ifscValidator = new QRegExpValidator(ifscExp, this);
    ifscEdit->setValidator(ifscValidator);

    QRegExp nameExp1("[A-Za-z0-9.,-'\\s]{50}");
    QRegExpValidator *nameValidator1 = new QRegExpValidator(nameExp1, this);
    bAddEdit->setValidator(nameValidator1);

    QRegExp cvvExp("[0-9]{3}");
    QRegExpValidator *cvvValidator = new QRegExpValidator(cvvExp, this);
    cvvEdit->setValidator(cvvValidator);

    //all validation are done

    //setting year range for Expire Date value
    int startyear = QDate::currentDate().year();
    int year;
    for (int i= 0; i<21; i++){
        year = startyear + i-2000;
        yearBox->addItem(tr("%1").arg(year));
    }
    //year setup has been done

    //changing index of account type to initial zero
    acTypeBox->currentIndexChanged(0);
}


void Payment::accountTypeChanged(int type)
{
    if(type == 0) {
        noaLabel->hide();
        noaEdit->hide();
        aNumberLabel->hide();
        aNumberEdit->hide();
        bNameLabel->hide();
        bNameEdit->hide();
        ifscLabel->hide();
        ifscEdit->hide();
        bAddLabel->hide();
        bAddEdit->hide();
        cvvLabel->hide();
        cvvEdit->hide();
        exDateLabel->hide();
        monthBox->hide();
        yearBox->hide();
        label_10->hide();
        errorLabel->hide();
    } else if (type == 1) {
        noaLabel->show();
        noaEdit->show();
        aNumberEdit->show();
        aNumberLabel->show();
        bNameLabel->show();
        bNameEdit->show();
        ifscLabel->show();
        ifscEdit->show();
        bAddLabel->show();
        bAddEdit->show();
        cvvLabel->hide();
        cvvEdit->hide();
        exDateLabel->hide();
        monthBox->hide();
        yearBox->hide();
        label_10->hide();
        errorLabel->show();
        noaLabel->setText(tr("<html><center><p align =\"left\" >Name on Account:   </p></center></html>"));
        aNumberLabel->setText(tr("<html><center><p align =\"left\" >Account Number:   </p></center></html>"));
    } else if (type == 2) {
        noaLabel->show();
        noaEdit->show();
        aNumberEdit->show();
        aNumberLabel->show();
        bNameLabel->show();
        bNameEdit->show();
        ifscLabel->hide();
        ifscEdit->hide();
        bAddLabel->hide();
        bAddEdit->hide();
        cvvLabel->show();
        cvvEdit->show();
        exDateLabel->show();
        monthBox->show();
        yearBox->show();
        label_10->show();
        errorLabel->show();
        noaLabel->setText(tr("<html><center><p align =\"left\" >Name on Debit Card:   </p></center></html>"));
        aNumberLabel->setText(tr("<html><center><p align =\"left\" >Debit Card Number:   </p></center></html>"));
    } else if(type == 3) {
        noaLabel->show();
        noaEdit->show();
        aNumberEdit->show();
        aNumberLabel->show();
        bNameLabel->hide();
        bNameEdit->hide();
        ifscLabel->hide();
        ifscEdit->hide();
        bAddLabel->hide();
        bAddEdit->hide();
        cvvLabel->hide();
        cvvEdit->hide();
        exDateLabel->show();
        monthBox->show();
        yearBox->show();
        label_10->show();
        errorLabel->show();
        noaLabel->setText(tr("<html><center><p align =\"left\" >Name on Credit Card:   </p></center></html>"));
        aNumberLabel->setText(tr("<html><center><p align =\"left\" >Credit Card Number:   </p></center></html>"));
    } else {
        noaLabel->show();
        noaEdit->show();
        aNumberEdit->show();
        aNumberLabel->show();
        bNameLabel->show();
        bNameEdit->show();
        ifscLabel->hide();
        ifscEdit->hide();
        bAddLabel->hide();
        bAddEdit->hide();
        cvvLabel->hide();
        cvvEdit->hide();
        exDateLabel->hide();
        monthBox->hide();
        yearBox->hide();
        label_10->hide();
        errorLabel->show();
        noaLabel->setText(tr("<html><center><p align =\"left\" >Name on UPI Account:   </p></center></html>"));
        aNumberLabel->setText(tr("<html><center><p align =\"left\" >UPI Number:   </p></center></html>"));
    }

    //set to default
    //set to default
    noaEdit->setText("");
    aNumberEdit->setText("");
    bNameEdit->setText("");
    ifscEdit->setText("");
    bAddEdit->setText("");
    cvvEdit->setText("");
    monthBox->setCurrentIndex(0);
    yearBox->setCurrentIndex(0);

}

void Payment::regPressed()
{
    QString error;

    if(acTypeBox->currentIndex() == 1) {
        if(bAddEdit->text().isEmpty()) {
            error = tr("Branch Address can not be empty");
            bAddEdit->setStyleSheet(uc.yesError);
        }
        if(ifscEdit->text().isEmpty()) {
            error = tr("IFSC Code can not be empty");
            ifscEdit->setStyleSheet(uc.yesError);
        }
        if(bNameEdit->text().isEmpty()){
            error = tr("Bank Name must required...Please fill it!");
            bNameEdit->setStyleSheet(uc.yesError);
        }
        if(aNumberEdit->text().isEmpty()) {
            error = tr("Enter account number Moron!");
            aNumberEdit->setStyleSheet(uc.yesError);
        }
        if(noaEdit->text().isEmpty()){
            error = tr("Please enter the name on the bank account");
            noaEdit->setStyleSheet(uc.yesError);
        }
    } else if(acTypeBox->currentIndex() == 2){
        if(monthBox->currentIndex() == 0 || yearBox->currentIndex() == 0) {
            error = tr("Please select month and year in Expire Date");
        }
        if(cvvEdit->text().count() != 3 || cvvEdit->text().isEmpty()) {
            error = tr("Enter valid CVV number");
            cvvEdit->setStyleSheet(uc.yesError);
        }
        if(bNameEdit->text().isEmpty()){
            error = tr("Bank Name must required...Please fill it!");
            bNameEdit->setStyleSheet(uc.yesError);
        }
        if(aNumberEdit->text().isEmpty()) {
            error = tr("Enter debit card number Moron!");
            aNumberEdit->setStyleSheet(uc.yesError);
        }
        if(noaEdit->text().isEmpty()){
            error = tr("Please enter the name on the debit card");
            noaEdit->setStyleSheet(uc.yesError);
        }
    } else if(acTypeBox->currentIndex() == 3) {
        if(monthBox->currentIndex() == 0 || yearBox->currentIndex() == 0) {
            error = tr("Please select month and year in Expire Date");
        }
        if(aNumberEdit->text().isEmpty()) {
            error = tr("Enter credit card number Moron!");
            aNumberEdit->setStyleSheet(uc.yesError);
        }
        if(noaEdit->text().isEmpty()){
            error = tr("Please enter the name on the credit card");
            noaEdit->setStyleSheet(uc.yesError);
        }
    }else if (acTypeBox->currentIndex() == 4) {
        if(bNameEdit->text().isEmpty()){
            error = tr("Bank Name must required...Please fill it!");
            bNameEdit->setStyleSheet(uc.yesError);
        }
        if(aNumberEdit->text().isEmpty()) {
            error = tr("Enter UPI number Moron!");
            aNumberEdit->setStyleSheet(uc.yesError);
        }
        if(noaEdit->text().isEmpty()){
            error = tr("Please enter the name on the UPI Account");
            noaEdit->setStyleSheet(uc.yesError);
        }
    }

    errorLabel->setText(tr("<html><p align=\"center\"><font size=\"5\" color=\"red\" >%1</font></p></html>").arg(error));
    if(error.isEmpty()){
        emit regByPay();
    }
}

void Payment::prevPressed()
{
    emit prevByPay();
}

void Payment::closeEvent(QCloseEvent *)
{
    emit quitByPay();
}

void Payment::exitPressed()
{
    emit quitByPay();
}

void Payment::rLoad(int i)
{
    if(i ==1){
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 - 64;
        loadingLabel->setGeometry(x, y, 128, 128);
        loadingLabel->show();
        loading->start();
        noaLabel->setEnabled(false);
        noaEdit->setEnabled(false);
        aNumberLabel->setEnabled(false);
        aNumberEdit->setEnabled(false);
        bNameLabel->setEnabled(false);
        bNameEdit->setEnabled(false);
        ifscLabel->setEnabled(false);
        ifscEdit->setEnabled(false);
        bAddLabel->setEnabled(false);
        bAddEdit->setEnabled(false);
        cvvLabel->setEnabled(false);
        cvvEdit->setEnabled(false);
        exDateLabel->setEnabled(false);
        monthBox->setEnabled(false);
        yearBox->setEnabled(false);
        label_10->setEnabled(false);
        errorLabel->setEnabled(false);
        registerButton->setEnabled(false);
        prevButton->setEnabled(false);
        exitButton->setEnabled(false);
        acTypeBox->setEnabled(false);
        acTypeLabel->setEnabled(false);
    } else {
        acTypeBox->setEnabled(true);
        acTypeLabel->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
        noaLabel->setEnabled(true);
        noaEdit->setEnabled(true);
        aNumberLabel->setEnabled(true);
        aNumberEdit->setEnabled(true);
        bNameLabel->setEnabled(true);
        bNameEdit->setEnabled(true);
        ifscLabel->setEnabled(true);
        ifscEdit->setEnabled(true);
        bAddLabel->setEnabled(true);
        bAddEdit->setEnabled(true);
        cvvLabel->setEnabled(true);
        cvvEdit->setEnabled(true);
        exDateLabel->setEnabled(true);
        monthBox->setEnabled(true);
        yearBox->setEnabled(true);
        label_10->setEnabled(true);
        errorLabel->setEnabled(true);
        registerButton->setEnabled(true);
        prevButton->setEnabled(true);
        exitButton->setEnabled(true);
    }
}

void Payment::setDefault()
{
    acTypeBox->setCurrentIndex(0);
    acTypeBox->currentIndexChanged(0);
    noaEdit->setText("");
    aNumberEdit->setText("");
    bNameEdit->setText("");
    ifscEdit->setText("");
    bAddEdit->setText("");
    cvvEdit->setText("");
    monthBox->setCurrentIndex(0);
    yearBox->setCurrentIndex(0);
    noaEdit->setStyleSheet(uc.noError);
    aNumberEdit->setStyleSheet(uc.noError);
    bNameEdit->setStyleSheet(uc.noError);
    ifscEdit->setStyleSheet(uc.noError);
    bAddEdit->setStyleSheet(uc.noError);
    cvvEdit->setStyleSheet(uc.noError);
}
