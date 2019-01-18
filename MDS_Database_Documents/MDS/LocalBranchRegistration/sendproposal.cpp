#include "sendproposal.h"
#include "picloadingdelegate.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QTimer>
#include "../CustomerRegistration/smtp.h"
SendProposal::SendProposal(QWidget *parent)
    : QWidget(parent)
{
    //set ui to sendproposal
    setupUi(this);

    //loading
    loadingLabel = new QLabel(this);
    loading = new QMovie(uc.loadImage1);
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //set attribute or property of send proposal
    setAttribute(Qt::WA_DeleteOnClose);

    //setting query model
    queryModel = new MySqlQuery;

    //setting basic mapper
    mapper = new QDataWidgetMapper(this);

    //connections of send proposal
    connect(goButton, SIGNAL(clicked(bool)),
            this, SLOT(goPressed()));
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(closeIt()));
    connect(sendButton, SIGNAL(clicked(bool)),
            this, SLOT(sendPressed()));
    //connections of send proposal is completed

    setWidgets();
}

void SendProposal::setWidgets()
{
    SNLabel->hide();
    EDLabel->hide();
    CNLabel->hide();
    ALabel->hide();
    secNameLabel->hide();
    estDateLabel->hide();
    contactLabel->hide();
    addressLabel->hide();
    sendButton->setEnabled(false);
    logoLabel->hide();
    dairyNameLabel->hide();
    tagLabel->hide();
    pContactLabel->hide();

    //setting properties of mapper
    PicLoadingDelegate *delegate = new PicLoadingDelegate(mapper);
    mapper->setModel(queryModel);
    mapper->setItemDelegate(delegate);
    mapper->addMapping(logoLabel, 0);
    mapper->addMapping(dairyNameLabel, 1, "text");
    mapper->addMapping(tagLabel, 2, "text");
    mapper->addMapping(estDateLabel, 3, "text");
    mapper->addMapping(pContactLabel, 4, "text");
    mapper->addMapping(contactLabel, 5, "text");
    mapper->addMapping(addressLabel, 6, "text");
    mapper->addMapping(secNameLabel, 7, "text");

    //setting header of the query model
    queryModel->setHeaderData(0, Qt::Horizontal, "Logo");
    queryModel->setHeaderData(1, Qt::Horizontal, "Name");
    queryModel->setHeaderData(2, Qt::Horizontal, "Tag");
    queryModel->setHeaderData(3, Qt::Horizontal, "Primary Contact");
    queryModel->setHeaderData(4, Qt::Horizontal, "Secondary Contact");
    queryModel->setHeaderData(5, Qt::Horizontal, "Address");
    queryModel->setHeaderData(6, Qt::Horizontal, "Secratary");
}

bool SendProposal::connectDatabase()
{
    if(!myDatabase.contains("remoteDBase")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "remoteDBase");
        myDatabase.setHostName(uc.hostName);
        myDatabase.setUserName(uc.databaseUName);
        myDatabase.setPassword(uc.databaseUPass);
        myDatabase.setDatabaseName(uc.dataBase);
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

void SendProposal::goPressed()
{
    toDairy = DairyIDEdit->text();
    if(toDairy == uc.dairyID){
        QMessageBox::information(this, tr("Opps! It's You - %1").arg(qApp->applicationName()),
                                 tr("Your dairy can not be the branch of itself. Please do not judge us!"),
                                 QMessageBox::Ok | QMessageBox::Default);
        disconnectDatabase();
        return;
    }
    if(!myDatabase.isOpen()){
        if(!connectDatabase())
            return;
    }

    queryModel->setQuery("select "
                         "dairy.Logo, dairy.Name, dairy.Tagline, dairy.EstDate, dairyOwner.PContact, dairyOwner.SContact, concat_ws(' ', dairy.Street,"
                         "dairy.City, dairy.State, dairy.Pincode), concat_ws(' ', dairyOwner.DOFName, dairyOwner.DOMName, dairyOwner.DOLName) "
                         "from dairy, dairyOwner, dairyOwnerLog"
                         " where binary dairy.LocalDID  = dairyOwnerLog.LocalDID and "
                         " binary dairyOwnerLog.OwnerID  = dairyOwner.OwnerID  and "
                         " binary dairy.LocalDID = '" + DairyIDEdit->text() + "';", myDatabase);

    mapper->toFirst();

    if(!myDatabase.isOpen()){
        if(!connectDatabase())
            return;
    }
    QSqlQuery query(myDatabase);
    if(!query.exec("select Email_id from dairyWPED where binary LocalDID = '" + toDairy + "';")){
    } else {
        if(query.size() > 0){
            if(query.next())
                dairyEmail = query.value("Email_id").toString();
        }
    }

    //show all widgets to user

    if(queryModel->hasIndex(0,0)){
        SNLabel->show();
        EDLabel->show();
        CNLabel->show();
        ALabel->show();
        secNameLabel->show();
        estDateLabel->show();
        contactLabel->show();
        addressLabel->show();
        sendButton->setEnabled(true);
        logoLabel->show();
        dairyNameLabel->show();
        tagLabel->show();
        pContactLabel->show();
    } else {
        SNLabel->hide();
        EDLabel->hide();
        CNLabel->hide();
        ALabel->hide();
        secNameLabel->hide();
        estDateLabel->hide();
        contactLabel->hide();
        addressLabel->hide();
        sendButton->setEnabled(false);
        logoLabel->hide();
        dairyNameLabel->hide();
        tagLabel->hide();
        pContactLabel->hide();

        //send message to user about dairy is not present

        QMessageBox::information(this, tr("Incorrect Dairy ID - %1").arg(qApp->applicationName()),
                                 tr("Incorrect Dairy ID !\n\n"
                                    "Please Enter any valid Dairy ID or Only enter ID of Dairy which registered with Milk Dairy Management System"),
                                 QMessageBox::Ok|QMessageBox::Default);
    }
}

void SendProposal::closeIt()
{
    delete queryModel;
    disconnectDatabase();
    this->close();
}


void SendProposal::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("remoteDBase");
}

void SendProposal::sendPressed()
{
    rLoad(1);
    int status = QMessageBox::question(this, tr("Proposal Confirmation Box - %1").arg(qApp->applicationName()),
                                       tr("Do you want to send proposal to %1 to make his/her dairy %2 in a local branch of yours ?")
                                       .arg(secNameLabel->text()).arg(dairyNameLabel->text()),
                                       tr("Yes, Send Proposal !"), tr("No, Do not send Proposal !"), QString(), 0, 1);
    if(status == 1){
        disconnectDatabase();
        rLoad(0);
        return ;
    }

    QSqlQuery query(myDatabase);
    QString queryString = "insert into dairyrequestlog (SendDateTime, SendDairy, ToDairy, IsDeniedAccept, AcceptDeniedDate, RForHD) values ('2018-01-01 00:00:00', '" +
            uc.dairyID + "','" + toDairy + "','0', '0000-00-00 00:00:00', '0');";

    if(!myDatabase.isOpen()){
        if(!connectDatabase()){
            rLoad(0);
            return;
        }
    }

    if(query.exec("select SendDateTime, SendDairy, ToDairy, IsDeniedAccept "
                   "from DairyRequestLog "
                   "where binary SendDairy = '" + uc.dairyID + "'  and binary ToDairy = '" + toDairy +"';")){
        if(query.size()>0){
            while(query.next()){
                if(query.value("IsDeniedAccept").toString() == "0"){
                    //you already have sent proposal to the dairy
                    QMessageBox::information(this, tr("Wait for Respond! - %1").arg(qApp->applicationName()),
                                             tr("Dear Secratary!, Please wait till dairy respond.\nYou already have sent proposal to this dairy on %1 and it doesn't respond to your proposal yet so please"
                                                " tell them to accept your proposal.\n\nThank You!")
                                             .arg(query.value("SendDateTime").toString()),
                                             QMessageBox::Ok | QMessageBox::Default);
                    disconnectDatabase();
                    rLoad(0);
                    return;
                } else if(query.value("IsDeniedAccept").toString() == "1") {
                    //this dairy is already a local branch of yours
                    QMessageBox::information(this, tr("Proposal Failed! - %1").arg(qApp->applicationName()),
                                             tr("Dear Secratary!, You are trying to send proposal to you local branch which is not permissible."
                                                "You may send proposal to the dairies which are not your local branch.\n\nThank You!"),
                                             QMessageBox::Ok | QMessageBox::Default);
                    disconnectDatabase();
                    rLoad(0);
                    return;
                }
            }
        }
    } else {
        //network connection problem message
        disconnectDatabase();
    }

    //myDatabase.database("remoteDBase").transaction();
    if(!query.exec(queryString)){
        //network connection problem message
        disconnectDatabase();
        rLoad(0);
        return;
    }

   //myDatabase.commit();
    disconnectDatabase();
    //sending mail to the dairy for information
    sendMail();
    //message sending is complete, now show message to user that his proposal is sent to the dairy he/she want
    QTimer::singleShot(10000, this, SLOT(showMessage()));
}

void SendProposal::showMessage()
{
    QMessageBox::information(this, tr("Message Sent! - %1").arg(qApp->applicationName()),
                             tr("Dear Secratary!, Your proposal has been sent to the dairy with id : %1, wait till the reciepant dairy will take action on your proposal\n\nThank You!")
                             .arg(toDairy), QMessageBox::Ok|QMessageBox::Default);
    disconnectDatabase();
    rLoad(0);
}

void SendProposal::sendMail()
{
    QString subject = tr("Branch Registration Proposal!");

    QString message = tr("Dear Secratary, \n"
                         "This is a mail from %1. We want that you could register with us as an our branch "
                         "You can do this just by accepting our proposal. We give you and your customer 2% consetion on each litre of milk."
                         " And we are very sure that our services will not frustrate you."
                         "\nThank You!\n"
                         "\nvisit our website %2 or call us on +91%3.").arg(uc.dairyName)
            .arg(uc.dairyWebsite)
            .arg(uc.dairyMobNo);
    Smtp *smtp = new Smtp(uc.hostEmail, uc.hostEPass, "smtp.gmail.com");

    //sending message to dairy
    smtp->sendMail(uc.hostEmail, dairyEmail ,subject, message);
}

void SendProposal::rLoad(int i)
{
    if(i == 1){
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 -64;
        loadingLabel->setGeometry(x,y, 128, 128);
        loadingLabel->show();
        loading->start();
        DairyIDEdit->setEnabled(false);
        goButton->setEnabled(false);
        cancelButton->setEnabled(false);
        sendButton->setEnabled(false);
    } else {
        DairyIDEdit->setEnabled(true);
        goButton->setEnabled(true);
        cancelButton->setEnabled(true);
        sendButton->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}
