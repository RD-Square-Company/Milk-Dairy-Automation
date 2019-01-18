#include "newdepartment.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QDateTime>
#include <QTimer>

NewDepartment::NewDepartment(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    //loading
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //setting title label
    titleLabel->setText(tr("Add New Department: %1").arg(mDetail.getDID()));

    //setting connections to the buttons of the widget
    connect(editButton, SIGNAL(clicked(bool)),
            this, SLOT(editPressed()));
    connect(addButton, SIGNAL(clicked(bool)),
            this, SLOT(addPressed()));
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    connect(mangBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateSalary(int)));
    //all the connections are done...

    setWidgets();
}

void NewDepartment::setWidgets()
{
    //disabling salary edit
    salaryEdit->setEnabled(false);

    //setting stylesheet of all the line edit in widget
    depNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    salaryEdit->setStyleSheet(gDetail.getNormalStylesheet());

    //setting validator to the line edit
    QRegExp nameRegExp("[A-Za-z ]{20}");
    QRegExpValidator *nameValidator = new QRegExpValidator(nameRegExp, this);
    depNameEdit->setValidator(nameValidator);

    QRegExp salaryExp("[0-9]{1,7}[.]{1}[0-9]{2}");
    QRegExpValidator *salaryValidator = new QRegExpValidator(salaryExp, this);
    salaryEdit->setValidator(salaryValidator);

    if(!myDatabase.isOpen()){
        if(!connectDatabase()) {
            cancelPressed();
        }
    }

    QSqlQuery query(myDatabase);
    QSqlQuery query1(myDatabase);
    QString queryString = "select concat_ws(' ', EMPFName, EMPMName, EMPLName) as EN, EmpID, Salary "
                          "from Employee where LocalDID = '"+mDetail.getDID()+"';";
    QString removeString = "select T.MangID as MID from Department D, DepartmentMang T where "
                           " binary D.LocalDID = '"+mDetail.getDID()+"' and "
                           " binary D.DepID = T.DepID;";
    retry:
    if((!query.exec(queryString)) || (!query1.exec(removeString))) {
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."),
                              tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry;
        else
            cancelPressed();
    }

    if (query.size() > 0) {
        while (query.next()) {
            mangNames.append(query.value("EN").toString());
            salaryList.append(query.value("Salary").toString());
            mangIDs.append(query.value("EmpID").toString());
        }
    }

    QStringList tempList;
    if (query1.size() > 0) {
        while(query1.next()) {
            tempList.append(query1.value("MID").toString());
        }
    }

    //setting mangBox values
    for (int item=0; item < mangIDs.length(); item++) {
        if (!tempList.contains(mangIDs.at(item)))
            mangID.append(mangIDs.at(item));
        else {
            mangNames.removeAt(mangID.length());
            salaryList.removeAt(mangID.length());
        }
    }
    for (int item=0; item < mangID.length(); item++) {
        mangBox->addItem(mangNames.at(item));
    }
}

void NewDepartment::updateSalary(int ind)
{
    if (ind != 0) {
        salaryEdit->setText(tr("%1").arg(salaryList.at(ind-1)));
    } else {
        salaryEdit->setText("");
    }
}

bool NewDepartment::connectDatabase()
{
    if(!myDatabase.contains("newDept")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "newDept");
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

void NewDepartment::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("newDept");
}

void NewDepartment::addPressed()
{
    rLoad(1);
    QString error = "";
    if (descBox->toPlainText().isEmpty()) {
        error = tr("Please write description about department.");
    }
    if ((mangBox->currentIndex() != 0) && salaryEdit->text().isEmpty()) {
        error = tr("salary of head of department can not be empty.");
        salaryEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if (depNameEdit->text().isEmpty()) {
        error = tr("Please enter name of department.");
        depNameEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }

    if (!error.isEmpty()) {
        QMessageBox::information(this,
                                 tr("Error! : %1").arg(qApp->applicationName()),
                                 tr("%1").arg(error),
                                 QMessageBox::Ok | QMessageBox::Default);
        rLoad(0);
        return;
    }

    //getting highest value from depID
    QString id = "";
    if (!myDatabase.isOpen()){
        if(!connectDatabase())
            rLoad(0);
            return;
    }

    QSqlQuery query(myDatabase);
    retry:
    if (!query.exec("select max(depID) as max from Department where LocalDID = '"+mDetail.getDID() +"' group by LocalDID; ")){
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(query.lastError().nativeErrorCode()),
                              tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry;
        else
            rLoad(0);
            return;
    }

    if(query.size() > 0){
        if (query.next()) {
            id = query.value("max").toString();
        }
    } else {
        id = "A0";
    }

    QString  t2; QChar t1;
    t1 = id[0]; t2 = id[1];
    if (t2.toInt() < 9) {
        int k = t2.toInt();
        k++;;
        t2 = QString::number(k);
    } else {
        char p = t1.toLatin1();
        int k = p;
        k++;
        char c = k;
        t1 = c;
        t2 = "0";
    }
    id = t1 + t2;


    this->depID = id;
    QString queryString = "START TRANSACTION; ";
    QString squery = "";
    if (mangBox->currentIndex() != 0) {
        squery = "update Employee set Salary = "+salaryEdit->text()+" "
                 " where binary LocalDID = '"+mDetail.getDID()+"' and "
                 " binary EmpID = "+mangID.at(mangBox->currentIndex()-1)+"; ";
    }
    QString dquery = " insert into Department(DepID, DepName, Description, LocalDID) values ('" +
            id+"','"+ depNameEdit->text()+"','"+descBox->toPlainText()+"','"+mDetail.getDID()+"'); ";
    if(mangBox->currentIndex() != 0) {
        dquery += " INSERT INTO DepartmentMang(DepID, MangID) VALUES ('" +
                  id+"'," + mangID.at(mangBox->currentIndex()-1)+"); "
                  " INSERT INTO ManagerDepLog(MangID, DepID, FromDate, ToDate) VALUES ('"+
                  mangID.at(mangBox->currentIndex()-1)+"','"+id+"','"+QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")+
                  "',NULL);"
                  " update EmployeeDep set DepID = '"+id+"', Designation = 'HOD' "
                  " where EmpID = " + mangID.at(mangBox->currentIndex()-1) + "; ";
    }

    queryString += squery + dquery+" COMMIT;";
    retry1:
    if(!query.exec(queryString)) {
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(query.lastError().nativeErrorCode()),
                              tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry1;
        else
            rLoad(0);
            return;
    } else {
        QTimer::singleShot(2000, this, SLOT(showMessage()));
        if(mangBox->currentIndex() != 0) {
            OfflineDepRegistration::registerOffline(this->depID, depNameEdit->text(),mangID.at(mangBox->currentIndex()-1),
                                                    descBox->toPlainText());
            OfflineEmpEdit::editDepInfo(mangID.at(mangBox->currentIndex()-1),this->depID, "HOD", salaryEdit->text());
        } else {
            OfflineDepRegistration::registerOffline(this->depID, depNameEdit->text(),"", descBox->toPlainText());
        }
    }
}

void NewDepartment::editPressed()
{
    salaryEdit->setEnabled(true);
}

void NewDepartment::cancelPressed()
{
    disconnectDatabase();
    this->close();
}

void NewDepartment::showMessage()
{
    rLoad(0);
    QMessageBox::information(this,
                             tr("New Department Created! : %1").arg(qApp->applicationName()),
                             tr("<qt><font color=\"black\">Dear Secratery!,\nYou have created new department with name <font color=\"green\"><i>%1</i></font> and department id <font color=\"green\"><i>"
                                "%2</i></font>.\n\nThank You!!</font></qt>").arg(depNameEdit->text()).arg(depID),
                             QMessageBox::Ok | QMessageBox::Default);
    cancelPressed();
}

void NewDepartment::rLoad(int i)
{
    if (i == 1) {
        depNameEdit->setEnabled(false);
        mangBox->setEnabled(false);
        salaryEdit->setEnabled(false);
        editButton->setEnabled(false);
        descBox->setEnabled(false);
        cancelButton->setEnabled(false);
        addButton->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 -64;
        loadingLabel->setGeometry(x,y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        depNameEdit->setEnabled(true);
        mangBox->setEnabled(true);
        salaryEdit->setEnabled(true);
        editButton->setEnabled(true);
        descBox->setEnabled(true);
        cancelButton->setEnabled(true);
        addButton->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}

void NewDepartment::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}

NewDepartment::~NewDepartment(){
    disconnectDatabase();
}
