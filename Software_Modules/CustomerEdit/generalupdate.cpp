#include "generalupdate.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QKeyEvent>
#include "../CustomerRegistration/smtp.h"
#include <QDebug>
#include <QTimer>
#include <QSqlError>

GeneralUpdate::GeneralUpdate(QString type, QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    this->type = type;

    adhaarEdit->setEnabled(false);

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
    connect(showPaymentButton, SIGNAL(clicked(bool)),
            this, SLOT(showPayment()));
    connect(listView, SIGNAL(currentRowChanged(int)),
            this, SLOT(customerChanged(int )));
    //connections are set

    //hide gender label and radio buttons
    genderLabel->hide();
    maleButton->hide();
    femaleButton->hide();

    //setting event filter to searchEdit
    searchEdit->installEventFilter(this);

    setWidgets();
}

void GeneralUpdate::setWidgets()
{
    //setting title text
    titleLabel->setText(tr("<html><center><p>Update %1 Information</p></center></html>").arg(this->type));
    //setting title text completed

    //setting stylesheet for all line edit
    firstNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    middleNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    lastNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    adhaarEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    sContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    emailEdit->setStyleSheet(gDetail.getNormalStylesheet());
    line1Edit->setStyleSheet(gDetail.getNormalStylesheet());
    line2Edit->setStyleSheet(gDetail.getNormalStylesheet());
    pincodeEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //setting of stylesheet is completed

    //setting validator for line edit
    QRegExp nameRegExp("[A-Za-z]{20}");
    QRegExpValidator *nameValidator = new QRegExpValidator(nameRegExp, this);
    firstNameEdit->setValidator(nameValidator);
    middleNameEdit->setValidator(nameValidator);
    lastNameEdit->setValidator(nameValidator);

    QRegExp adharRegExp("[0-9]{12}");
    QRegExpValidator *adharValidator = new QRegExpValidator(adharRegExp, this);
    adhaarEdit->setValidator(adharValidator);

    QRegExp contactRegExp("[0-9]{10}");
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

    //setting of all validator is completed

    //setting mapper for widgets
    mapper->setModel(model);
    mapper->addMapping(firstNameEdit,1);
    mapper->addMapping(middleNameEdit, 2);
    mapper->addMapping(lastNameEdit, 3);
    mapper->addMapping(adhaarEdit, 4);
    mapper->addMapping(pContactEdit, 5);
    mapper->addMapping(sContactEdit, 6);
    mapper->addMapping(emailEdit, 7);
    mapper->addMapping(line1Edit, 8);
    mapper->addMapping(line2Edit, 9);
    mapper->addMapping(stateBox, 10, "currentIndex");
    mapper->addMapping(pincodeEdit, 11);
    mapper->addMapping(androidBox, 12, "currentIndex");

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
        stringList << model->data(model->index(row, 13)).toString();
    }

    stringModel->setStringList(stringList);

    if(model->rowCount() == 0) {
        editSetting(0);
    } else {
        editSetting(1);
    }
}

void GeneralUpdate::editSetting(int i)
{
    if(i == 1) {
        firstNameEdit->setEnabled(true);
        middleNameEdit->setEnabled(true);
        lastNameEdit->setEnabled(true);
        adhaarEdit->setEnabled(true);
        pContactEdit->setEnabled(true);
        sContactEdit->setEnabled(true);
        line1Edit->setEnabled(true);
        line2Edit->setEnabled(true);
        stateBox->setEnabled(true);
        pincodeEdit->setEnabled(true);
        androidBox->setEnabled(true);
        emailEdit->setEnabled(true);
        showPaymentButton->setEnabled(true);
        updateButton->setEnabled(true);
    } else {
        firstNameEdit->setEnabled(false);
        middleNameEdit->setEnabled(false);
        lastNameEdit->setEnabled(false);
        adhaarEdit->setEnabled(false);
        pContactEdit->setEnabled(false);
        sContactEdit->setEnabled(false);
        line1Edit->setEnabled(false);
        line2Edit->setEnabled(false);
        stateBox->setEnabled(false);
        pincodeEdit->setEnabled(false);
        androidBox->setEnabled(false);
        emailEdit->setEnabled(false);
        showPaymentButton->setEnabled(false);
        updateButton->setEnabled(false);
    }
}

void GeneralUpdate::modelQuery()
{
    for(int row=0; row< model->rowCount(); row++){
        model->removeRow(row);
    }

    //setting list view
    for(int row = 0; row<listView->count(); row++){
        listView->model()->removeRows(0, model->rowCount());
    }

    QString queryString;
    if(this->type == "Producer"){
        queryString = "select concat_ws(' ',Producer.ProdFName, Producer.ProdMName, Producer.ProdLName ), Producer.ProdFName, Producer.ProdMName, Producer.ProdLName, ProducerPAE.AdhaarNo, "
                      "Producer.Pcontact, Producer.Scontact,Producer.Email_ID, Producer.Street, Producer.City, Producer.State, Producer.Pincode,"
                      "Producer.IsApp, Producer.ProdID "
                      "from Producer, ProducerPAE "
                      "where binary Producer.ProdID = ProducerPAE.ProdID and "
                      " binary Producer.LocalDID = '" + mDetail.getDID() + "' Order By Producer.ProdFName ASC;";
    } else {
        queryString = "select concat_ws(' ', Consumer.ConsFName, Consumer.ConsMName, Consumer.ConsLName), Consumer.ConsFName, Consumer.ConsMName, Consumer.ConsLName, ConsumerPAE.AdhaarNo,"
                      "Consumer.Pcontact, Consumer.Scontact, Consumer.Email_ID, Consumer.Street, Consumer.City, Consumer.State, Consumer.Pincode,"
                      "Consumer.IsApp, Consumer.ConsID "
                      "from Consumer, ConsumerPAE "
                      "where binary Consumer.ConsID = ConsumerPAE.ConsID and "
                      "binary Consumer.LocalDID = '" + mDetail.getDID() + "' Order By Consumer.ConsFName ASC;";
    }


    //connect database if not connected

    if(!myDatabase.isOpen()){
        if(!connectDatabase())
            return;
    }

    model->setQuery(queryString, myDatabase);

    for(int row=0; row < model->rowCount(); row++){
        listView->addItem(model->data(model->index(row, 0)).toString());
    }
}

void GeneralUpdate::updatePressed()
{
    QString error;
    if(pincodeEdit->text().isEmpty() || pincodeEdit->text().count() < 6) {
        error = tr("Pincode must be 6 digit number");
        pincodeEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(stateBox->currentIndex() == 0) {
        error = tr("please select any state");
    }
    if(line1Edit->text().isEmpty() || line2Edit->text().isEmpty()) {
        error = tr("Please enter your address to address line");
        line1Edit->setStyleSheet(gDetail.getErrorStylesheet());
        line2Edit->setStyleSheet(gDetail.getErrorStylesheet());
    }

    if(! (emailEdit->text().isEmpty())) {
        if(!(emailEdit->text().contains('@')) || !(emailEdit->text().contains(".com"))){
            error = tr("Please enter valid email ID");
            emailEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(emailEdit->text().count('@') > 1 || emailEdit->text().count('.') > 1) {
            error = tr("Please enter valid email ID");
            emailEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    }
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
    if(adhaarEdit->text().isEmpty() || adhaarEdit->text().count() != 12) {
        error = tr("Please enter valid adhar card no");
        adhaarEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }

    if(firstNameEdit->text().isEmpty()) {
        error = tr("First name can not be empty");
        firstNameEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }

    if(error.isEmpty()){
        updateValue();
    } else {

        QMessageBox::information(this, tr("Enter Correct Value - %1").arg(qApp->applicationName()),
                                 tr("%1").arg(error),
                                 QMessageBox::Ok|QMessageBox::Default);
    }
}

void GeneralUpdate::updateValue()
{
    rLoad(1);
    if(!myDatabase.isOpen()){
        if(!connectDatabase()){
            rLoad(0);
            return;
        }
    }

    /*
     * cancelling adhaar card updation for
     * undefined time
     * so don't consider this code as working
     * but it is important for future use
     * this code is not working as expected
     * Thank You
     */
    /*
    QString queryString, cust="";
    if(this->type== "Producer"){
        cust = "ProdID";
        queryString = "select ProdID, AdhaarNo from "
                      "producerpae "
                      "where binary ProdID <> '" + model->data(model->index(listView->currentRow(), 13)).toString() + "'"
                                                                                                                      " and AdhaarNo = '" + adhaarEdit->text() +"';";
    } else {
        cust = "ConsID";
        queryString = "select ConsID, AdhaarNo from "
                      "consumerpae "
                      "where binary ConsID <> '" + model->data(model->index(listView->currentRow(), 13)).toString() +
                " and AdhaarNo = '"+ adhaarEdit->text()+ "';";
    }

    QSqlQuery query(myDatabase);
    QString custID;

    if(!query.exec(queryString)){
        QMessageBox::information(this, tr("Query Erro - %1").arg(qApp->applicationName()),
                                 tr("You have encoutered connection problem. Please retry after some time."),
                                 QMessageBox::Ok | QMessageBox::Default);
        disconnectDatabase();
        rLoad(0);
        return;
    } else {


         * if no error is found and data is exist before
         * then show user that data is already exists you can not owerwrite the data

        if(query.size()>0){
            if(query.next()){
                custID = query.value(cust).toString();
            }
        }

        if(!custID.isEmpty()){
            QMessageBox::information(this, tr("Registratio failed! - %1").arg(qApp->applicationName()),
                                     tr("Duplication Restricted!\n\n The Adhaar no you entered is already assigned to the customer"
                                        "%1. Please select different adhaar no.").arg(custID),
                                     QMessageBox::Ok|QMessageBox::Default);
            disconnectDatabase();
            rLoad(0);
            return;
        }
    }

     * now all the errors are removed so
     * it is safe to update new adhaar card no to the
     * customer's account
     */

    QSqlQuery query(myDatabase);
    QString updateQuery = "START TRANSACTION;";
    if(this->type == "Producer"){
        updateQuery += "update Producer set "
                       "ProdFName = '" + firstNameEdit->text() + "'," +
                       "ProdMName = '" + middleNameEdit->text() + "'," +
                       "ProdLName = '" + lastNameEdit->text() + "', " +
                       "Pcontact  = '" + pContactEdit->text() + "', " +
                       "Scontact = '" + sContactEdit->text() + "', " +
                       "Street = '" + line1Edit->text() + "', " +
                "City = '" + line2Edit->text() + "', " +
                       "State = '" + stateBox->currentText() + "', " +
                       "Pincode = '" + pincodeEdit->text() + "', " +
                       "Email_ID = '" + emailEdit->text() + "', " +
                       "IsApp = '" + androidBox->currentText() + "'  "+
                " where binary ProdID = '" + model->data(model->index(listView->currentRow(), 13)).toString() + "'; ";
                           //  "update producerpae set AdhaarNo = '" + adhaarEdit->text() + "' "
               //  "where binary ProdID = '" + model->data(model->index(listView->currentRow(), 13)).toString() + "'; ";
    } else {
        updateQuery += "update Consumer set "
                       "ConsFName = '" + firstNameEdit->text() + "'," +
                       "ConsMName = '" + middleNameEdit->text() + "'," +
                       "ConsLName = '" + lastNameEdit->text() + "', " +
                       "Pcontact  = '" + pContactEdit->text() + "', " +
                       "Scontact = '" + sContactEdit->text() + "', " +
                       "Street = '" + line1Edit->text() + "', " +
                "City = '" + line2Edit->text() + "', " +
                       "State = '" + stateBox->currentText() + "', " +
                       "Pincode = '" + pincodeEdit->text() + "', " +
                       "Email_ID = '" + emailEdit->text() + "', " +
                       "IsApp = '" + androidBox->currentText() + "' "+
                " where binary ConsID = '" + model->data(model->index(listView->currentRow(), 13)).toString() + "'; ";
                      //  "update consumerpae set AdhaarNo = '" + adhaarEdit->text() + "' "
                      //"where binary ConsID = '" + model->data(model->index(listView->currentRow(), 13)).toString() + "'; ";
    }

    updateQuery += "COMMIT;";

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
        sendMail();
        QTimer::singleShot(2000, this, SLOT(showMessage()));
        OfflineCustEdit::editGeneral(model->data(model->index(listView->currentRow(), 13)).toString(), androidBox->currentText().at(0),
                                     firstNameEdit->text(), middleNameEdit->text(), lastNameEdit->text(), pContactEdit->text(), sContactEdit->text(),
                                     line1Edit->text(), line2Edit->text(), stateBox->currentText(), pincodeEdit->text(), emailEdit->text());
    }

}

void GeneralUpdate::showMessage()
{
    rLoad(0);
    QMessageBox::information(this, tr("Information Updated! - %1").arg(qApp->applicationName()),
                             tr("Your information is updated successfully."),
                             QMessageBox::Ok | QMessageBox::Default);
    modelQuery();
}

void GeneralUpdate::sendMail()
{
    QString subject = tr("Information Successfully Updated!");
    QString message = tr("Dear %1,"
                      "\n\nYour information is updated successfully  by secratery. Contact to your dairy for further details or query.\nThank You");

    //sending to mail to the customer
    Smtp *smtp = new Smtp(oDetail.getHostEmail(), oDetail.getHostEmailPass(), "smtp.gmail.com");
    smtp->sendMail(oDetail.getHostEmail(), emailEdit->text() , subject, message);
}

void GeneralUpdate::showPayment()
{
    paymentUpdate = new PaymentUpdate(this->type, model->data(model->index(listView->currentRow(), 13)).toString(), emailEdit->text());
    //connect payment to remake signal
    connect(paymentUpdate, SIGNAL(remakeMe()),
            this, SLOT(remakePayment()));
    paymentUpdate->exec();
}

void GeneralUpdate::remakePayment()
{
    delete paymentUpdate;
    paymentUpdate = new PaymentUpdate(this->type, model->data(model->index(listView->currentRow(), 13)).toString(), emailEdit->text());
    //connect payment to remake signal
    connect(paymentUpdate, SIGNAL(remakeMe()),
            this, SLOT(remakePayment()));
    paymentUpdate->exec();
}

bool GeneralUpdate::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == searchEdit && event->type() == QEvent::KeyPress){
        QKeyEvent *key = static_cast<QKeyEvent *> (event);
        if(key->key() == Qt::Key_Return || key->key() == Qt::Key_Enter){
            QString temp = searchEdit->text();

            int row = 0;
            while (row < model->rowCount()){
                if(temp == model->data(model->index(row, 13)).toString()){
                    listView->setCurrentRow(row);
                    listView->currentRowChanged(row);
                    return true;
                }
                row++;
            }

            row = 0;
            while (row <model->rowCount()){
                if(temp == model->data(model->index(row, 0)).toString()){
                    listView->setCurrentRow(row);
                    listView->currentRowChanged(row);
                    return true;
                }
                row++;
            }
            QMessageBox::information(this, tr("Not Found! - %1").arg(qApp->applicationName()),
                                     tr("%1 is not found in database...").arg(temp),
                                     QMessageBox::Ok|QMessageBox::Default);
        return true;
        }
    }
    return true;
}

bool GeneralUpdate::connectDatabase()
{
    if(!myDatabase.contains("editRemoteDBase")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "editRemoteDBase");
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

void GeneralUpdate::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("editRemoteDBase");
}

void GeneralUpdate::customerChanged(int row)
{
    if(!firstNameEdit->isEnabled()){
        firstNameEdit->setEnabled(true);
        middleNameEdit->setEnabled(true);
        lastNameEdit->setEnabled(true);
        pContactEdit->setEnabled(true);
        sContactEdit->setEnabled(true);
        line1Edit->setEnabled(true);
        line2Edit->setEnabled(true);
        stateBox->setEnabled(true);
        pincodeEdit->setEnabled(true);
        androidBox->setEnabled(true);
        emailEdit->setEnabled(true);
        showPaymentButton->setEnabled(true);
        updateButton->setEnabled(true);
    }

    //setting stylesheet for all line edit
    firstNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    middleNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    lastNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    adhaarEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    sContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    emailEdit->setStyleSheet(gDetail.getNormalStylesheet());
    line1Edit->setStyleSheet(gDetail.getNormalStylesheet());
    line2Edit->setStyleSheet(gDetail.getNormalStylesheet());
    pincodeEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //setting of stylesheet is completed

    mapper->toFirst();

    for(int jump = 0; jump < row; jump++){
        mapper->toNext();
    }

    stateBox->setCurrentText(model->data(model->index(row, 10)).toString());
    if(model->data(model->index(row, 12)).toString() == "Y"){
        androidBox->setCurrentIndex(0);
    } else
        androidBox->setCurrentIndex(1);
}

void GeneralUpdate::rLoad(int i)
{
    if(i == 1){
        searchEdit->setEnabled(false);
        listView->setEnabled(false);
        firstNameEdit->setEnabled(false);
        middleNameEdit->setEnabled(false);
        lastNameEdit->setEnabled(false);
        pContactEdit->setEnabled(false);
        sContactEdit->setEnabled(false);
        emailEdit->hide();
        line1Edit->setEnabled(false);
        line2Edit->setEnabled(false);
        stateBox->setEnabled(false);
        pincodeEdit->setEnabled(false);
        androidBox->setEnabled(false);
        showPaymentButton->setEnabled(false);
        updateButton->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 - 64;
        loadingLabel->setGeometry(x, y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        loading->stop();
        loadingLabel->hide();
        searchEdit->setEnabled(true);
        listView->setEnabled(true);
        firstNameEdit->setEnabled(true);
        middleNameEdit->setEnabled(true);
        lastNameEdit->setEnabled(true);
        pContactEdit->setEnabled(true);
        sContactEdit->setEnabled(true);
        emailEdit->show();
        line1Edit->setEnabled(true);
        line2Edit->setEnabled(true);
        stateBox->setEnabled(true);
        pincodeEdit->setEnabled(true);
        androidBox->setEnabled(true);
        showPaymentButton->setEnabled(true);
        updateButton->setEnabled(true);
    }
}

void GeneralUpdate::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}
