#include "transportedit.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QSqlError>

TransportEdit::TransportEdit(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    //loading initializing
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //initializing model
    model = new QSqlQueryModel;
    stringModel = new QStringListModel;

    //initializing mapper
    mapper = new QDataWidgetMapper(this);

    //initializing completer
    completer = new QCompleter(this);

    //setting connections
    connect(updateButton, SIGNAL(clicked(bool)),
            this, SLOT(updatePressed()));
    connect(idButton, SIGNAL(clicked(bool)),
            this, SLOT(showID()));
    connect(listView, SIGNAL(currentRowChanged(int)),
            this, SLOT(transportChanged(int)));
    connect(goButton, SIGNAL(clicked(bool)),
            this, SLOT(doSearching()));
    connect(newTransButton, SIGNAL(clicked(bool)),
            this, SLOT(registerNew()));
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    //connections are set

    setWidgets();
}

void TransportEdit::setWidgets()
{
    //setting stylesheet for all line edit
    firstNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    middleNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    lastNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    sContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    licenseEdit->setStyleSheet(gDetail.getNormalStylesheet());
    vehicalEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //setting of stylesheet is completed

    //setting validator to all line edit
    QRegExp nameRegExp("[A-Za-z]{20}");
    QRegExpValidator *nameValidator = new QRegExpValidator(nameRegExp, this);
    firstNameEdit->setValidator(nameValidator);
    middleNameEdit->setValidator(nameValidator);
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

    //setting mapper for widgets
    mapper->setModel(model);
    mapper->addMapping(firstNameEdit,2);
    mapper->addMapping(middleNameEdit, 3);
    mapper->addMapping(lastNameEdit, 4);
    mapper->addMapping(pContactEdit, 5);
    mapper->addMapping(sContactEdit, 6);
    mapper->addMapping(licenseEdit, 7);
    mapper->addMapping(vehicalEdit, 8);

    //querying by model
    modelQuery();

    //settting completer

    completer->setModel(stringModel);
    completer->setMaxVisibleItems(10);
    completer->setWrapAround(true);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    searchEdit->setCompleter(completer);

    QStringList stringList;
    for(int row=0; row < model->rowCount(); row++){
        stringList << model->data(model->index(row, 0)).toString();
        stringList << model->data(model->index(row, 1)).toString();
        stringList << model->data(model->index(row, 5)).toString();
    }

    stringModel->setStringList(stringList);

    if(model->rowCount() == 0) {
        editSetting(0);
    } else {
        editSetting(1);
    }

    listView->setCurrentRow(0);
}

void TransportEdit::editSetting(int i)
{
    if(i == 1) {
        firstNameEdit->setEnabled(true);
        middleNameEdit->setEnabled(true);
        lastNameEdit->setEnabled(true);
        pContactEdit->setEnabled(true);
        sContactEdit->setEnabled(true);
        licenseEdit->setEnabled(true);
        vehicalEdit->setEnabled(true);
        idButton->setEnabled(true);
        updateButton->setEnabled(true);
    } else {
        firstNameEdit->setEnabled(false);
        middleNameEdit->setEnabled(false);
        lastNameEdit->setEnabled(false);
        pContactEdit->setEnabled(false);
        sContactEdit->setEnabled(false);
        licenseEdit->setEnabled(false);
        vehicalEdit->setEnabled(false);
        idButton->setEnabled(false);
        updateButton->setEnabled(false);
    }
}

void TransportEdit::modelQuery()
{
    for(int row=0; row< model->rowCount(); row++){
        model->removeRow(row);
    }

    //setting list view
    for(int row = 0; row<listView->count(); row++){
        listView->model()->removeRows(0, model->rowCount());
    }

    QString queryString = "select TransID, concat_ws(' ',DrivFName, DrivMName, DrivLName), DrivFName,"
                          "DrivMName, DrivLName, Pcontact, Scontact, DLicenseNo, VehicleNo from Transport "
                          "where LocalDID = '"+mDetail.getDID()+"';";

    //connect database if not connected

    if(!myDatabase.isOpen()){
        if(!connectDatabase())
            return;
    }

    model->setQuery(queryString, myDatabase);
    for(int row=0; row < model->rowCount(); row++){
        listView->addItem("("+model->data(model->index(row, 0)).toString()+") "+
                          model->data(model->index(row, 1)).toString());
    }
    countLabel->setText(tr("Total: (%1) Members").arg(model->rowCount()));
}

void TransportEdit::updatePressed()
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
    } else {
        updateValue();
    }
}

void TransportEdit::updateValue()
{
    rLoad(1);
    if(!myDatabase.isOpen()){
        if(!connectDatabase()){
            rLoad(0);
            return;
        }
    }

    QSqlQuery query(myDatabase);
    QString updateQuery;
    updateQuery = " UPDATE Transport SET "
                   " DrivFName = '"+firstNameEdit->text() +"', "
                   " DrivMName = '" +middleNameEdit->text()+"', "
                   " DrivLName = '" +lastNameEdit->text() + "', "
                   " Pcontact = '"+pContactEdit->text() +"', "
                   " Scontact = '"+sContactEdit->text() + "', "
                   " DLicenseNo = '"+licenseEdit->text() +"', "
                   " VehicleNo = '" +vehicalEdit->text() + "' "
                   " where TransID = "+model->data(model->index(listView->currentRow(), 0)).toString()+" and "
                   " LocalDID = '"+mDetail.getDID()+"';";
    if(!query.exec(updateQuery)){
        QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service."
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(query.lastError().text()),
                              QMessageBox::Ok | QMessageBox::Default);
        rLoad(0);
        return;
    } else {
        QTimer::singleShot(2000, this, SLOT(showMessage()));
        OfflineTransport::editOffline(model->data(model->index(listView->currentRow(), 0)).toString(),firstNameEdit->text(),
                                      middleNameEdit->text(), lastNameEdit->text(),pContactEdit->text(), sContactEdit->text(),
                                      licenseEdit->text(), vehicalEdit->text());
    }
}

void TransportEdit::showMessage()
{
    rLoad(0);
    int ind = listView->currentRow();
    QMessageBox::information(this, tr("Information Updated! - %1").arg(qApp->applicationName()),
                             tr("Your information is updated successfully."),
                             QMessageBox::Ok | QMessageBox::Default);
    modelQuery();
    listView->setCurrentRow(ind);
}

void TransportEdit::doSearching()
{
    QString temp = searchEdit->text();
    int row = 0;
    while (row < model->rowCount()){
        if(temp == model->data(model->index(row, 0)).toString()){
            listView->setCurrentRow(row);
            listView->currentRowChanged(row);
            return ;
        }
        row++;
    }

    row = 0;
    while (row < model->rowCount()){
        if(temp == model->data(model->index(row, 1)).toString()){
            listView->setCurrentRow(row);
            listView->currentRowChanged(row);
            return ;
        }
        row++;
    }

    row = 0;
    while (row < model->rowCount()){
        if(temp == model->data(model->index(row, 5)).toString()){
            listView->setCurrentRow(row);
            listView->currentRowChanged(row);
            return ;
        }
        row++;
    }

    QMessageBox::information(this, tr("Not Found! - %1").arg(qApp->applicationName()),
                             tr("%1 is not found in database...").arg(temp),
                             QMessageBox::Ok|QMessageBox::Default);
}

bool TransportEdit::connectDatabase()
{
    if(!myDatabase.contains("transEdit")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "transEdit");
        myDatabase.setHostName(oDetail.getHostName());
        myDatabase.setUserName(oDetail.getUserName());
        myDatabase.setPassword(oDetail.getUserPass());
        myDatabase.setDatabaseName(oDetail.getDatabase());
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

void TransportEdit::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("transEdit");
}

void TransportEdit::transportChanged(int row)
{
    if(!firstNameEdit->isEnabled()){
        firstNameEdit->setEnabled(true);
        middleNameEdit->setEnabled(true);
        lastNameEdit->setEnabled(true);
        pContactEdit->setEnabled(true);
        sContactEdit->setEnabled(true);
        licenseEdit->setEnabled(true);
        vehicalEdit->setEnabled(true);
        idButton->setEnabled(true);
        updateButton->setEnabled(true);
    }

    //setting stylesheet for all line edit
    firstNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    middleNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    lastNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    sContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    licenseEdit->setStyleSheet(gDetail.getNormalStylesheet());
    vehicalEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //setting of stylesheet is completed

    mapper->toFirst();

    for(int jump = 0; jump < row; jump++){
        mapper->toNext();
    }
}

void TransportEdit::rLoad(int i)
{
    if(i == 1){
        searchEdit->setEnabled(false);
        listView->setEnabled(false);
        firstNameEdit->setEnabled(false);
        middleNameEdit->setEnabled(false);
        lastNameEdit->setEnabled(false);
        pContactEdit->setEnabled(false);
        sContactEdit->setEnabled(false);
        licenseEdit->setEnabled(false);
        vehicalEdit->setEnabled(false);
        newTransButton->setEnabled(false);
        idButton->setEnabled(false);
        updateButton->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 - 64;
        loadingLabel->setGeometry(x, y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        searchEdit->setEnabled(true);
        listView->setEnabled(true);
        firstNameEdit->setEnabled(true);
        middleNameEdit->setEnabled(true);
        lastNameEdit->setEnabled(true);
        pContactEdit->setEnabled(true);
        sContactEdit->setEnabled(true);
        licenseEdit->setEnabled(true);
        vehicalEdit->setEnabled(true);
        newTransButton->setEnabled(true);
        idButton->setEnabled(true);
        updateButton->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}

void TransportEdit::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}

void TransportEdit::showID()
{
    QMessageBox::information(this,
                             tr("%1 - %2").arg(listView->currentItem()->text()).arg(qApp->applicationName()),
                             tr("<qt><h3>Transportation ID: <font color=\"red\"><b>%1</b></font></h3></qt>").arg(model->data(model->index(listView->currentRow(), 0)).toString()),
                             QMessageBox::Ok | QMessageBox::Default);
}

void TransportEdit::registerNew()
{
    newTransport = new NewTransport(this);
    newTransport->exec();
    delete newTransport;
    modelQuery();
    listView->setCurrentRow(0);
}

void TransportEdit::cancelPressed()
{
    disconnectDatabase();
    this->close();
}

TransportEdit::~TransportEdit()
{
    disconnectDatabase();
}
