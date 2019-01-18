#include "newtransport.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>

NewTransport::NewTransport(QWidget *parent)
    : QDialog(parent)
{
    //setting up ui
    setupUi(this);

    //loading
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //setting connections of buttons
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    connect(addButton, SIGNAL(clicked(bool)),
            this, SLOT(addPressed()));
    //all connections are done

    setWidgets();
}

void NewTransport::setWidgets()
{
    //setting style sheet to all line edit
    firstNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    secondNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    lastNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    sContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    licenseEdit->setStyleSheet(gDetail.getNormalStylesheet());
    vehicalEdit->setStyleSheet(gDetail.getNormalStylesheet());

    //setting validator to all line edit
    QRegExp nameRegExp("[A-Za-z]{20}");
    QRegExpValidator *nameValidator = new QRegExpValidator(nameRegExp, this);
    firstNameEdit->setValidator(nameValidator);
    secondNameEdit->setValidator(nameValidator);
    lastNameEdit->setValidator(nameValidator);

    QRegExp contactRegExp("[0-9]{10}");
    QRegExpValidator *contactValidator = new QRegExpValidator(contactRegExp, this);
    pContactEdit->setValidator(contactValidator);
    sContactEdit->setValidator(contactValidator);

    QRegExp licenseRegExp("[0-9A-Za-z]{30}");
    QRegExpValidator *licenseValidator = new QRegExpValidator(licenseRegExp, this);
    licenseEdit->setValidator(licenseValidator);

    QRegExp vehicalRegExp("[0-9a-zA-Z ]{30}");
    QRegExpValidator *vehicalValidator = new QRegExpValidator(vehicalRegExp, this);
    vehicalEdit->setValidator(vehicalValidator);
}

void NewTransport::rLoad(int i)
{
    if(i == 1){
        firstNameEdit->setEnabled(false);
        secondNameEdit->setEnabled(false);
        lastNameEdit->setEnabled(false);
        pContactEdit->setEnabled(false);
        sContactEdit->setEnabled(false);
        licenseEdit->setEnabled(false);
        vehicalEdit->setEnabled(false);
        addButton->setEnabled(false);
        cancelButton->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 -64;
        loadingLabel->setGeometry(x,y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        firstNameEdit->setEnabled(true);
        secondNameEdit->setEnabled(true);
        lastNameEdit->setEnabled(true);
        pContactEdit->setEnabled(true);
        sContactEdit->setEnabled(true);
        licenseEdit->setEnabled(true);
        vehicalEdit->setEnabled(true);
        addButton->setEnabled(true);
        cancelButton->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}

bool NewTransport::connectDatabase()
{
    if(!myDatabase.contains("newTrans")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "newTrans");
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
                              tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry;
        else{
            return false;
    }
 }
    return true;
}

void NewTransport::disconnectDatabase()
{
    //removing database connection from  the QSqlDatabase
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("newTrans");
}

void NewTransport::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}

void NewTransport::cancelPressed()
{
    disconnectDatabase();
    this->close();
}

void NewTransport::addPressed()
{
    rLoad(1);

    QString error;
    //checking for error
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
    if(firstNameEdit->text().isEmpty()) {
        error = tr("Please enter driver first name");
        firstNameEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }

    if(!error.isEmpty()){
        rLoad(0);
        QMessageBox::information(this,
                                 tr("Error Encountered! - %1").arg(qApp->applicationName()),
                                 tr("<qt><p>Enter required detail:</p><p>"
                                    "%1</p></qt>").arg(error),
                                 QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    if(!myDatabase.isOpen()) {
        rLoad(0);
        if(!connectDatabase()) {
            return;
        }
        rLoad(1);
    }

    QSqlQuery query(myDatabase);
    QString getTransID = "select max(TransID) as TransID from Transport;";
    QSqlDatabase::database("newTrans").transaction();

    if(!query.exec(getTransID)){
        rLoad(0);
        QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(query.lastError().nativeErrorCode()),
                              QMessageBox::Ok|QMessageBox::Default);
        return ;
    }

    if(query.size()>0) {
        if(query.next()) {
            this->transID = query.value("TransID").toString();
        } else {
            this->transID = "0";
        }
    } else {
        this->transID = "0";
    }

    int tmp = this->transID.toInt();
    tmp++;
    this->transID = QString::number(tmp);

    QString queryString = "INSERT INTO Transport(TransID, VehicleNo, DrivFName, DrivMName, "
                          "DrivLName, DLicenseNo, Pcontact, Scontact, LocalDID) VALUES ( " + this->transID+",'"+
            vehicalEdit->text()+"','"+firstNameEdit->text()+"','"+secondNameEdit->text()+"','"+lastNameEdit->text()+
            "','" + licenseEdit->text()+"','"+pContactEdit->text()+"','"+sContactEdit->text()+"','"+mDetail.getDID()+"');";
    if(!query.exec(queryString)){
        rLoad(0);
        QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(query.lastError().nativeErrorCode()),
                              QMessageBox::Ok|QMessageBox::Default);
        return ;
    }
    QSqlDatabase::database("newTrans").commit();

    QTimer::singleShot(2000, this, SLOT(showMessage()));
    OfflineTransport::registerOffline(this->transID, firstNameEdit->text(), secondNameEdit->text(),
                                      lastNameEdit->text(), pContactEdit->text(), sContactEdit->text(),
                                      licenseEdit->text(), vehicalEdit->text());
}

void NewTransport::showMessage()
{
    rLoad(0);
    QMessageBox::information(this,
                             tr("Update Successful! : %1").arg(qApp->applicationName()),
                             tr("New Transport is registered with dairy successfully on server.\n"
                                "For any query please visit 'www.mds.com'."),
                             QMessageBox::Ok);
    disconnectDatabase();
    cancelPressed();
}

NewTransport::~NewTransport()
{
    disconnectDatabase();
}
