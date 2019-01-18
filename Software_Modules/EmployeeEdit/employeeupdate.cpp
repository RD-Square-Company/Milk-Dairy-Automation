#include "employeeupdate.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QSqlError>
#include "../CustomerRegistration/smtp.h"

EmployeeUpdate::EmployeeUpdate(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    adhaarEdit->setEnabled(false);

    //setting set variable for department box
    setDept = 0;

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
    connect(listWidget, SIGNAL(currentRowChanged(int)),
            this, SLOT(employeeChanged(int)));
    //connections are set

    //hide gender label and radio buttons
    genderLabel->hide();
    maleButton->hide();
    femaleButton->hide();

    //setting event filter to searchEdit
    searchEdit->installEventFilter(this);

    setWidgets();
}

void EmployeeUpdate::setWidgets()
{
    //setting stylesheet for general information line edit
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
    //setting of stylesheet is completed for general information

    //setting stylesheet for office information line edit
    //designationEdit->setStyleSheet(gDetail.getNormalStylesheet());
    salaryEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //setting of stylesheet for office information line edit is completed

    //setting validator for line edit of general information
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

    QRegExp streetExp("[A-Za-z-.*\\s0-9]{40}");
    QRegExpValidator *streetValidator = new QRegExpValidator(streetExp, this);
    line1Edit->setValidator(streetValidator);

    QRegExp cityExp("[A-Za-z\\s]{20}");
    QRegExpValidator *cityValidator = new QRegExpValidator(cityExp, this);
    line2Edit->setValidator(cityValidator);
    //setting of validator of general information is compeleted

    //setting of  validator for office information
    //QRegExp designationExp("[A-Za-z-,\\s]{50}");
    //QRegExpValidator *designationValidator = new QRegExpValidator(designationExp, this);
    //designationEdit->setValidator(designationValidator);

    QRegExp salaryExp("[0-9]{1,7}[.]{1}[0-9]{2}");
    QRegExpValidator *salaryValidator = new QRegExpValidator(salaryExp, this);
    salaryEdit->setValidator(salaryValidator);

    /*********
     *
     * set minimum date to establish date of dairy
     *
     */
    dojEdit->setDate(QDate::currentDate());
    dojEdit->setMaximumDate(QDate::currentDate());

    //setting mapper for widgets
    mapper->setModel(model);
    mapper->addMapping(firstNameEdit, 1);
    mapper->addMapping(middleNameEdit, 2);
    mapper->addMapping(lastNameEdit, 3);
    mapper->addMapping(adhaarEdit, 4);
    mapper->addMapping(pContactEdit, 5);
    mapper->addMapping(sContactEdit, 6);
    mapper->addMapping(emailEdit, 7);
    mapper->addMapping(dobEdit, 8);
    mapper->addMapping(dojEdit, 9);
    mapper->addMapping(line1Edit, 10);
    mapper->addMapping(line2Edit , 11);
    mapper->addMapping(stateBox, 12);
    mapper->addMapping(pincodeEdit, 13);
    mapper->addMapping(checkBox, 14);
    mapper->addMapping(hQBox, 15);
    mapper->addMapping(salaryEdit, 16);
    //below two lines are removed as department may more than one
    //mapper->addMapping(designationEdit, 17);
    //mapper->addMapping(departmentBox, 18);

    //setting completer

    completer->setModel(stringModel);
    completer->setMaxVisibleItems(10);
    completer->setWrapAround(true);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    searchEdit->setCompleter(completer);

    //disabling all the widget at initially
    firstNameEdit->setEnabled(false);
    middleNameEdit->setEnabled(false);
    lastNameEdit->setEnabled(false);
    adhaarEdit->setEnabled(false);
    pContactEdit->setEnabled(false);
    sContactEdit->setEnabled(false);
    emailEdit->setEnabled(false);
    showPaymentButton->setEnabled(false);
    updateButton->setEnabled(false);
    line1Edit->setEnabled(false);
    line2Edit->setEnabled(false);
    dobEdit->setEnabled(false);
    dojEdit->setEnabled(false);
    stateBox->setEnabled(false);
    pincodeEdit->setEnabled(false);
    departLabel->setEnabled(false);//changed on the place of department box
    desgLabel->setEnabled(false); //changed on the place of designation edit
    salaryEdit->setEnabled(false);
    hQBox->setEnabled(false);
    checkBox->setEnabled(false);

    //querying by model
    modelQuery();

    QStringList stringList;

    for (int row = 0; row < model->rowCount(); row++){
        stringList << model->data(model->index(row, 0)).toString();
    }

    stringModel->setStringList(stringList);

    //below connection would be not used in future
    //setting temporary connection to database to set departments into department box
    //setTempConnection();
}

void EmployeeUpdate::modelQuery()
{
    for (int row=0; row< model->rowCount(); row++){
        model->removeRow(row);
    }

    //setting list view
    for(int row =0; row<listWidget->count(); row++){
        listWidget->model()->removeRows(0, model->rowCount());
    }

    QString queryString;

    queryString = "select concat_ws(' ', Employee.EMPFName, Employee.EMPMName, Employee.EMPLName), Employee.EMPFName, Employee.EMPMName, Employee.EMPLName, EmployeePAE.AdhaarNo, "
                  "Employee.Pcontact, Employee.Scontact, Employee.Email_ID, Employee.EmpDOB, Employee.DOJoin, Employee.Street, Employee.City, Employee.State, Employee.Pincode, Employee.IsActive, Employee.Hqualification, "
                  "Employee.Salary, Employee.EmpID "
                  "from Employee, EmployeePAE "
                  "where binary Employee.EmpID = EmployeePAE.EmpID;";

    //connect database if not connected

    if(!myDatabase.isOpen()) {
        if(!connectDatabase())
            return;
    }

    model->setQuery(queryString, myDatabase);

    for(int row = 0; row <model->rowCount(); row++){
        listWidget->addItem(model->data(model->index(row, 0)).toString());
    }

    listWidget->setCurrentRow(0);
    listWidget->currentRowChanged(0);

    //setting value to the department and designation label
    setDepartment();
}

void EmployeeUpdate::editSetting(int i)
{
    if( i == 1) {
        firstNameEdit->setEnabled(true);
        middleNameEdit->setEnabled(true);
        lastNameEdit->setEnabled(true);
        dobEdit->setEnabled(true);
        pContactEdit->setEnabled(true);
        sContactEdit->setEnabled(true);
        emailEdit->setEnabled(true);
        line1Edit->setEnabled(true);
        line2Edit->setEnabled(true);
        pincodeEdit->setEnabled(true);
        stateBox->setEnabled(true);
        dojEdit->setEnabled(true);
        salaryEdit->setEnabled(true);
        hQBox->setEnabled(true);
        checkBox->setEnabled(true);
        showPaymentButton->setEnabled(true);
        updateButton->setEnabled(true);
        searchEdit->setEnabled(true);
    } else {
        firstNameEdit->setEnabled(false);
        middleNameEdit->setEnabled(false);
        lastNameEdit->setEnabled(false);
        dobEdit->setEnabled(false);
        pContactEdit->setEnabled(false);
        sContactEdit->setEnabled(false);
        emailEdit->setEnabled(false);
        line1Edit->setEnabled(false);
        line2Edit->setEnabled(false);
        pincodeEdit->setEnabled(false);
        stateBox->setEnabled(false);
        dojEdit->setEnabled(false);
        salaryEdit->setEnabled(false);
        hQBox->setEnabled(false);
        checkBox->setEnabled(false);
        showPaymentButton->setEnabled(false);
        updateButton->setEnabled(false);
        //searchEdit->setEnabled(false);
    }
}

void EmployeeUpdate::setDepartment()
{
  QString queryString = "select Department.DepName as dept, EmployeeDep.Designation as desg "
      "from Department, EmployeeDep "
      "where Department.DepID = EmployeeDep.DepID "
      "and EmployeeDep.EmpID = '" + model->data(model->index(listWidget->currentRow(), 17)).toString() + "';";

  QSqlQuery query(myDatabase);

  //checking database connectivity and get it connected!
  if(!myDatabase.isOpen()){
      if(!connectDatabase())
        return;
    }

  QStringList depList, desgList;
  QString dep, desg;
  if(query.exec(queryString)){
      if(query.size() > 0){
          int start = 0;
          while(query.next()){
              depList.insert(start, "");
              desgList.insert(start, "");
              depList[start] = query.value("dept").toString();
              desgList[start] = query.value("desg").toString();
              start++;
            }
        }
    }


  //changing list to comma separated string
  for(int start=0; start<depList.count(); start++){
      if(start==0){
          dep = depList.at(0);
          desg = desgList.at(0);
        } else {
          dep += "," + depList.at(start);
          desg += "," + desgList.at(start);
        }
    }

  //set the final string to the department and designation label
  departLabel->setText(tr("%1").arg(dep));
  desgLabel->setText(tr("%1").arg(desg));

  if(listWidget->count() == 0) {
      editSetting(0);
  } else {
      editSetting(1);
  }
}

bool EmployeeUpdate::connectDatabase()
{
    if(!myDatabase.contains("editRemoteDBase")) {
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "editRemoteDBase");
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
            rLoad(0);
            return false;
    }
 }
    return true;
}

void EmployeeUpdate::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("editRemoteDBase");
}

bool EmployeeUpdate::checkInfo()
{
    QString error;
    if(pincodeEdit->text().isEmpty() || pincodeEdit->text().count() < 6) {
        error = tr("Pincode must be 6 digit number");
        pincodeEdit->setStyleSheet(gDetail.getNormalStylesheet());
    }
    if(stateBox->currentIndex() == 0) {
        error = tr("please select any state");
    }
    if(line1Edit->text().isEmpty() || line2Edit->text().isEmpty()) {
        error = tr("Please enter your address to address line");
        line1Edit->setStyleSheet(gDetail.getNormalStylesheet());
        line2Edit->setStyleSheet(gDetail.getNormalStylesheet());
    }

    if(! (emailEdit->text().isEmpty())) {
        if(!(emailEdit->text().contains('@')) || !(emailEdit->text().contains(".com"))){
            error = tr("Please enter valid email ID");
            emailEdit->setStyleSheet(gDetail.getNormalStylesheet());
        }
        if(emailEdit->text().count('@') > 1 || emailEdit->text().count('.') > 1) {
            error = tr("Please enter valid email ID");
            emailEdit->setStyleSheet(gDetail.getNormalStylesheet());
    }
    }
    if(!sContactEdit->text().isEmpty()){
        if (sContactEdit->text().count() != 10 ){
            error = tr("Enter valid mob no & not use 0 at starting");
            sContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
        }
    }
    if((pContactEdit->text().count() != 10) || pContactEdit->text().isEmpty()){
        error = tr("Please enter any valid mob no");
        pContactEdit->setStyleSheet(gDetail.getNormalStylesheet());
    }
    if(adhaarEdit->text().isEmpty() || adhaarEdit->text().count() != 4) {
        error = tr("Please enter valid adhar card no");
        adhaarEdit->setStyleSheet(gDetail.getNormalStylesheet());
    }
    if(firstNameEdit->text().isEmpty()) {
        error = tr("First name can not be empty");
        firstNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    }

    if(hQBox->currentIndex() == 0){
        error = tr("You must have to select highest qualification of employee");
    }
    if(salaryEdit->text().isEmpty()) {
        error = tr("You must have to give salary to your Employees");
        salaryEdit->setStyleSheet(gDetail.getNormalStylesheet());
    }

    if(!error.isEmpty()){
        QMessageBox::information(this,
                                 tr("Updation Error! - %1").arg(qApp->applicationName()),
                                 tr("%1").arg(error),
                                 QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    return true;
}
/*
void EmployeeUpdate::setTempConnection()
{
    QStringList deptValues;
    QSqlDatabase localDatabase = QSqlDatabase::addDatabase("QMYSQL", "localDBase");
    localDatabase.setHostName("localhost");
    localDatabase.setDatabaseName(uc.localDB);
    localDatabase.setUserName(uc.localDBUName);
    localDatabase.setPassword(uc.localDBPass);
    localDatabase.setPort(3306);

    retry:
    if(!localDatabase.open()){
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(localDatabase.lastError().nativeErrorCode()),
                              tr("&Exit"), tr("&Retry"), QString(), 0, 1);
        if (result == 1)
            goto retry;
        else{
            localDatabase.removeDatabase("localDBase");
            getDeptValues(deptValues);
        }
    }

    QSqlQuery query(localDatabase);
    QString value;
    retry1:
    if(!query.exec("select DepName, DepID from Department;")){
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(query.lastError().nativeErrorCode()),
                              tr("&Exit"), tr("&Retry"), QString(), 0, 1);
        if (result == 1)
            goto retry1;
        else{
            localDatabase.removeDatabase("localDBase");
            getDeptValues(deptValues);
        }
    }

    deptValues.append("No Any Department  (A0)");
    if(query.size() > 0){
        while(query.next()){
            value = query.value("DepName").toString();
            value += "  (" + query.value("DepID").toString() + ")";
            deptValues.append(value);
        }
    }
    getDeptValues(deptValues);
    localDatabase = QSqlDatabase();
    localDatabase.removeDatabase("localDBase");
}

void EmployeeUpdate::getDeptValues(QStringList depNames)
{
    if(depNames.count() > 1){
        for(int item= 0; item<departmentBox->count(); item++) {
            departmentBox->removeItem(0); //remove first item every time as next item will be first after deleting first item
        }

        for(int item = 0; item < depNames.count(); item++){
            departmentBox->addItem(depNames.at(item));
        }

    } else if (depNames.count() == 1){
        for(int item= 0; item<departmentBox->count(); item++) {
            departmentBox->removeItem(0); //remove first item every time as next item will be first after deleting first item
        }

        departmentBox->addItem(depNames.at(0));
    }
}
*/
void EmployeeUpdate::rLoad(int i)
{
    if(i==1){
        searchEdit->setEnabled(false);
        listWidget->setEnabled(false);
        generalBox->setEnabled(false);
        officeBox->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 - 64;
        loadingLabel->setGeometry(x, y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        loading->stop();
        loadingLabel->hide();
        searchEdit->setEnabled(true);
        listWidget->setEnabled(true);
        generalBox->setEnabled(true);
        officeBox->setEnabled(true);
    }
}

void EmployeeUpdate::updatePressed()
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
        if (sContactEdit->text().count() != 10 ){
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
    if(hQBox->currentIndex() == 0){
        error = tr("You must have to select highest qualification of employee");
    }
    if(salaryEdit->text().isEmpty()) {
        error = tr("You must have to give salary to your Employees");
        salaryEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }

    if(error.isEmpty()){
        updateValue();
    } else {
        QMessageBox::information(this, tr("Enter Correct Value - %1").arg(qApp->applicationName()),
                                 tr("%1").arg(error),
                                 QMessageBox::Ok|QMessageBox::Default);
    }
}

void EmployeeUpdate::updateValue()
{
    rLoad(1);
    if(!myDatabase.isOpen()){
        if(!connectDatabase()){
            rLoad(0);
            return;
        }
    }
    /*
     * cancelling adhaar card updation for undefined time
     * so don't consider this code as working but it
     * is important for future use
     * this code is not working as expected
     * Thank you
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
    QString check = "0";
    QString updateQuery = ""; //"START TRANSACTION;";
    if(checkBox->isChecked()){
        check = "1";
    }
    QString eID = model->data(model->index(listWidget->currentRow(), 17)).toString();
    updateQuery += "update Employee set "
                   "EMPFName = '" + firstNameEdit->text() + "'," +
                   "EMPMName = '" + middleNameEdit->text() + "'," +
                   "EMPLName = '" + lastNameEdit->text() + "', " +
            "DOJoin = '" + dojEdit->date().toString("yyyy-MM-dd") + "', " +
            "EmpDOB = '" + dobEdit->date().toString("yyyy-MM-dd") + "', " +
            "Pcontact  = '" + pContactEdit->text() + "', " +
             "Scontact = '" + sContactEdit->text() + "', " +
             "Street = '" + line1Edit->text() + "', " +
            "State = '" + stateBox->currentText() + "', " +
            "City = '" + line2Edit->text() + "', " +
            "Hqualification = '" + hQBox->currentText() + "', " +
            "IsActive = '" + check + "', " +
            "Pincode = '" + pincodeEdit->text() + "', " +
           "Email_ID = '" + emailEdit->text() + "', " +
            "Salary = " + salaryEdit->text() +
            "  where binary EmpID = " + model->data(model->index(listWidget->currentRow(), 17)).toString() + "; ";

   // updateQuery += "COMMIT;";

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
        OfflineEmpEdit::editGeneral(eID, check, firstNameEdit->text(), middleNameEdit->text(), lastNameEdit->text(),
                                    pContactEdit->text(), sContactEdit->text(), line1Edit->text(), line2Edit->text(),
                                    stateBox->currentText(), pincodeEdit->text(), emailEdit->text(),
                                    dobEdit->date().toString("yyyy-MM-dd"),hQBox->currentText(), salaryEdit->text());
    }
}

void EmployeeUpdate::sendMail()
{
    QString subject = tr("Information Successfully Updated!");
    QString message = tr("Dear %1,"
                      "\n\nYour information is updated successfully  by secratery. Contact to your dairy for further details or query.\nThank You");

    //sending to mail to the customer
    Smtp *smtp = new Smtp(oDetail.getHostEmail(), oDetail.getHostEmailPass(), "smtp.gmail.com");
    smtp->sendMail(oDetail.getHostEmail(), emailEdit->text() , subject, message);
}

void EmployeeUpdate::showMessage()
{
    rLoad(0);
    QMessageBox::information(this, tr("Information Updated! - %1").arg(qApp->applicationName()),
                             tr("Your information is updated successfully."),
                             QMessageBox::Ok | QMessageBox::Default);
    modelQuery();
}

void EmployeeUpdate::showPayment()
{
    paymentUpdate = new EPaymentUpdate(model->data(model->index(listWidget->currentRow(), 17)).toString(), emailEdit->text());

    //connect payment to remake signal
    connect(paymentUpdate, SIGNAL(remakeMe()),
            this, SLOT(remakePayment()));
    paymentUpdate->exec();
}

void EmployeeUpdate::employeeChanged(int row)
{
    if(!firstNameEdit->isEnabled()){
        firstNameEdit->setEnabled(true);
        middleNameEdit->setEnabled(true);
        lastNameEdit->setEnabled(true);
        pContactEdit->setEnabled(true);
        sContactEdit->setEnabled(true);
        dobEdit->setEnabled(true);
        emailEdit->setEnabled(true);
        line1Edit->setEnabled(true);
        line2Edit->setEnabled(true);
        stateBox->setEnabled(true);
        pincodeEdit->setEnabled(true);
        departLabel->setEnabled(true);
        desgLabel->setEnabled(true);
        hQBox->setEnabled(true);
        salaryEdit->setEnabled(true);
        showPaymentButton->setEnabled(true);
        updateButton->setEnabled(true);
        checkBox->setEnabled(true);
    }

    //setting stylesheet for general information line edit
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
    //setting of stylesheet is completed for general information

    //setting stylesheet for office information line edit
    //designationEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //salaryEdit->setStyleSheet(gDetail.getNormalStylesheet());

    //stylesheet work is done

    mapper->toFirst();

    for(int jump=0; jump<row; jump++){
        mapper->toNext();
    }

    stateBox->setCurrentText(model->data(model->index(row, 12)).toString());
    hQBox->setCurrentText(model->data(model->index(row, 15)).toString());
    //departmentBox->setCurrentText(model->data(model->index(row, 18)).toString());

    if(model->data(model->index(row, 14)).toString() == "1"){
        checkBox->setChecked(true);
    } else {
        checkBox->setChecked(false);
    }
}

bool EmployeeUpdate::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == searchEdit && event->type() == QEvent::KeyPress){
        QKeyEvent *key = static_cast<QKeyEvent *> (event);
        if(key->key() == Qt::Key_Return || key->key() == Qt::Key_Enter){
            QString temp = searchEdit->text();

            int row =0;
            while (row < model->rowCount()){
                if(model->data(model->index(row, 0)).toString().contains(temp)){
                    listWidget->setCurrentRow(row);
                    listWidget->currentRowChanged(row);
                    return true;
                }
                row ++;
            }
            QMessageBox::information(this,
                                     tr("Not Found - %1").arg(qApp->applicationName()),
                                     tr("%1 is not found in database...").arg(temp),
                                     QMessageBox::Ok | QMessageBox::Default);
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);;
}

void EmployeeUpdate::remakePayment()
{
    delete paymentUpdate;
    paymentUpdate = new EPaymentUpdate(model->data(model->index(listWidget->currentRow(), 17)).toString(), emailEdit->text());
    //connect payment to remake signal
    connect(paymentUpdate, SIGNAL(remakeMe()),
            this, SLOT(remakePayment()));
    paymentUpdate->exec();
}

void EmployeeUpdate::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}
