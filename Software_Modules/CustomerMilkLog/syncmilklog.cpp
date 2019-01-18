#include "syncmilklog.h"
#include <QPainter>
#include <QRadialGradient>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

SyncMilkLog::SyncMilkLog(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    progressBar->setRange(0,100);
    progressBar->setValue(0);
    progressBar->setFormat("%p%");
    textLabel->setText(tr("Preparing to upload data on server..."));
}

void SyncMilkLog::setRange(int minimum, int maximum, QString format)
{
    progressBar->setRange(minimum, maximum);
    progressBar->setValue(minimum);
    progressBar->setFormat(format);
}

void SyncMilkLog::setValue(int value)
{
    progressBar->setValue(value);
}

void SyncMilkLog::setText(QString text)
{
    textLabel->setText(text);
}

void SyncMilkLog::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter p(this);
    QBrush brush(QColor(148,148,148));
    p.setBrush(brush);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(this->rect(),25,25);
}

bool SyncMilkLog::connectDatabase()
{
    if(!myDatabase.contains("syncMilkLog")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "syncMilkLog");
        myDatabase.setHostName(oDetail.getHostName());
        myDatabase.setDatabaseName(oDetail.getDatabase());
        myDatabase.setUserName(oDetail.getUserName());
        myDatabase.setPassword(oDetail.getUserPass());
        myDatabase.setPort(3306);
    }
  retry:
    if(!myDatabase.open()){
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(myDatabase.lastError().nativeErrorCode()),
                              tr("&Exit"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry;
        else{
            return false;
    }
 }
    return true;
}

void SyncMilkLog::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("syncMilkLog");
}

bool SyncMilkLog::uploadAddCust(QString mobileNo, QString custName)
{
    if(!myDatabase.isOpen()) {
        if(!connectDatabase()) {
            return false;
        }
    }

    QString queryString = "INSERT INTO AdditionalCust(Contact, CustName, LocalDID) VALUES ('" + mobileNo +
            "','"+custName+"','"+mDetail.getDID()+"');";
    QSqlQuery query(myDatabase);
    if(query.exec(queryString)){
        return true;
    }
    return false;
}

bool SyncMilkLog::uploadAddCustLog(QString custID, QString date, QString shift, QString dateTime, QString animal,
                                   QString quantity, QString price, QString isKg)
{
    if(!myDatabase.isOpen()) {
        if(!connectDatabase()){
            return false;
        }
    }

    QString queryString = "INSERT INTO AddMilkLog(ACustID, OfDate, DateATime, IsMorning, AnimalName, "
                          "Quantity, Price, IsKg, LocalDID) VALUES ('"+custID+"','"+date+"','"+dateTime+"','"+
            shift+"','"+animal+"',"+quantity+","+price +",'"+isKg+"','"+mDetail.getDID()+"');";
    QSqlQuery query(myDatabase);
    if(query.exec(queryString)){
        return true;
    }
    return false;
}

bool SyncMilkLog::uploadCustLog(QString custID, QString date, QString shift, QString dateTime, QString iskg,
            QString milkType, QString quantity, QString snf, QString fat, QString waterPerc, QString price)
{
    //formatting strings
    if(snf.isEmpty()){
        snf = "NULL";
    }
    if(waterPerc.isEmpty()) {
        waterPerc = "NULL";
    }
    if(fat.isEmpty()) {
        fat = "NULL";
    }
    if(!myDatabase.isOpen()) {
        if(!connectDatabase()) {
            return false;
        }
    }

    QString queryString;
    if(custID.left(2)=="MP"){
        queryString = "INSERT INTO ProdMilkLog (ProdID, Ofdate, DateATime, IsMorning, Quantity, SNF, WaterP, FAT, "
                      "Price, MilkTypeID, IsKg, LocalDID) VALUES ('"+custID+"','"+date+"','"+dateTime+"','"+shift+
                "',"+quantity+","+snf+","+waterPerc+","+fat+","+price+",'"+milkType+"','"+iskg+"','"+mDetail.getDID()+"');";
    } else {
        queryString = "INSERT INTO ConsMilkLog (ConsID, OfDate, DateATime, IsMorning, Quantity, SNF, WaterP, "
                      "FAT, Price, MilkTypeID, IsKg, LocalDID) VALUES ('"+custID+"','"+date+"','"+dateTime+ "','"+shift+
                "',"+quantity+","+snf+","+waterPerc+","+fat+","+price+",'"+milkType+"','"+iskg+"','"+mDetail.getDID()+"');";
    }

    QSqlQuery query(myDatabase);
    if(query.exec(queryString)){
        return true;
    }
    return false;
}
