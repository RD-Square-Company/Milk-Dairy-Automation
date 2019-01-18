#include "additionalcustomer.h"
#include "customerofflineentry.h"
#include <QRegExp>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QDateTime>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QPen>

AdditionalCustomer::AdditionalCustomer(QString date, int shift, QWidget *parent)
    : QWidget(parent)
{
    //setting personals
    setupUi(this);
    this->date = date;
    this->shift = QString::number(shift);

    //setting connections
    connect(addBox, SIGNAL(clicked(bool)),
            this, SLOT(billChecked(bool)));
    connect(pBillBox, SIGNAL(clicked(bool)),
            this, SLOT(printBill(bool)));
    connect(SubmitButton, SIGNAL(clicked(bool)),
           this, SLOT(submitPressed()));
    connect(mobEdit, SIGNAL(textChanged(QString)),
            this, SLOT(changingText()));
    connect(nameEdit, SIGNAL(textChanged(QString)),
            this, SLOT(nameTextChanged()));

    //connecting temporarily requireMilkPrice() to gotMilkPrice()
    connect(this, SIGNAL(requireMilkPrice(int)),
            this, SLOT(gotMilkPrice()));
    //all connections are done

    setWidgets();
}

void AdditionalCustomer::setWidgets()
{
    //setting stylesheet to line edit
    nameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    quantityEdit->setStyleSheet(gDetail.getNormalStylesheet());
    mobEdit->setStyleSheet(gDetail.getNormalStylesheet());

    //setting validator to line edit
    QRegExp nameRegExp("[A-Za-z]{1,10}[ ]{1}[A-Za-z]{1,10}[ ]{1}[A-Za-z]{10}");
    QRegExpValidator *nameValidator = new QRegExpValidator(nameRegExp, this);
    nameEdit->setValidator(nameValidator);

    QRegExp priceExp("[0-9]{1,5}[.][0-9]{2}");
    QRegExpValidator *priceValidator = new QRegExpValidator(priceExp, this);
    quantityEdit->setValidator(priceValidator);

    QRegExp mobileExp("[0-9]{10}");
    QRegExpValidator *mobileValidator = new QRegExpValidator(mobileExp, this);
    mobEdit->setValidator(mobileValidator);

    //setting billchecked to non selected
    billChecked(false);
    animalTypeBox->setCurrentIndex(3);
}

void AdditionalCustomer::billChecked(bool clicked)
{
    if(clicked){
        nameLabel->show();
        nameEdit->show();
        mobEdit->show();
        mobLabel->show();
        pBillBox->setChecked(true);
        pBillBox->show();
        pBillBox->setEnabled(false);
    } else {
        nameLabel->hide();
        nameEdit->hide();
        mobEdit->hide();
        mobLabel->hide();
        pBillBox->hide();
    }
}

void AdditionalCustomer::printBill(bool clicked)
{
    //empty for now
}

void AdditionalCustomer::submitPressed()
{
    //disabling all the activities
    SubmitButton->setEnabled(false);
    addBox->setEnabled(false);
    pBillBox->setEnabled(false);
    nameEdit->setEnabled(false);
    quantityEdit->setEnabled(false);
    mobEdit->setEnabled(false);
    animalTypeBox->setEnabled(false);

    QString error;
    if(quantityEdit->text().isEmpty()){
        error = tr("Please ener valid quantity of milk.");
        quantityEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if((!mobEdit->text().isEmpty())  && addBox->isChecked()){
        if(mobEdit->text().length() != 10){
            error = tr("Please enter valid mobile number.");
            mobEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    }
    if(addBox->isChecked()){
        if(nameEdit->text().isEmpty()) {
            error = tr("Please enter name of customer.");
            nameEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    }

    if (!error.isEmpty()){
        QMessageBox::information(this, tr("Data Error! - %1").arg(qApp->applicationName()),
                                 tr("<html><p><h3>Error Encountered!</h3></p><p>"
                                    "%1 - Please make it correct.</p>").arg(error),
                                 QMessageBox::Ok|QMessageBox::Default);
        //enabling all the activities
        SubmitButton->setEnabled(true);
        addBox->setEnabled(true);
        pBillBox->setEnabled(true);
        nameEdit->setEnabled(true);
        quantityEdit->setEnabled(true);
        mobEdit->setEnabled(true);
        animalTypeBox->setEnabled(true);
        return ;
    }

    if(!saveOfflineData()){
        QMessageBox::critical(this,tr("File Error! - %1").arg(qApp->applicationName()),
                              tr("<html><p><h3>Critical Data Error!:</h3></p><p>"
                                 "Your software has encountered serious data problem.</p>"
                                 "<p>Please contact our help line number otherwise your data will not be saved now and after.</p></html>"),
                              QMessageBox::Ok|QMessageBox::Default);
        //enabling all the activities
        SubmitButton->setEnabled(true);
        addBox->setEnabled(true);
        pBillBox->setEnabled(true);
        nameEdit->setEnabled(true);
        quantityEdit->setEnabled(true);
        mobEdit->setEnabled(true);
        animalTypeBox->setEnabled(true);
        return;
    }

    //enabling all the activities
    SubmitButton->setEnabled(true);
    addBox->setEnabled(true);
    pBillBox->setEnabled(true);
    nameEdit->setEnabled(true);
    quantityEdit->setEnabled(true);
    mobEdit->setEnabled(true);
    animalTypeBox->setEnabled(true);

    nameEdit->setText("");
    quantityEdit->setText("");
    mobEdit->setText("");
    emit hideThis();
}

bool AdditionalCustomer::saveOfflineData()
{
    if(addBox->isChecked()){
        if(!CustomerOfflineEntry::saveTempCustomer(mobEdit->text(), nameEdit->text())) return false;
        if(!CustomerOfflineEntry::saveCustomer(mobEdit->text(),nameEdit->text())) return false;
        QString isKg;
        if(kgButton->isChecked())
            isKg = "1";
        else
            isKg = "0";
        gotPrice = false;
        emit requireMilkPrice(animalTypeBox->currentIndex());
        checkAgain:
        if(!gotPrice)
            goto checkAgain;
        if(!CustomerOfflineEntry::saveTempCustLog(mobEdit->text(),this->date,QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"),
                                                  this->shift,animalTypeBox->currentText(), quantityEdit->text(),QString::number(this->price) ,isKg))
            return false;
        if(!CustomerOfflineEntry::saveCustLog(mobEdit->text(),this->date,QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"),
                                              this->shift,animalTypeBox->currentText(), quantityEdit->text(),QString::number(this->price) ,isKg))
            return false;
        return true;
    } else {
        QString isKg;
        if(kgButton->isChecked())
            isKg = "1";
        else
            isKg = "0";
        gotPrice = false;
        emit requireMilkPrice(animalTypeBox->currentIndex());
        reCheckAgain:
        if(!gotPrice)
            goto reCheckAgain;
        if(!CustomerOfflineEntry::saveTempCustLog("DEFAULT",this->date,QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"),
                                                  this->shift,animalTypeBox->currentText(), quantityEdit->text(),QString::number(this->price) ,isKg))
            return false;
        if(!CustomerOfflineEntry::saveCustLog("DEFAULT",this->date,QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"),
                                              this->shift,animalTypeBox->currentText(), quantityEdit->text(),QString::number(this->price) ,isKg))
            return false;
        return true;
    }
}

void AdditionalCustomer::changingText()
{
    if(mobEdit->text().isEmpty()){
        pBillBox->setChecked(true);
        pBillBox->setEnabled(false);
    } else {
        pBillBox->setChecked(false);
        pBillBox->setEnabled(true);
    }
}

void AdditionalCustomer::nameTextChanged()
{
    nameEdit->setText(nameEdit->text().toUpper());
}

void AdditionalCustomer::gotMilkPrice()
{
    this->price = 35.00;
    gotPrice = true;
}

void AdditionalCustomer::dateChanged(QDate date)
{
    this->date = date.toString("yyyy-MM-dd");
}

void AdditionalCustomer::shiftChanged(int shift)
{
    this->shift = shift;
}

void AdditionalCustomer::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter p(this);
    p.setPen(Qt::black);
    p.setRenderHint(QPainter::Antialiasing, true);
    QColor col(150,146,142);
    QBrush brush(col);
    p.setBrush(brush);

    QRect leftRect(0,0,10,this->rect().height());
    QRect rightRect(this->rect().width()-10,0,10,this->rect().height());
    QRect upperRect(0,0,this->rect().width(), 10);
    QRect lowerRect(0,this->rect().height()-10,this->rect().width(),10);

    p.drawRect(leftRect);
    p.drawRect(rightRect);
    p.drawRect(upperRect);
    p.drawRect(lowerRect);

    QColor color(242,242,242);
    QBrush brush2(color);
    p.setBrush(brush2);
    QRect windowRect (10,10,this->rect().width()-20, this->rect().height()-20);
    p.drawRect(windowRect);
}
