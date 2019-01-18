#include "paymentupdate.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QMessageBox>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDebug>
#include "../CustomerRegistration/smtp.h"
#include <QTimer>

PaymentUpdate::PaymentUpdate(QWidget *parent)
    : QDialog(parent)
{
    //setting ui to the widget
    setupUi(this);

    //setting dialog attribute
    setAttribute(Qt::WA_DeleteOnClose);

    //loading initializing
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //setting connections for widgets
    connect(acTypeBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(accountTypeChanged(int)));
    connect(updateButton, SIGNAL(clicked(bool)),
            this, SLOT(updatePressed()));
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    connect(okButton, SIGNAL(clicked(bool)),
            this, SLOT(okPressed()));
    connect(deleteButton, SIGNAL(clicked(bool)),
            this, SLOT(deletePressed()));
    connect(newButton, SIGNAL(clicked(bool)),
            this, SLOT(newPressed()));
    //connetion completed

    setWidgets();
}

//setting general widgets of the paymentupdate like stylesheet, validators etc.
void PaymentUpdate::setWidgets()
{
    //setting title label
    titleLabel->setText(tr("<html><center><p><b>Payment Information of</b> <i>%1</i></p><center></html>").arg(mDetail.getDID()));

    //setting stylesheet to all line edit

    noaEdit->setStyleSheet(gDetail.getNormalStylesheet());
    aNumberEdit->setStyleSheet(gDetail.getNormalStylesheet());
    bNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    ifscEdit->setStyleSheet(gDetail.getNormalStylesheet());
    bAddEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cvvEdit->setStyleSheet(gDetail.getNormalStylesheet());

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

    //hiding payment box
    paymentBox->hide();

    //setting values to the table headers
    QStringList headerList;
    headerList  << "Select"<< "Name On Account" << "Account Numer" << "Account Type" << "Bank Name" << "Branch Address" << "IFSC Code" ;
    tableWidget->setColumnCount(headerList.count());
    tableWidget->setHorizontalHeaderLabels(headerList);
    setTableValue();
}

// it will provides functionality when different modes are selected for the payment
void PaymentUpdate::accountTypeChanged(int type)
{
    if(type == 0) {
        noaLabel->hide();
        updateButton->hide();
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
        updateButton->show();
        cvvEdit->hide();
        exDateLabel->hide();
        monthBox->hide();
        yearBox->hide();
        label_10->hide();
        noaLabel->setText(tr("<html><center><p align =\"left\" >Name on Account:   </p></center></html>"));
        aNumberLabel->setText(tr("<html><center><p align =\"left\" >Account Number:   </p></center></html>"));
    }/* else if (type == 2) {
        noaLabel->show();
        noaEdit->show();
        aNumberEdit->show();
        updateButton->show();
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
        noaLabel->setText(tr("<html><center><p align =\"left\" >Name on Debit Card:   </p></center></html>"));
        aNumberLabel->setText(tr("<html><center><p align =\"left\" >Debit Card Number:   </p></center></html>"));
    } else if(type == 3) {
        noaLabel->show();
        noaEdit->show();
        aNumberEdit->show();
        aNumberLabel->show();
        bNameLabel->hide();
        updateButton->show();
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
        noaLabel->setText(tr("<html><center><p align =\"left\" >Name on Credit Card:   </p></center></html>"));
        aNumberLabel->setText(tr("<html><center><p align =\"left\" >Credit Card Number:   </p></center></html>"));
    }*/ else {
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
        updateButton->show();
        label_10->hide();
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
    noaEdit->setStyleSheet(gDetail.getNormalStylesheet());
    aNumberEdit->setStyleSheet(gDetail.getNormalStylesheet());
    bNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    ifscEdit->setStyleSheet(gDetail.getNormalStylesheet());
    bAddEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cvvEdit->setStyleSheet(gDetail.getNormalStylesheet());
}

void PaymentUpdate::updatePressed()
{
    rLoad(1);
    QString error;

    if(acTypeBox->currentIndex() == 1) {
        if(bAddEdit->text().isEmpty()) {
            error = tr("Branch Address can not be empty");
            bAddEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(ifscEdit->text().isEmpty()) {
            error = tr("IFSC Code can not be empty");
            ifscEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(bNameEdit->text().isEmpty()){
            error = tr("Bank Name must required...Please fill it!");
            bNameEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(aNumberEdit->text().isEmpty()) {
            error = tr("Enter account number Moron!");
            aNumberEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(noaEdit->text().isEmpty()){
            error = tr("Please enter the name on the bank account");
            noaEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    }/* else if(acTypeBox->currentIndex() == 2){
        if(monthBox->currentIndex() == 0 || yearBox->currentIndex() == 0) {
            error = tr("Please select month and year in Expire Date");
        }
        if(cvvEdit->text().count() != 3 || cvvEdit->text().isEmpty()) {
            error = tr("Enter valid CVV number");
            cvvEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(bNameEdit->text().isEmpty()){
            error = tr("Bank Name must required...Please fill it!");
            bNameEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(aNumberEdit->text().isEmpty()) {
            error = tr("Enter debit card number Moron!");
            aNumberEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(noaEdit->text().isEmpty()){
            error = tr("Please enter the name on the debit card");
            noaEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    } else if(acTypeBox->currentIndex() == 3) {
        if(monthBox->currentIndex() == 0 || yearBox->currentIndex() == 0) {
            error = tr("Please select month and year in Expire Date");
        }
        if(aNumberEdit->text().isEmpty()) {
            error = tr("Enter credit card number Moron!");
            aNumberEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(noaEdit->text().isEmpty()){
            error = tr("Please enter the name on the credit card");
            noaEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    }*/ else if (acTypeBox->currentIndex() == 2) {
        if(bNameEdit->text().isEmpty()){
            error = tr("Bank Name must required...Please fill it!");
            bNameEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(aNumberEdit->text().isEmpty()) {
            error = tr("Enter UPI number Moron!");
            aNumberEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(noaEdit->text().isEmpty()){
            error = tr("Please enter the name on the UPI Account");
            noaEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    }

    if(error.isEmpty()){
        QSqlQuery query(myDatabase);
        QString queryString = "";

        queryString =  "select DairyPayInfo.NameOnAccount "
                       "from DairyPayInfo, DairyAccountNo "
                       "where DCAccountNo = '" + aNumberEdit->text() + "' and "
                                                                     "binary DairyPayInfo.BID = DairyAccountNo.BID and "
                                                                     "DairyPayInfo.ACType = '" + acTypeBox->currentText() + "'; ";


        if(!myDatabase.isOpen()){
            if(!connectDatabase()){
                rLoad(0);
                return ; //return if software is not able to connect with database;
            }
        }

        //now excecute query
        retry:
        if(!query.exec(queryString)){
            QMessageBox::critical(this,
                                     tr("Internet Connection Error - %1").arg(qApp->applicationName()),
                                     tr("Please make sure, you are connected to the internet service."
                                        "Retry after connecting to the internet"
                                        "SQL Error Code - %1").arg(query.lastError().nativeErrorCode()),
                                    tr("&OK"), tr("&Retry"), QString(), 0, 1 );
            if(result() == 1)
                goto retry;
            else {
                rLoad(0);
                return;
            }
        }

        if(query.size()> 0){
            if(query.next()){
                QMessageBox::information(this, tr("Registration failed! - %1").arg(qApp->applicationName()),
                                         tr("Error Code 0x001 - Duplication Restricted!\n\nAccount no: %1 is already registered to "
                                            "bank id: %2\nPlease visit our site for further information www.mds.onlinehelp.in")
                                         .arg(aNumberEdit->text()).arg(query.value("BID").toString()),
                                         QMessageBox::Ok | QMessageBox::Default);
                rLoad(0);
                return;
            }
        } else {
            //do insertion as account number is not registered yet to any bank id

            if(saveData()){
                //send mail to the customer of information updation
                sendMail();
                QTimer::singleShot(2000, this, SLOT(showMessage()));
                updateOffline();
                return;
            } else {
                rLoad(0);
                return;
                //just quit without sending mail if data is not saved
            }
        }
    } else {
        QMessageBox::information(this,
                                 tr("Error! - %1").arg(qApp->applicationName()),
                                 tr("%1").arg(error),
                                 QMessageBox::Ok | QMessageBox::Default);
        rLoad(0);
    }
}

void PaymentUpdate::updateOffline()
{
    mDetail.setBankInfo(this->bID,noaEdit->text(), acTypeBox->currentText(), bNameEdit->text(),
                        ifscEdit->text(), bAddEdit->text(), cvvEdit->text(), "", aNumberEdit->text());
    bID = ""; //setting to null for next uses
}

void PaymentUpdate::sendMail()
{
    QString subject = tr("Update Successfull!");
    QString message = tr("Dear Secretary,\n\nYour account information is updated successfully. Please login to your MDS account to see your information.\n\n"
              "Thank You.\nFor more support and information, visit our website www.mds.onlinehelp.co.on or call us on +91 7568577487.");

    //sending message to client
    Smtp *smtp = new Smtp(oDetail.getHostEmail(), oDetail.getHostEmailPass(), "smtp.gmail.com");
    smtp->sendMail(oDetail.getHostEmail(), mDetail.getemailID(), subject, message);
}

void PaymentUpdate::showMessage()
{
    disconnectDatabase();
    rLoad(0);
    QMessageBox::information(this,
                             tr("Updation Successfull - %1").arg(qApp->applicationName()),
                             tr("Your information is updated successfully.\nThank You"),
                             QMessageBox::Ok | QMessageBox::Default);
    emit remakeMe();
}

void PaymentUpdate::cancelPressed()
{
    paymentBox->hide();
    okButton->show();
    deleteButton->show();
    newButton->show();
}

void PaymentUpdate::closeEvent(QCloseEvent *)
{
    disconnectDatabase();
}

void PaymentUpdate::rLoad(int i)
{
    if(i ==1){
        tableWidget->setEnabled(false);
        okButton->setEnabled(false);
        deleteButton->setEnabled(false);
        newButton->setEnabled(false);
        noaEdit->setEnabled(false);
        aNumberEdit->setEnabled(false);
        bNameEdit->setEnabled(false);
        ifscEdit->setEnabled(false);
        bAddEdit->setEnabled(false);
        cvvEdit->setEnabled(false);
        monthBox->setEnabled(false);
        yearBox->setEnabled(false);
        updateButton->setEnabled(false);
        cancelButton->setEnabled(false);
        acTypeBox->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 - 64;
        loadingLabel->setGeometry(x, y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        tableWidget->setEnabled(true);
        okButton->setEnabled(true);
        deleteButton->setEnabled(true);
        newButton->setEnabled(true);
        acTypeBox->setEnabled(true);
        noaEdit->setEnabled(true);
        aNumberEdit->setEnabled(true);
        bNameEdit->setEnabled(true);
        ifscEdit->setEnabled(true);
        bAddEdit->setEnabled(true);
        cvvEdit->setEnabled(true);
        monthBox->setEnabled(true);
        yearBox->setEnabled(true);
        updateButton->setEnabled(true);
        cancelButton->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}

void PaymentUpdate::okPressed()
{
    this->close();
}

void PaymentUpdate::sendSignal()
{
    disconnectDatabase();
    rLoad(0);
    QMessageBox::information(this,
                             tr("Deletion Complete! - %1").arg(qApp->applicationName()),
                             tr("Selected Account details is deleted!"),
                             QMessageBox::Ok|QMessageBox::Default);
    emit remakeMe();
}

void PaymentUpdate::newPressed()
{
    //hide delete , new and ok button
    deleteButton->hide();
    newButton->hide();
    okButton->hide();

    //show payment box
    paymentBox->show();
}

bool PaymentUpdate::connectDatabase()
{
    if(!myDatabase.contains("dairyPayment")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "dairyPayment");
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
                              tr("\tDatabase Connection Problem 101!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(myDatabase.lastError().nativeErrorCode()),
                              tr("&Exit"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry;
        else{
            rLoad(0);
            deleteButton->hide();
            return false;
    }
 }
    return true;
}

void PaymentUpdate::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("dairyPayment");
}

void PaymentUpdate::setTableValue()
{
    if(!myDatabase.isOpen()){
        if(!connectDatabase()){
            deleteButton->hide();
            newButton->hide();
            return;
        }
    }

    //setting values to table
    QSqlQuery query(myDatabase);
    QString queryString;
    queryString = " select DairyPayInfo.BID, DairyPayInfo.ACType, DairyPayInfo.NameOnAccount, DairyAccountNo.DCAccountNo, DairyPayInfo.BankName, "
                  "DairyPayInfo.IFSC_Code, DairyPayInfo.BranchName, DairyPayInfo.CVV, DairyPayInfo.Expdate "
                  " from DairyPayInfo, DairyAccountNo "
                  "where binary DairyPayInfo.BID = DairyAccountNo.BID and "
                                                                     "binary DairyPayInfo.LocalDID = '" + mDetail.getDID() + "';";
    retry:
    if(!query.exec(queryString)){
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(query.lastError().nativeErrorCode()),
                              tr("&Exit"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry;
        else{
            rLoad(0);
            deleteButton->hide();
            return;
    }
    }

    if(query.size() > 0){
        int row = 0;
        while(query.next()){
            tableWidget->insertRow(tableWidget->rowCount());
            QTableWidgetItem *item = new QTableWidgetItem();
            QCheckBox *check = new QCheckBox;
            check->setText(query.value("BID").toString());
            checkList.insert(row, check);
            checkList[row] = check;
            tableWidget->setCellWidget(row, 0, checkList.at(row));

            item->setText(query.value("NameOnAccount").toString());
            tableWidget->setItem(row, 1, item);

            item = new QTableWidgetItem;
            item->setText(query.value("DCAccountNo").toString());
            tableWidget->setItem(row, 2, item);

            item = new QTableWidgetItem;
            item->setText(query.value("ACType").toString());
            tableWidget->setItem(row, 3, item);

            item = new QTableWidgetItem;
            item->setText(query.value("BankName").toString());
            tableWidget->setItem(row, 4, item);

            item = new QTableWidgetItem;
            item->setText(query.value("BranchName").toString());
            tableWidget->setItem(row, 5, item);

            item = new QTableWidgetItem;
            item->setText(query.value("IFSC_Code").toString());
            tableWidget->setItem(row, 6, item);
/*
            item = new QTableWidgetItem;
            item->setText(query.value("CVV").toString());
            tableWidget->setItem(row, 7, item);

            item = new QTableWidgetItem;
            item->setText(query.value("Expdate").toString());
            tableWidget->setItem(row, 8, item);
*/
            row++;

        }
    } else {
        deleteButton->hide();
    }
}

void PaymentUpdate::deletePressed()
{
    rLoad(1);
    if(!myDatabase.isOpen()){
        if(!connectDatabase()){
            rLoad(0);
            return;
        }
    }

    QSqlQuery query(myDatabase);
    QString queryString = "";
    int count = 0;
    queryString = "START TRANSACTION;";

    for(int row = 0; row<checkList.count();row++){
        if(checkList.at(row)->isChecked()){
            count = 1;
            queryString += "delete from DairyAccountNo where binary BID = '" + checkList.at(row)->text() + "';";
            queryString += "delete from DairyPayInfo where binary BID = '" + checkList.at(row)->text() + "' and  "
                                                                                                     " binary LocalDID = '" + mDetail.getDID() + "';";
        }
    }

    queryString += "COMMIT;";

    if(count == 0){
        rLoad(0);
        return;
    }

    retry:
    if(!query.exec(queryString)){
        qDebug() << "query error during deleting " << query.lastError() << endl;
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
            rLoad(0);
            return;
    }
    } else {
        sendMail();
        QTimer::singleShot(2000, this, SLOT(sendSignal()));
        deleteOffline();
    }
}

void PaymentUpdate::deleteOffline()
{
    //deleting data present offline
    for(int row = 0; row<checkList.count();row++){
        if(checkList.at(row)->isChecked()){
            mDetail.removeBankInfo(checkList.at(row)->text());
        }
    }
}

bool PaymentUpdate::saveData()
{
    QString bankQuery, accountQuery;
    bankQuery = "INSERT INTO DairyPayInfo(BID,NameOnAccount,ACType,BankName,IFSC_Code,BranchName,CVV,Expdate, LocalDID)";
    accountQuery = "insert into DairyAccountNo (BID, DCAccountNo) ";

    if(!myDatabase.isOpen()){
        if(!connectDatabase()){
            return false;
        }
    }

    QSqlDatabase::database("dairyPayment").transaction();
    QSqlQuery query(myDatabase);

    if(acTypeBox->currentIndex() != 0){
        //retreive highest bid from DairyPayInfo
        if(!query.exec("select max(BID) as maxBID from DairyPayInfo; ")){
            QMessageBox::critical(this,
                                  tr("Connection Error! : %1").arg(qApp->applicationName()),
                                  tr("\tDatabase Connection Problem!\bn"
                                     "Please make sure, you are connected to the internet service."
                                     "Retry after connecting to the internet."
                                     "SQL Error Code - %1").arg(query.lastError().nativeErrorCode()),
                                  QMessageBox::Ok|QMessageBox::Default);

            return false;
        }

        int bid;
        if(query.size() > 0){
            if(query.next()){
                bid = query.value("maxBID").toInt();
            }
        } else
            bid = 0;
        ++bid;

        //preparing expire date
        QString date = "20" + yearBox->currentText() + "-";
        QString tempDate  = QString::number(monthBox->currentIndex());

        if(tempDate.count() < 2){
            tempDate.insert(0,'0');
        }

        date += tempDate;
        date += "-01";

        this->bID = QString::number(bid);
        //insert values into DairyPayInfo
        bankQuery += "values (" + QString::number(bid) + ",'" + noaEdit->text() + "','" + acTypeBox->currentText() + "','" +
                bNameEdit->text() + "','" + ifscEdit->text() + "','"+
                bAddEdit->text() + "','" + cvvEdit->text() + "','" + date + "','" + mDetail.getDID() + "');";

        //insert values into DairyAccountNo
        accountQuery += "values (" + QString::number(bid) + ",'" + aNumberEdit->text() + "');";

        QString fullQuery = "START TRANSACTION; " +
                bankQuery + accountQuery +
                "COMMIT;";

        if(!myDatabase.isOpen()){
            if(!connectDatabase()){
                return false;
            }
        }

        retry:
        if(!query.exec(fullQuery)){
            int status = QMessageBox::critical(this,
                                  tr("Connection Error! - %1").arg(qApp->applicationName()),
                                  tr("Seems that you are not connected with internet.\n"
                                     "Please connect to the internet and try again."),
                                  tr("&Cancel"), tr("Retry"), QString() , 0, 1);

            if(status == 1){
                goto retry;
            }

            QSqlDatabase::database("remoteDBase").commit();
            return false;
        } else {
            QSqlDatabase::database().commit();
            return true;
        }
    }

    return false;
}

void PaymentUpdate::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}
