#include "customermilklog.h"
#include <QDate>
#include <QDebug>
#include <QTime>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QMessageBox>
#include <QMouseEvent>
#include <QRegExp>
#include <QRegExpValidator>
#include "offlinecustomerlog.h"
#include "../AdditionalCustomer/customerofflineentry.h"

CustomerMilkLog::CustomerMilkLog(QWidget *parent)
    : QWidget(parent)
{
    //setting up personal items
    setupUi(this);
    int hour = QTime::currentTime().hour();
    int tempShift;
    if(hour <=13){
        tempShift = 1;
    } else {
        tempShift = 0;
    }
    gotPrice = false;
    this->setMessage = 0;
    dateEdit->setDate(QDate::currentDate());
    if(QTime::currentTime().toString("a") == "pm")
        shiftBox->setCurrentIndex(1);
    namePoint = new QMovie(":/media/rd_square/Important/Qt projects/CustomerMilkLog/Images/Images/dir.gif");
    namePoint->setScaledSize(panimationLabel->size());
    panimationLabel->setMovie(namePoint);
    cAnimationLabel->setMovie(namePoint);
    namePoint->start();
    this->set = false;
    //additional customer log
    addCustLog = new AdditionalCustomer(QDate::currentDate().toString("yyyy-MM-dd"),tempShift,this);
    addCustLog->hide();
    //message for completion
    message = new Message(this); //for showing my message
    message->setGeometry((this->rect().width()-message->rect().width())/2,0,message->rect().width(), 10);
    message->hide();
    //sync milk log
    syncMilkLog = new SyncMilkLog(this);
    syncMilkLog->hide();

    //setting up timer
    timer = new QTimer(this);
    clockTimer = new QTimer(this);
    messageTimer = new QTimer(this);

    //setting loading label
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loading->setScaledSize(QSize(150,150));
    loading->start();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //installing event filter
    upAdditional->installEventFilter(this);

    //setting sync button
    syncButton = new QPushButton(tr("Upload Milk-Entry-Data"),this);
    syncButton->setFixedSize(200, 30);

    //setting up connections
    connect(timer,SIGNAL(timeout()),this, SLOT(updateAddCustMilkLog()));
    connect(clockTimer, SIGNAL(timeout()),this, SLOT(updateClockTime()));
    connect(messageTimer, SIGNAL(timeout()), this, SLOT(showMessage()));
    connect(cppBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(consumerCppChanged(int)));
    connect(ppBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(producerPpChanged(int)));
    connect(cclrBox, SIGNAL(clicked(bool)),
            this, SLOT(clrActivated(bool)));
    connect(pclrBox, SIGNAL(clicked(bool)),
            this, SLOT(clrActivated(bool)));
    connect(pokButton, SIGNAL(clicked(bool)),
            this, SLOT(searchCustomer()));
    connect(cokButton, SIGNAL(clicked(bool)),
            this, SLOT(searchCustomer()));
    connect(pSubmitButton, SIGNAL(clicked(bool)),
            this, SLOT(submitPressed()));
    connect(cSubmitButton, SIGNAL(clicked(bool)),
            this, SLOT(submitPressed()));
    connect(addCustLog, SIGNAL(hideThis()),
            this, SLOT(hideAddCustLog()));
    connect(shiftBox, SIGNAL(currentIndexChanged(int)),
            addCustLog, SLOT(shiftChanged(int)));
    connect(dateEdit, SIGNAL(dateChanged(QDate)),
            addCustLog, SLOT(dateChanged(QDate)));
    connect(syncButton, SIGNAL(clicked(bool)),
            this, SLOT(syncData()));

    //temporary connection
    connect(this, SIGNAL(requireMilkPrice(int)),
            this, SLOT(gotMilkPrice()));

    setWidgets();
}

void CustomerMilkLog::setWidgets()
{
    clockTimer->start(100);
    pNameLabel->hide();
    cNameLabel->hide();
    panimationLabel->hide();
    cAnimationLabel->hide();
    cAmountLabel->setText("");
    pAmountLabel->setText("");
    cppBox->currentIndexChanged(0);
    ppBox->setCurrentIndex(1);
    pclrBox->clicked();
    prodTagLabel->setText(tr("%1").arg("MP"+mDetail.getDID().right(4)));
    consTagLabel->setText(tr("%1").arg("MC"+mDetail.getDID().right(4)));
    tabWidget->setCurrentIndex(0);

    //setting stylesheets to all line edits
    pSearchEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pQuantityEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pFatEdit->setStyleSheet(gDetail.getNormalStylesheet());
    psnfEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pwpEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cSearchEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cQuantityEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cFatEdit->setStyleSheet(gDetail.getNormalStylesheet());
    csnfEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cwpEdit->setStyleSheet(gDetail.getNormalStylesheet());

    //setting validator to all line edits
    QRegExp searchExp("[0-9]{4}");
    QRegExpValidator *searchValidator = new QRegExpValidator(searchExp, this);
    pSearchEdit->setValidator(searchValidator);
    cSearchEdit->setValidator(searchValidator);

    QRegExp priceExp("[0-9]{1,5}[.][0-9]{2}");
    QRegExpValidator *priceValidator = new QRegExpValidator(priceExp, this);
    pQuantityEdit->setValidator(priceValidator);
    cQuantityEdit->setValidator(priceValidator);
    pFatEdit->setValidator(priceValidator);
    cFatEdit->setValidator(priceValidator);
    psnfEdit->setValidator(priceValidator);
    csnfEdit->setValidator(priceValidator);
    pwpEdit->setValidator(priceValidator);
    cwpEdit->setValidator(priceValidator);
}

void CustomerMilkLog::submitPressed()
{
    rLoad(1);
    QString error;
    if(tabWidget->currentIndex() == 0){
        //producer checking
        if (ppBox->currentIndex() == 1){
            if (pclrBox->isChecked()){
                if (psnfEdit->text().isEmpty()){
                    error = tr("Enter clr(degree) of milk.");
                    psnfEdit->setStyleSheet(gDetail.getErrorStylesheet());
                }
            } else {
                if (psnfEdit->text().isEmpty()) {
                    error = tr("Enter snf of milk.");
                    psnfEdit->setStyleSheet(gDetail.getErrorStylesheet());
                }
            }
            if(pFatEdit->text().isEmpty()) {
                error = tr("Enter fat of milk");
                pFatEdit->setStyleSheet(gDetail.getErrorStylesheet());
            }
        }
        if(pQuantityEdit->text().isEmpty()){
            error = tr("Enter quantity of milk");
            pQuantityEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(pAnimalBox->currentIndex() ==0) {
           error = tr("Select animal type for milk");
        }
        if(this->prodID.isEmpty()) {
            error = tr("Select customer for milk entry.");
        }
    } else {
        //consumer checking
        if(cppBox->currentIndex() == 1) {
            if (cclrBox->isChecked()) {
                if (csnfEdit->text().isEmpty()) {
                    error = tr("Enter clr(degree) of milk.");
                    csnfEdit->setStyleSheet(gDetail.getErrorStylesheet());
                }
            } else {
                if(csnfEdit->text().isEmpty()){
                    error = tr("Enter snf of milk.");
                    csnfEdit->setStyleSheet(gDetail.getErrorStylesheet());
                }
            }
            if(cFatEdit->text().isEmpty()){
                error = tr("Enter fat of milk.");
                cFatEdit->setStyleSheet(gDetail.getErrorStylesheet());
            }
        }
        if(cQuantityEdit->text().isEmpty()){
            error = tr("Enter quantity of milk");
            cQuantityEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(cAnimalBox->currentIndex() == 0) {
            error = tr("Select animal type for milk.");
        }
        if(this->consID.isEmpty()){
            error = tr("Select customer for milk entry.");
        }
    }

    if(!error.isEmpty()){
        rLoad(0);
        QMessageBox::information(this,
                                 tr("Error Encountered! - %1").arg(qApp->applicationName()),
                                 tr("<html><p><h3>%1</h3></p></html>").arg(error),
                                 QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    if(!saveDataOffline()){
        rLoad(0);
        QMessageBox::critical(this,tr("File Error! - %1").arg(qApp->applicationName()),
                              tr("<html><p><h3>Critical Data Error!:</h3></p><p>"
                                 "Your software has encountered serious data problem.</p>"
                                 "<p>Please contact our help line number otherwise your data will not be saved now and after.</p></html>"),
                              QMessageBox::Ok|QMessageBox::Default);
    }
    //showing successfull message
    if(tabWidget->currentIndex()==0){
        message->setValue(pNameLabel->text(), pQuantityEdit->text()+" "+pWeightBox->currentText(), QString::number(this->milkPrice) + tr(" per ")+ pWeightBox->currentText(),
                          QString::number(this->milkPrice*pQuantityEdit->text().toDouble()) + tr(" Rs."));
        this->setMessage=1;
        messageTimer->start(20);
        pQuantityEdit->setText("");
        psnfEdit->setText("");
        pFatEdit->setText("");
        pwpEdit->setText("");
    } else {
        message->setValue(cNameLabel->text(), cQuantityEdit->text()+" "+cWeightBox->currentText(), QString::number(this->milkPrice) + tr(" per ")+ cWeightBox->currentText(),
                          QString::number(this->milkPrice*cQuantityEdit->text().toDouble())+ tr(" Rs."));
        this->setMessage=1;
        messageTimer->start(20);
        cQuantityEdit->setText("");
        csnfEdit->setText("");
        cFatEdit->setText("");
        cwpEdit->setText("");
    }
    rLoad(0);
}

bool CustomerMilkLog::saveDataOffline()
{
    gotPrice = false;
    emit requireMilkPrice(animalTypeBox->currentIndex());
    checkAgain:
    if(!gotPrice)
        goto checkAgain;
    if(tabWidget->currentIndex() == 0){
        QString isKg;
        if(pWeightBox->currentIndex()==0)
            isKg = "1";
        else
            isKg = "0";
        if(!OfflineCustomerLog::saveCustLog(prodID, dateEdit->date().toString("yyyy-MM-dd"), QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"),
                                           QString::number(shiftBox->currentIndex()),QString::number(pAnimalBox->currentIndex()),isKg,pQuantityEdit->text(),psnfEdit->text(),
                                            pFatEdit->text(), QString::number(this->milkPrice), pwpEdit->text()))
            return false;
        if(!OfflineCustomerLog::saveTempCustLog(prodID, dateEdit->date().toString("yyyy-MM-dd"), QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"),
                                                QString::number(shiftBox->currentIndex()),QString::number(pAnimalBox->currentIndex()),isKg,pQuantityEdit->text(),psnfEdit->text(),
                                                 pFatEdit->text(), QString::number(this->milkPrice), pwpEdit->text()))
            return false;
        return true;
    } else {
        QString isKg;
        if(cWeightBox->currentIndex()==0)
            isKg = "1";
        else
            isKg = "0";
        if(!OfflineCustomerLog::saveCustLog(consID, dateEdit->date().toString("yyyy-MM-dd"), QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"),
                                           QString::number(shiftBox->currentIndex()),QString::number(cAnimalBox->currentIndex()),isKg,cQuantityEdit->text(),csnfEdit->text(),
                                            cFatEdit->text(), QString::number(this->milkPrice), cwpEdit->text()))
            return false;
        if(!OfflineCustomerLog::saveTempCustLog(consID, dateEdit->date().toString("yyyy-MM-dd"), QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"),
                                           QString::number(shiftBox->currentIndex()),QString::number(cAnimalBox->currentIndex()),isKg,cQuantityEdit->text(),csnfEdit->text(),
                                            cFatEdit->text(), QString::number(this->milkPrice), cwpEdit->text()))
            return false;
        return true;
    }
}

void CustomerMilkLog::searchCustomer()
{
    if(tabWidget->currentIndex() == 0){
        //for producer
        QString id = pSearchEdit->text();
        while(id.length()<4){
            id = "0"+id;
        }
        QString custID = "MP" + mDetail.getDID().right(4)+id;
        prodID = custID;
        QString custName = OfflineCustRegistration::searchCustomer(custID);
        if(custName.isEmpty()){
            panimationLabel->hide();
            pNameLabel->hide();
            pNameLabel->setText("");
            QMessageBox::information(this,
                                     tr("No Match Found! - %1").arg(qApp->applicationName()),
                                     tr("<html><p><h3>No Match Found!</h3></p>"
                                        "<p>Please search with valid customer id.</p></html>"),
                                     QMessageBox::Ok|QMessageBox::Default);
            return;
        }
        panimationLabel->show();
        pNameLabel->show();
        pNameLabel->setText(tr("%1").arg(custName+" ("+QString::number(id.toInt())+") "));
    } else {
        //for consumer
        QString id = cSearchEdit->text();
        while(id.length()<4){
            id = "0"+id;
        }
        QString custID = "MC"+ mDetail.getDID().right(4) +id;
        consID = custID;
        QString custName = OfflineCustRegistration::searchCustomer(custID);
        if(custName.isEmpty()) {
            cAnimationLabel->hide();
            cNameLabel->hide();
            cNameLabel->setText("");
            QMessageBox::information(this,
                                     tr("No Match Found! - %1").arg(qApp->applicationName()),
                                     tr("<html><p><h3>No Match Found!</h3></p>"
                                        "<p>Please search with valid customer id.</p></html>"),
                                     QMessageBox::Ok|QMessageBox::Default);
            return;
        }
        cAnimationLabel->show();
        cNameLabel->show();
        cNameLabel->setText(tr("%1").arg(custName+" ("+QString::number(id.toInt())+") "));
    }
}

void CustomerMilkLog::clrActivated(bool stat)
{
    if(tabWidget->currentIndex() == 1){
        if(stat){
            csnfLabel->setText(tr("CLR:"));
            cclrBox->setText(tr("Deactivate CLR (Corrected Lactometer Reading)"));
        } else {
            csnfLabel->setText(tr("SNF:"));
            cclrBox->setText(tr("Activate CLR (Corrected Lactometer Reading)"));
        }
    } else {
        if(stat){
            psnfLabel->setText(tr("CLR:"));
            pclrBox->setText(tr("Deactivate CLR (Corrected Lactometer Reading)"));
        } else {
            psnfLabel->setText(tr("SNF:"));
            pclrBox->setText(tr("Activate CLR (Corrected Lactometer Reading)"));
        }
    }
}

void CustomerMilkLog::consumerCppChanged(int index)
{
    if(index==0){
        cFatLabel->hide();
        cFatEdit->hide();
        csnfEdit->hide();
        csnfLabel->hide();
        cwpLabel->hide();
        cwpEdit->hide();
        cclrBox->hide();
        line_7->hide();
        line_8->hide();
    } else {
        cFatLabel->show();
        cFatEdit->setText("");
        cFatEdit->show();
        csnfEdit->setText("");
        csnfEdit->show();
        csnfLabel->show();
        cwpLabel->show();
        cwpLabel->setText("");
        cwpEdit->show();
        cclrBox->setCheckState(Qt::Unchecked);
        cclrBox->show();
        line_7->show();
        line_8->show();
    }
}

void CustomerMilkLog::producerPpChanged(int index)
{
    if(index==0){
        pFatLabel->hide();
        pFatEdit->hide();
        psnfEdit->hide();
        psnfLabel->hide();
        pwpLabel->hide();
        pwpEdit->hide();
        pclrBox->hide();
        line_5->hide();
        line_6->hide();
    } else {
        pFatLabel->show();
        pFatEdit->setText("");
        pFatEdit->show();
        psnfEdit->setText("");
        psnfEdit->show();
        psnfLabel->show();
        pwpLabel->show();
        pwpEdit->setText("");
        pwpEdit->show();
        pclrBox->setCheckState(Qt::Unchecked);
        pclrBox->show();
        line_5->show();
        line_6->show();
    }
}

bool CustomerMilkLog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == upAdditional && event->type() == QEvent::MouseButtonPress){
        QMouseEvent* me = static_cast<QMouseEvent*>(event);
        if(me->button() == Qt::LeftButton){
            if(set)
                set = false;
            else
                set = true;
            setAddMilkLog(set);
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void CustomerMilkLog::setAddMilkLog(bool set)
{
    if(set) {
        tabWidget->setEnabled(false);
        addCustLog->setGeometry((this->rect().width()-addCustLog->rect().width())/2,this->rect().height()-290,addCustLog->rect().width(), 10);
        addCustLog->show();
        timer->start(20);
    } else {
        timer->start(20);
    }
}

void CustomerMilkLog::updateAddCustMilkLog()
{
    if(set){
        addCustLog->setGeometry((this->rect().width()-addCustLog->rect().width())/2,this->rect().height()-290,addCustLog->rect().width(), addCustLog->rect().height()+10);
        if(addCustLog->rect().height() > 240){
            timer->stop();
            repaint();
        }
    } else {
        addCustLog->setGeometry((this->rect().width()-addCustLog->rect().width())/2,this->rect().height()-290,addCustLog->rect().width(), addCustLog->rect().height()-10);
        if(addCustLog->rect().height() == 10){
            timer->stop();
            addCustLog->hide();
            tabWidget->setEnabled(true);
            repaint();
        }
    }
}

void CustomerMilkLog::showMessage()
{
    if(this->setMessage==0){
        //message going to hide
        message->setGeometry((this->rect().width()-message->rect().width())/2,0,message->rect().width(), message->rect().height()-10);
        if(message->rect().height() == 10){
            message->hide();
            messageTimer->stop();
            syncButton->show();
        }
    } else if(this->setMessage==1){
        //message is going to show
        message->show();
        syncButton->hide();
        message->setGeometry((this->rect().width()-message->rect().width())/2,0,message->rect().width(), message->rect().height()+10);
        if(message->rect().height() > 140){
            messageTimer->stop();
            this->setMessage = 2;
            messageTimer->start(5000);

        }
    } else {
        messageTimer->stop();
        this->setMessage = 0;
        messageTimer->start(20);
    }
}

void CustomerMilkLog::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    addCustLog->setGeometry((this->rect().width()-addCustLog->rect().width())/2,this->rect().height()-addCustLog->rect().height()-40,addCustLog->rect().width(), addCustLog->rect().height());
    syncButton->setGeometry(this->rect().width()-250, 20, syncButton->rect().width(), syncButton->rect().height());
    message->setGeometry((this->rect().width()-message->rect().width())/2,0,message->rect().width(), message->rect().height());
    syncMilkLog->setGeometry(this->rect().width()/4, this->rect().height()/4, syncMilkLog->rect().width(), syncMilkLog->rect().height());

    QPainter p(this);
    QPen pen;
    QColor color(101,99,97);
    pen.setColor(color);
    pen.setWidth(3);
    p.setPen(pen);
    p.setRenderHint(QPainter::Antialiasing, true);
    QRect rec = upAdditional->geometry();

    if(set){
        p.drawLine(rec.left(), rec.top()+20, rec.left()+(rec.width())/2, rec.top()+30);
        p.drawLine(rec.left(),rec.top()+15, rec.left()+(rec.width())/2, rec.top()+25);

        p.drawLine(rec.left()+(rec.width())/2, rec.top()+30, rec.right(),rec.top()+20);
        p.drawLine(rec.left()+(rec.width())/2, rec.top()+25, rec.right(),rec.top()+15);
    } else {
        p.drawLine(rec.left(), rec.top()+30, rec.left()+(rec.width())/2, rec.top()+20);
        p.drawLine(rec.left(),rec.top()+25, rec.left()+(rec.width())/2, rec.top()+15);

        p.drawLine(rec.left()+(rec.width())/2, rec.top()+20, rec.right(),rec.top()+30);
        p.drawLine(rec.left()+(rec.width())/2, rec.top()+15, rec.right(),rec.top()+25);
    }

    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}

void CustomerMilkLog::updateClockTime()
{
    QString clockTime = QTime::currentTime().toString("hh:mm:ss a");
    timeLabel->setText(tr("<html><font color=\"red\">%1</font></html>").arg(clockTime));
}

void CustomerMilkLog::gotMilkPrice()
{
    milkPrice = 40;
    gotPrice = true;
}

void CustomerMilkLog::rLoad(int i)
{
    if (i == 0){
        //turn off loading label
        loadingLabel->hide();
        tabWidget->setEnabled(true);
    } else {
        //turn on loading label
        loadingLabel->show();
        tabWidget->setEnabled(false);
    }
}

void CustomerMilkLog::hideAddCustLog()
{
    this->set = false;
    timer->start(20);
}

void CustomerMilkLog::syncData()
{
    //disabling all the input widgets
    tabWidget->setEnabled(false);
    upAdditional->hide();
    dateEdit->setEnabled(false);
    shiftBox->setEnabled(false);
    animalTypeBox->setEnabled(false);

    //upload data to internet
    syncMilkLog->show();
    syncMilkLog->textLabel->setText(tr("Uploading Additional Customers..."));
    QList<QStringList> customer;
    customer = CustomerOfflineEntry::getTempCust();
    syncMilkLog->setRange(0, customer.length(), tr("Uploading Customer Data to server (%p%)"));
    for(int temp = 0; temp< customer.length(); temp++) {
        if(syncMilkLog->uploadAddCust(customer[temp].at(0), customer[temp].at(1))){
            CustomerOfflineEntry::delTempCust(customer[temp].at(0));
        } else {
            //break;
    }
        syncMilkLog->setValue(temp+1);
    }

    //uploading milk data log to server

    QList<QStringList> customerLog ;
    customerLog = CustomerOfflineEntry::getTempLog();
    syncMilkLog->textLabel->setText(tr("Uploading Additional Customer Milk Data Entry..."));
    syncMilkLog->setRange(0, customerLog.length(), tr("Uploading Additional Customer Milk-Data (%p%)"));
    for (int temp = 0; temp< customerLog.length(); temp++) {
        QStringList singleCust = customerLog[temp];
        if(syncMilkLog->uploadAddCustLog(singleCust.at(0), singleCust.at(1), singleCust.at(2), singleCust.at(3),
                                         singleCust.at(5), singleCust.at(6), singleCust.at(7),singleCust.at(4))) {
            CustomerOfflineEntry::delTempLog(singleCust.at(0), singleCust.at(1), singleCust.at(2),singleCust.at(3));
        } else {
            //break;
        }
        syncMilkLog->setValue(temp+1);
    }

    //write for customer milk entry data log
    QList<QStringList> prodLog;
    prodLog = OfflineCustomerLog::getTempLog("Producer");
    syncMilkLog->textLabel->setText(tr("Uploading Producer Milk Data Entry..."));
    syncMilkLog->setRange(0, prodLog.length(), tr("Uploading Producer Milk-Data (%p%)"));
    for(int temp= 0; temp<prodLog.length(); temp++) {
        QStringList singleCust = prodLog[temp];
        if(syncMilkLog->uploadCustLog(singleCust.at(0), singleCust.at(1),singleCust.at(2),singleCust.at(3),
                                      singleCust.at(4),singleCust.at(5), singleCust.at(6),singleCust.at(8), singleCust.at(7),
                                      singleCust.at(10),singleCust.at(9)))
        {
            OfflineCustomerLog::delTempLog(singleCust.at(0),singleCust.at(1),singleCust.at(3), singleCust.at(2));
        } else {
            //break;
        }
        syncMilkLog->setValue(temp+1);
    }

    QList<QStringList> consLog;
    consLog = OfflineCustomerLog::getTempLog("Consumer");
    syncMilkLog->textLabel->setText(tr("Uploading Producer Milk Data Entry..."));
    syncMilkLog->setRange(0, consLog.length(), tr("Uploading Producer Milk-Data (%p%)"));
    for(int temp= 0; temp<consLog.length(); temp++) {
        QStringList singleCust = consLog[temp];
        if(syncMilkLog->uploadCustLog(singleCust.at(0), singleCust.at(1),singleCust.at(2),singleCust.at(3),
                                      singleCust.at(4),singleCust.at(5), singleCust.at(6),singleCust.at(8), singleCust.at(7),
                                      singleCust.at(10),singleCust.at(9)))
        {
            OfflineCustomerLog::delTempLog(singleCust.at(0),singleCust.at(1),singleCust.at(3), singleCust.at(2));
        } else {
            //break;
        }
        syncMilkLog->setValue(temp+1);
    }

    //enabling all the input widgets
    tabWidget->setEnabled(true);
    upAdditional->show();
    dateEdit->setEnabled(true);
    shiftBox->setEnabled(true);
    animalTypeBox->setEnabled(true);

    syncMilkLog->hide();
}
