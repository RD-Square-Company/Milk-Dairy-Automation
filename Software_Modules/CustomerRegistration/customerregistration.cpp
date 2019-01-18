#include "customerregistration.h"
#include "smtp.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QPixmap>
#include <QBrush>
#include <QPrinter>
#include <QPainter>

CustomerRegistration::CustomerRegistration(QString type, QWidget *parent)
    : QWidget(parent)
{
    this->type = type;
    registrationDialog = new Registration(type);
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(registrationDialog, 0, 0);
    paymentDialog = new Payment;


    //defining properties of window
    setAttribute(Qt::WA_DeleteOnClose);
    setLayout(mainLayout);

    //setting connections
    connect(registrationDialog, SIGNAL(nextByCRF()),
            this, SLOT(nextFromCRF()));
    connect(registrationDialog, SIGNAL(cancelByCRF()),
            this, SLOT(quit()) );
    connect(paymentDialog, SIGNAL(regByPay()),
            this, SLOT(regFromPay()));
    connect(paymentDialog, SIGNAL(prevByPay()),
            this, SLOT(prevFromPay()));
    connect(paymentDialog, SIGNAL(quitByPay()),
            this, SLOT(quit()));

    //all connections are done
}

void CustomerRegistration::nextFromCRF()
{
    registrationDialog->hide();
    paymentDialog->show();
    mainLayout->removeWidget(registrationDialog);
    mainLayout->addWidget(paymentDialog, 0, 0);
}

void CustomerRegistration::quit()
{
    int status = QMessageBox::warning(this, tr("Cancel Registration - %1").arg(qApp->applicationName()),
                         tr("Do you want to cancel Registration ? \n"
                            "Your information will not be saved!"),
                         tr("&Yes"), tr("&No"), QString(), 0, 1);
    if (status == 0){
        delete paymentDialog;
        delete registrationDialog;
        this->close();
    }
}

void CustomerRegistration::regFromPay()
{
    paymentDialog->rLoad(1);
    if(connectDatabase()){
        /*
         * initializing query handler to check wheather the enetered adhaar card no and
         * account number is already exist or not
         * if already exist.. Program will through a error to user
         * and show a message that adhaar or account is already exists!
         *
         */
        bool doB = false;
        if(paymentDialog->acTypeBox->currentIndex() != 0)
            doB = true;
        QString q1, custID, adhaarno, getA="", getB="";
        QSqlQuery query1(mydatabase) ,query2(mydatabase);
        if(type == "Producer"){
            custID = "ProdID";
            q1 = "select * from ProducerPAE where AdhaarNo ";
        }else {
            custID = "ConsID";
            q1 = "select * from ConsumerPAE where AdhaarNo ";
        }

        adhaarno = registrationDialog->ad1Edit->text() +
                registrationDialog->ad2Edit->text() + registrationDialog->ad3Edit->text();
        query1.prepare(q1 + "= ? ;");
       if(doB){
            query2.prepare("select  BankInfo.NameOnAccount "
                           " from BankInfo, BankAccountNo "
                           " where  DCAccount = ? and "
                           "binary BankInfo.BID = BankAccountNo.BID and "
                           "  BankInfo.ACType = ?;");
            query2.bindValue(0, paymentDialog->aNumberEdit->text());
            query2.bindValue(1, paymentDialog->acTypeBox->currentText());
      }
        query1.bindValue(0, adhaarno);

        //checking if query is executing or not
        bool ifquery1 = true, ifquery2=true;
        if(!mydatabase.isOpen())
            connectDatabase();
        if(!query1.exec()){
            ifquery1 = false;
        }
       if(doB){
           if(!query2.exec()){
               ifquery2 = false;
           }
       }


       //showing error messages if query is not executing
        if(!ifquery1 && !ifquery2){
            QMessageBox::information(this, tr("Query Error - %1").arg(qApp->applicationName()),
                                     tr("Error Code: %1 and %2\n\n%3\n%4").arg(query1.lastError().nativeErrorCode()).arg(query2.lastError().nativeErrorCode())
                                     .arg(query1.lastError().text()).arg(query2.lastError().text()),
                                     QMessageBox::Ok|QMessageBox::Default);
            disconnectDatabase();
            paymentDialog->rLoad(0);
            return;
        } else if (!ifquery1){
            QMessageBox::information(this, tr("Query Error - %1").arg(qApp->applicationName()),
                                     tr("Error Code: %1 \n\n2%").arg(query1.lastError().nativeErrorCode())
                                     .arg(query1.lastError().text()),
                                     QMessageBox::Ok|QMessageBox::Default);
            disconnectDatabase();
            paymentDialog->rLoad(0);
            return;
        } else if(!ifquery2) {
            QMessageBox::information(this, tr("Query Error - %1").arg(qApp->applicationName()),
                                     tr("Error Code: %1\n\n%2").arg(query2.lastError().nativeErrorCode())
                                     .arg(query2.lastError().text()),
                                     QMessageBox::Ok|QMessageBox::Default);
            disconnectDatabase();
            paymentDialog->rLoad(0);
            return;
        } else {/*
                  if no error is found and data is retrieved than error message will pop up
                  as data is already exists in database
                  */
            if(query1.size() > 0){
                if(query1.next())
                    getA = query1.value(custID).toString();
            }

            if(doB){
                if(query2.size() > 0){
                    if(query2.next())
                        getB = query2.value("BID").toString();
                }
            }

            if((!getA.isEmpty()) && (!getB.isEmpty())){
                QMessageBox::information(this, tr("Registration failed! - %1").arg(qApp->applicationName()),
                                         tr("Error Code: 0x001 - Duplication Restricted!\n\nAdhaar no: %1 and Account no: %2 are already registered to "
                                            "customer: %3 and Bank id: %4\nPlease visit our site for further information www.mds.onlinehelp.in")
                                         .arg(adhaarno).arg(paymentDialog->aNumberEdit->text()).arg(getA).arg(getB),
                                         QMessageBox::Ok|QMessageBox::Default);
                disconnectDatabase();
                paymentDialog->rLoad(0);
                return;
            } else if (!getA.isEmpty()){
                QMessageBox::information(this, tr("Registration failed! - %1").arg(qApp->applicationName()),
                                         tr("Error Code: 0x001 - Duplication Restricted!\n\nAdhaar no: %1 is already registered to "
                                            "customer: %2\nPlease visit our site for further information www.mds.onlinehelp.in")
                                         .arg(adhaarno).arg(getA),
                                         QMessageBox::Ok|QMessageBox::Default);
                disconnectDatabase();
                paymentDialog->rLoad(0);
                return;
            } else if (!getB.isEmpty()){
                QMessageBox::information(this, tr("Registration failed! - %1").arg(qApp->applicationName()),
                                         tr("Error Code: 0x001 - Duplication Restricted!\n\nAccount no: %1 is already registered to "
                                            "Bank id: %2\nPlease visit our site for further information www.mds.onlinehelp.in")
                                         .arg(paymentDialog->aNumberEdit->text()).arg(getB),
                                         QMessageBox::Ok|QMessageBox::Default);
                disconnectDatabase();
                paymentDialog->rLoad(0);
                return;
            }
        }

        /*
         * now all the errors are remove so
         * it can generate custID and
         * save data to database
         *
         */
        if(generateCustId()){
            //paymentDialog->rLoad(0);
            if(!registrationDialog->emailEdit->text().isEmpty()){
                sentMail(registrationDialog->emailEdit->text(), registrationDialog->firstNameEdit->text() + " " + registrationDialog->lastNameEdit->text());
                //preparing expire date for bank account info
                //as  credit card and debit card payment will be removed from this system so
                //expire date will be set to null by default till this feature is disabled.
                //For information see acTypeBox in paymentDialog.
                OfflineCustRegistration::registerOffline(custDairyID,registrationDialog->androidBox->currentText().at(0),registrationDialog->ad1Edit->text()+registrationDialog->ad2Edit->text()+registrationDialog->ad3Edit->text() ,registrationDialog->firstNameEdit->text(), registrationDialog->middleNameEdit->text(),
                                                         registrationDialog->lastNameEdit->text(), registrationDialog->pContactEdit->text(), registrationDialog->sContactEdit->text(), registrationDialog->line1Edit->text(), registrationDialog->line2Edit->text(),
                                                         registrationDialog->stateBox->currentText(), registrationDialog->pincodeEdit->text(),registrationDialog->emailEdit->text(),bID, paymentDialog->noaEdit->text(), paymentDialog->aNumberEdit->text(),
                                                         paymentDialog->acTypeBox->currentText(),paymentDialog->bNameEdit->text(),paymentDialog->ifscEdit->text(),paymentDialog->bAddEdit->text(),paymentDialog->cvvEdit->text(),QString() );
                bID = "";
                QTimer::singleShot(10000, this, SLOT(completionMessage()) );
            } else {
                OfflineCustRegistration::registerOffline(custDairyID,registrationDialog->androidBox->currentText().at(0),registrationDialog->ad1Edit->text()+registrationDialog->ad2Edit->text()+registrationDialog->ad3Edit->text() ,registrationDialog->firstNameEdit->text(), registrationDialog->middleNameEdit->text(),
                                                         registrationDialog->lastNameEdit->text(), registrationDialog->pContactEdit->text(), registrationDialog->sContactEdit->text(), registrationDialog->line1Edit->text(), registrationDialog->line2Edit->text(),
                                                         registrationDialog->stateBox->currentText(), registrationDialog->pincodeEdit->text(),registrationDialog->emailEdit->text(),bID, paymentDialog->noaEdit->text(), paymentDialog->aNumberEdit->text(),
                                                         paymentDialog->acTypeBox->currentText(),paymentDialog->bNameEdit->text(),paymentDialog->ifscEdit->text(),paymentDialog->bAddEdit->text(),paymentDialog->cvvEdit->text(),QString() );
                bID = "";
                QTimer::singleShot(1000, this, SLOT(completionMessage()) );
            }
        } else {
            paymentDialog->rLoad(0);
            disconnectDatabase();
        }
    }
}

void CustomerRegistration::prevFromPay()
{
    paymentDialog->hide();
    registrationDialog->show();
    mainLayout->removeWidget(paymentDialog);
    mainLayout->addWidget(registrationDialog, 0, 0);
}

bool CustomerRegistration::connectDatabase()
{
    if(!mydatabase.contains("remoteDBase")){
        mydatabase = QSqlDatabase::addDatabase("QMYSQL", "remoteDBase");
        mydatabase.setHostName(oDetail.getHostName());
        mydatabase.setDatabaseName(oDetail.getDatabase());
        mydatabase.setUserName(oDetail.getUserName());
        mydatabase.setPassword(oDetail.getUserPass());
        mydatabase.setPort(3306);
    }
  retry:
    if(!mydatabase.open()){
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(mydatabase.lastError().nativeErrorCode()),
                              tr("&Exit"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry;
        else{
            paymentDialog->rLoad(0);
            return false;
    }
 }
    return true;
}

void CustomerRegistration::disconnectDatabase()
{
    mydatabase = QSqlDatabase();
    mydatabase.removeDatabase("remoteDBase");
}

bool CustomerRegistration::saveData()
{
    //generating user name and user password for login
    generateUserName();
    generateCustPass();

    //setting data for master table
    QString custQuery,custQuery1, custQuery2,custQuery3 , custQuery4;
    custQuery1 = "INSERT INTO BankInfo(BID,NameOnAccount,ACType,BankName,IFSC_Code,BranchName,CVV,Expdate, LocalDID)";
    //query handler initialization

    if(type == "Producer"){
        custQuery = "INSERT INTO Producer(ProdID,ProdFName,ProdMName,ProdLName,Pcontact,Scontact,Street,City,State,Pincode,Email_ID,IsApp, LocalDID ) ";
        custQuery2 = "insert into ProducerAccount (ProdID, BID) ";
        custQuery4 = "insert into ProducerPAE (ProdID, AdhaarNo) ";
    }
    else{
        custQuery = "INSERT INTO Consumer(ConsID,ConsFName,ConsMName,ConsLName,Pcontact,Scontact,Street,City,State,Pincode,Email_ID,IsApp, LocalDID) ";
        custQuery2 = "insert into ConsumerAccount (ConsID, BID) ";
        custQuery4 = "insert into ConsumerPAE (ConsID, AdhaarNo) ";
    }

    //insert values into Producer or Consumer
    custQuery += " values('"+ custDairyID + "','"+
                              registrationDialog->firstNameEdit->text() + "','" + registrationDialog->middleNameEdit->text() + "','" +
                              registrationDialog->lastNameEdit->text() + "','" + registrationDialog->pContactEdit->text()  + "','" +
                              registrationDialog->sContactEdit->text() + "','" + registrationDialog->line1Edit->text() + "','" +
                              registrationDialog->line2Edit->text() + "','" + registrationDialog->stateBox->currentText() + "','" +
                              registrationDialog->pincodeEdit->text() + "','" + registrationDialog->emailEdit->text() + "','" +
                              registrationDialog->androidBox->currentText() + "','" +  mDetail.getDID() + "');";

    QString adhaarNo = registrationDialog->ad1Edit->text() +
            registrationDialog->ad2Edit->text() + registrationDialog->ad3Edit->text();
    // insert values into producerpae and consumerpae

    custQuery4 += "  values ( '"+ custDairyID + "','" + adhaarNo + "');";

    if(!mydatabase.isOpen())
        if(!connectDatabase()){
            return false;
        }
    QSqlQuery query(mydatabase);

    QSqlDatabase::database("remoteDBase").transaction();

    if(paymentDialog->acTypeBox->currentIndex() != 0){
        //retreive highest bid from bankinfo
        if(!query.exec("select max(bid) as maxBID from BankInfo;")){
            QMessageBox::critical(this,
                                  tr("Connection Error! : %1").arg(qApp->applicationName()),
                                  tr("\tDatabase Connection Problem!\n"
                                     "Please make sure, you are connected to the internet service. "
                                     "Retry after connecting to the internet."
                                     "SQL Error Code - %1").arg(query.lastError().nativeErrorCode()),
                                  QMessageBox::Ok|QMessageBox::Default);
            return false;
        }
        int bid;
        if(query.size() > 0){
            if(query.next())
                bid = query.value("maxBID").toInt();
        } else
            bid = 0;
        ++bid;
        //preparing expire date
        QString date ="20" + paymentDialog->yearBox->currentText()+ "-";
        QString tempDate = QString::number(paymentDialog->monthBox->currentIndex());
        if(tempDate.count() < 2)
            tempDate.insert(0, '0');
        date+=tempDate;
        date +="-01";

        bID = QString::number(bid);  //saving bank id to bID for offline saving
        //insert values into bankinfo
        custQuery1 += " values (" + QString::number(bid) + ",'" + paymentDialog->noaEdit->text() + "','" + paymentDialog->acTypeBox->currentText() + "','" +
                                        paymentDialog->bNameEdit->text() + "','" + paymentDialog->ifscEdit->text() + "','" +
                                        paymentDialog->bAddEdit->text() + "','" + paymentDialog->cvvEdit->text() + "','" + date + "','" + mDetail.getDID() + "');";

        //insert values into bankaccountno
        custQuery3 = "insert into BankAccountNo (BID, DCAccount) "
                     "values (" + QString::number(bid) + ",'" + paymentDialog->aNumberEdit->text() + "');";

        //insert values into produceraccount and consumeraccount

        custQuery2 += "  values ('"  +custDairyID + "'," + QString::number(bid) + ");";

        //username and password saving query in case of payment is register by user
        QString userPassQuery = "insert into UserPass (userName , userPass, custID) values ('" +
                userName + "','" + userPass + "','" + custDairyID + "');";

        //starting another transaction inside a transaction in case of payment is register by user
        QString allQuery = "START TRANSACTION; " +
                highCustIDBack + custQuery + custQuery1 + custQuery3 + custQuery2 + custQuery4 + userPassQuery
                 +" COMMIT; ";
        //custQuery for customer
        //custQuery1 for bankinfo
        //custQuery3 for customerAccount
        //custQuery2 for bankAccount
        //custQuery4 for customerpae

        if(!mydatabase.isOpen())
            connectDatabase();
        if(!query.exec(allQuery)){
            //do something here
            QSqlDatabase::database().commit();
            return false;
        } else{
            QSqlDatabase::database().commit();
            return true;
        }
    }

    //username and password saving query in case of payment is not register by user
    QString userPassQuery = "insert into UserPass (userName , userPass, custID) values ('" +
            userName + "','" + userPass + "','" + custDairyID + "');";

    //starting another transaction inside a transaction in case of payment is not register by user
    QString allQuery = "START TRANSACTION; " +
            highCustIDBack + custQuery + custQuery4 + userPassQuery
             +" COMMIT; ";
    //custQuery for customer
    //custQuery4 for customerpae

    if(!mydatabase.isOpen())
        connectDatabase();

    retry:
    if(!query.exec(allQuery)){
        int status = QMessageBox::critical(this,
                              tr("Connection Error! - %1").arg(qApp->applicationName()),
                              tr("Seems that you are not connected with internet.\n"
                                 "Please connect to the internet and try again."),
                              tr("&Cancel"), tr("Retry"), QString() , 0, 1);

        if(status == 1){
            goto retry;
        }
        QSqlDatabase::database().commit();
        return false;
    } else{
        QSqlDatabase::database().commit();
        return true;
    }
}

bool CustomerRegistration::generateCustId()
{
    QString st0;
    QString idType;
    if(this->type == "Producer"){
        st0 = "MP"; idType = "ProdID";
    } else {
        st0 = "MC"; idType = "ConsID";
    }
    QSqlQuery query(mydatabase);
    retry:
    //getting highest id for customer
    if(!mydatabase.isOpen())
        connectDatabase();
    if(!query.exec("SELECT * FROM HighOfDairy WHERE binary LocalDID = '" + mDetail.getDID() + "';")){
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(mydatabase.lastError().nativeErrorCode()),
                              tr("&Exit"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry;
        else{
            paymentDialog->rLoad(0);
            return false;
    }
    }
    QString prevCustID;
    QString newCustID;
    QString st1, st2;

    if(query.size() >0){
        if(query.next())
            prevCustID = query.value(idType).toString();
        //to insure that if one id is filled and other is not than handle it differently
        if (prevCustID.isEmpty()){
            st1 = mDetail.getDID()[2];
            st1 += mDetail.getDID()[3];
            st1 += mDetail.getDID()[4];
            st1 += mDetail.getDID()[5];
            st2 = "0001";
            newCustID = st0 + st1  + st2;

            //registering high id to the highofdairy
            highCustIDBack = "UPDATE HighOfDairy "
                             " set " + idType + " = '"+newCustID+"' where "
                             " LocalDID = '"+mDetail.getDID()+ "';";

            /*
             *
             * This query will be execute in transaction thats why it
             * is removed from here
             * do not include it here, first see the transaction
             * in userRegistration function
             *
             */
            //query.exec();
            this->custDairyID = newCustID;

            //saving data to database as all goes in right way
            if(saveData())
                return true;
            else
                return false;
            }

            st1 = prevCustID[2] ;
            st1+= prevCustID[3];
            st1 += prevCustID[4];
            st1 += prevCustID[5];
            st2 = prevCustID[6];
            st2 += prevCustID[7];
            st2 += prevCustID[8];
           st2 += prevCustID[9];


        int number = st2.toInt();
        if(number == 9999){
            QMessageBox::critical(this, tr("Limit Cross - %1").arg(qApp->applicationName()),
                                  tr("<qt><html><p>You have cross your limit.. Please Contact administrator\n\n</p>"
                                    "<p> Contact on +91 7568577487 or visit www.mds.helponline.in<p></html></qt>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            paymentDialog->rLoad(0);
            return false;
        } else
            number++;

        st2 = QString::number(number);
        if (st2.count() != 4){
            int num = 4 - st2.count();
            for(int i=0; i<num; i++){
                st2.insert(0, '0');
            }
        }
        newCustID = st0 + st1 + st2;

        //registered highe id back Highofdairy
        highCustIDBack = "UPDATE HighOfDairy"
                         " SET " + idType + " = '" + newCustID + "' "
                         " WHERE binary LocalDID = '" + mDetail.getDID() + "';";

        this->custDairyID = newCustID;
        /*
         *
         * This query will be execute in transaction thats why it
         * is removed from here
         * do not include it here, first see the transaction
         * in userRegistration function
         *

        query.exec("UPDATE HighOfDairy"
                   " SET " + idType + " = '" + newCustID + "' "
                   " WHERE LocalDID = '" + mDetail.getDID() + "';");
        */

        //saving data to database as all goes in right way
        if(saveData())
            return true;
        else
            return false;
    } else {
        st1 = mDetail.getDID()[2];
        st1 += mDetail.getDID()[3];
        st1 += mDetail.getDID()[4];
        st1 += mDetail.getDID()[5];
        st2 = "0001";
        newCustID = st0 + st1  + st2;

        //registering high id to the highofdairy
        highCustIDBack = "INSERT INTO HighOfDairy (LocalDID, ProdID, ConsID) "
                         "values ('" + mDetail.getDID() + "', ";
        //query.prepare("INSERT INTO HighOfDairy (LocalDID, ProdID, ConsID) "
        //           "values (?, ?, ?);");
        //query.bindValue(0, mDetail.getDID());
        if(st0 == "MP") {
            highCustIDBack  +="'" + newCustID + "',";
            highCustIDBack += "NULL);";
            //query.bindValue(1, newCustID);
           // query.bindValue(2, "");
        } else {
            highCustIDBack += "NULL, '" + newCustID + "');";
            //query.bindValue(1, "");
            //query.bindValue(2, newCustID);
        }

        /*
         *
         * This query will be execute in transaction thats why it
         * is removed from here
         * do not include it here, first see the transaction
         * in userRegistration function
         *
         */
        //query.exec();
        this->custDairyID = newCustID;

        //saving data to database as all goes in right way
        if(saveData())
            return true;
        else
            return false;
    }

}

void CustomerRegistration::generateUserName()
{
    this->userName = this->custDairyID;
}

void CustomerRegistration::generateCustPass()
{
    this->userPass = registrationDialog->pContactEdit->text();
}

void CustomerRegistration::completionMessage()
{
    regCompDialog = new RegistrationComplete;
    regCompDialog->setValue(registrationDialog->firstNameEdit->text() +" " +registrationDialog->lastNameEdit->text(),
                            userName, userPass, custDairyID, mDetail.getdName(), this->type);

    //connections of regCompDialog
    connect(regCompDialog, SIGNAL(okBye()),
            this, SLOT(bye()));
    connect(regCompDialog, SIGNAL(printSlip()),
            this, SLOT(printSlip()));
    //complete connections of regcompdialog

    paymentDialog->rLoad(0);
    paymentDialog->hide();
    registrationDialog->show();
    mainLayout->removeWidget(paymentDialog);
    mainLayout->addWidget(registrationDialog);

    //setting all widgets to empty
    regCompDialog->exec();
}

void CustomerRegistration::bye()
{
    delete regCompDialog;
    registrationDialog->setDefault();
    paymentDialog->setDefault();
}

void CustomerRegistration::printSlip()
{
    QString dString1 = tr("Congratulations! Registration Complete");
     QString dString2 = tr("%1").arg(mDetail.getdName());
    QString dString3 = tr("Dear, %1").arg(registrationDialog->firstNameEdit->text() + " " + registrationDialog->lastNameEdit->text());
    QString dString8 = QObject::tr("Your login information:  ");
    QString dString4 = tr("User Name:                  %1").arg(this->userName);
    QString dString5 = tr("Password:                     %1").arg(this->userPass);
    QString dString6 = tr("%1 ID No:               %2").arg(this->type).arg(this->custDairyID);
    QString dString7 = QObject::tr("Thank You, for registration Milk Dairy Management System ");
     QString dString9 = QObject::tr("www.mdsystem.co.in       +91 7568577487 ");
    QPrinter printer;
    printer.setOrientation(QPrinter::Landscape);
     printer.newPage();
     QPainter p(&printer);
     p.drawRect(10, 10, 180, 130);
     QPen pen;
     pen.setColor(Qt::green);
     p.setPen(pen);
     pen.setWidth(1);
     QFont font("MS Shell Dlg 2", 6);
     font.setStyle(QFont::StyleNormal);
     p.setFont(font);
     p.drawText(30, 25, dString1);
     QFont font1("MS Shell Dlg 2", 5);
     p.setFont(font1);
     pen.setColor(Qt::black);
     p.setPen(pen);
     p.drawText(30, 40, dString2);
     p.drawText(20, 55, dString3);
     p.drawText(20, 65, dString8);
     p.drawRect(40, 70, 130, 35);
     p.drawText(50, 80, dString4);
     p.drawText(50, 90, dString5);
     p.drawText(50, 100, dString6);
     QRectF rect(20, 110, 170, 25);
     p.drawText(rect, dString7);
     p.setPen(Qt::blue);
     font1.setWeight(4);
     QRectF rect1(50, 125, 150, 25);
     p.drawText(rect1, dString9);
     p.end();
    registrationDialog->setDefault();
    paymentDialog->setDefault();
}

void CustomerRegistration::sentMail(QString to, QString custName)
{
    QString tf, sb;

    if(this->type == "Producer"){
        tf = "to";
        sb = "sell";
    } else {
        tf = "from";
        sb = "buy";
    }

    QString subject = tr("Registeration Complete!");

    QString message = tr("                                                     Congratulations!\n\n\n"
                                           "                            Dear %1. Thank You for the registration with MDS\n\n"
                                          "You are registered with Milk Dairy Management System as a %2 on dairy %3. Using your"
                                          " %4 ID you can %5 milk %6 %7.\n\n"
                                          "You are now also a user of Milk Dairy Management System, you can login to MDS android "
                                          "app and website by your user name and password listed below. Now you can easily see "
                                          "your daily milk data on your phone any where - any time. Use our android app.\n\n\n"
                                          "                                          Your registration information:\n\n"
                                          "You are registered with %8 Dairy.\n\n"
                                          "                                                        User Name:         %9\n"
                                          "                                                        Password:            %10\n"
                                          "                                                        %11 ID:           %12\n"
                                          "Enjoy our Services. For further inquiry, please visit our "
                                          "website 'www.msysdairy.com' or call us on '+91 %13'."
                ).arg(custName)
            .arg(this->type)
            .arg(mDetail.getdName())
            .arg(this->type)
            .arg(sb)
            .arg(tf)
            .arg(mDetail.getdName())
            .arg(mDetail.getdName())
            .arg(this->userName)
            .arg(this->userPass)
            .arg(this->type)
            .arg(this->custDairyID)
           .arg(mDetail.getpc());

    Smtp *smtp = new Smtp(oDetail.getHostEmail(), oDetail.getHostEmailPass(), "smtp.gmail.com");

    //sending message to client
    smtp->sendMail(oDetail.getHostEmail(), to , subject,message);

}
