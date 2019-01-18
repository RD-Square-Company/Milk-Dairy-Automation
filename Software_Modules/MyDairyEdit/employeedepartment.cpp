#include "employeedepartment.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>
#include <QEvent>
#include <QTimer>
#include <QKeyEvent>

EmployeeDepartment::EmployeeDepartment(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    //loading
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //installing event filter on search edit
    searchEdit->installEventFilter(this);

    //hidding option widgets as this feature is temporarily unavailable
    optionLabel->hide();
    rsButton->hide();
    raButton->hide();
    asButton->hide();

    //setting connections of button in widget
    connect(proceedButton, SIGNAL(clicked(bool)),
            this, SLOT(proceedPressed()));
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    //all the connections are done

    setWidgets();
}

void EmployeeDepartment::setWidgets()
{
    //setting stylesheet to line edit of widget
    searchEdit->setStyleSheet(gDetail.getNormalStylesheet());
    desgEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //setting stylesheet is done

    //temporarily hiding widgets
    proceedButton->setEnabled(false);
    empNameLabel->hide();
    empAdhaarLabel->hide();
    cdDepartmentLabel->hide();
    empDesgLabel->hide();
    nameLabel->hide();
    adhaarLabel->hide();
    depLabel->hide();
    desgEdit->hide();
    sDepLabel->hide();
    departmentBox->hide();

    //settting validator to line edit of widget
    QRegExp searchExp("[0-9]{0,11}");
    QRegExpValidator *searchValidator = new QRegExpValidator(searchExp, this);
    searchEdit->setValidator(searchValidator);
    //all validator(s) are set now

    if(!myDatabase.isOpen()) {
        if(!connectDatabase()) {
            cancelPressed();
        }
    }

    QString depString = "select DepID, DepName from Department where binary Department.LocalDID = '"+mDetail.getDID()+"';";
    QSqlQuery query(myDatabase);
    retry:
    if(!query.exec(depString)){
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

    if (query.size()>0) {
        while(query.next()) {
            didList.append(query.value("DepID").toString());
            dNameList.append(query.value("DepName").toString());
        }
    }

    //setting department to departmentBox
    for (int item=0; item<didList.length(); item++) {
        departmentBox->addItem(dNameList.at(item) + " ("+didList.at(item)+")");
    }
}

void EmployeeDepartment::cancelPressed()
{
    disconnectDatabase();
    this->close();
}

void EmployeeDepartment::proceedPressed()
{
    rLoad(1);
    QString error;

    if(desgEdit->text().isEmpty()){
        error = tr("<html><p>Enter Designation!</p><p>Please enter designation of employee.</p></html>");
        desgEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(departmentBox->currentText() == depLabel->text()) {
        error = tr("<html><p>Same Department!</p><p>There is nothing to change!</p></html>");
    }
    if (departmentBox->currentIndex() == 0) {
        error = tr("<html><p>Select Department!</p>Please select any department.</p></html>");
    }

    if (!error.isEmpty()) {
        rLoad(0);
        QMessageBox::information(this,
                                 tr("Error Encountered! - %1").arg(qApp->applicationName()),
                                 tr("%1").arg(error),
                                 QMessageBox::Ok | QMessageBox::Default);
        return ;
    }

    int result;
    rLoad(0);
    result = QMessageBox::question(this,
                                   tr("Change Department? - %1").arg(qApp->applicationName()),
                                   tr("This will remove employee from previous department and assign him/her to new department.\n"
                                      "Do you want to change the department of selected employee?"),
                                   QString(tr("Yes, I want to change Department!")), QString(tr("No, I don't want to change Department")), QString(),
                                   0,1);
    if (result==1)
        return;
    rLoad(1);

    if(!myDatabase.isOpen()) {
        if(!connectDatabase()) {
            rLoad(0);
            return;
        }
    }

    QString q1 = " select D.DepName as Name from DepartmentMang DM, Department D where "
                 " D.DepID = DM.DepID and MangID = "+this->eID+";";
    QSqlQuery qry(myDatabase);
    rty:
    rLoad(0);
    if (!qry.exec(q1)){
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."),
                              tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
        if (result == 1)
            goto rty;
        else
            return;
    }
    rLoad(1);
    if(qry.size()>0) {
        QString tempName;
        if(qry.next())
            tempName = qry.value("Name").toString();
        rLoad(0);
        QMessageBox::information(this,
                                 tr("Department Error - %1").arg(qApp->applicationName()),
                                 tr("<html><p>Department Can't be changed!</p><p>%1 is currently head of %2.</p><p>First change HOD of %2 and then "
                                    "try again!</p><p>Thank You!</p></html>").arg(nameLabel->text()).arg(depLabel->text()),
                                 QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QString queryString = " update EmployeeDep "
                          " set DepID = '"+didList.at(departmentBox->currentIndex()-1)+"',"
                          " Designation = '"+desgEdit->text()+"' "
                          " where EmpID = "+this->eID+" and "
                          " DepID = '" + tmpID + "';";

    QSqlQuery query(myDatabase);
    retry:
    rLoad(0);
    if(!query.exec(queryString)) {
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."),
                              tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
        if (result == 1)
            goto retry;
        else
            return;
    }
    rLoad(1);
    QTimer::singleShot(2000, this, SLOT(showMessage()));
    OfflineEmpEdit::editDepID(this->eID,didList.at(departmentBox->currentIndex()-1) );
    OfflineEmpEdit::editDesignation(this->eID, desgEdit->text());
}

void EmployeeDepartment::showMessage()
{
    rLoad(0);
    QMessageBox::information(this,
                             tr("Update Successfull! - %1").arg(qApp->applicationName()),
                             tr("<html><p>Update Successfull!</p><p>Department of employee with id %1 "
                                "has been changed to %2.</p><p>Thank You!</p>").arg(searchEdit->text()).arg(depLabel->text()),
                             QMessageBox::Ok | QMessageBox::Default);

    cancelPressed();
}

bool EmployeeDepartment::connectDatabase()
{
    if(!myDatabase.contains("empDep")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "empDep");
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
            //rLoad(0);
            return false;
    }
  }
    return true;
}

void EmployeeDepartment::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("empDep");
}

bool EmployeeDepartment::eventFilter(QObject *object, QEvent *event)
{
    if(object == searchEdit && event->type() == QEvent::KeyPress){
        QKeyEvent *key = static_cast<QKeyEvent *> (event);
        if(key->key() == Qt::Key_Return || key->key() == Qt::Key_Enter){
            if(!myDatabase.isOpen()) {
                if(!connectDatabase()) {
                    proceedButton->setEnabled(false);
                    empNameLabel->hide();
                    empAdhaarLabel->hide();
                    cdDepartmentLabel->hide();
                    nameLabel->hide();
                    adhaarLabel->hide();
                    depLabel->hide();
                    empDesgLabel->hide();
                    desgEdit->hide();
                    sDepLabel->hide();
                    departmentBox->hide();
                    return true;
                }
            }

            if (searchEdit->text().isEmpty())
                return true;

            QString queryString = " select concat_ws(' ', E.EMPFName, E.EMPMName, E.EMPLName) as EN, "
                                  " EP.AdhaarNo as A, D.DepID as DID, D.DepName as DN, ED.Designation as EDD "
                                  " from Employee E, Department D, EmployeeDep ED, EmployeePAE EP "
                                  " where E.EmpID = ED.EmpID "
                                  " and EP.EmpID = E.EmpID "
                                  " and D.DepID = ED.DepID "
                                  " and binary E.LocalDID = '"+mDetail.getDID()+"' "
                                  " and binary E.EmpID = "+searchEdit->text()+";";
            QSqlQuery query(myDatabase);
            retry:
            if (!query.exec(queryString)) {
                int result = QMessageBox::critical(this,
                                      tr("Connection Error! : %1").arg(qApp->applicationName()),
                                      tr("\tDatabase Connection Problem!\n"
                                         "Please make sure, you are connected to the internet service. "
                                         "Retry after connecting to the internet."),
                                      tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
                if(result==1)
                    goto retry;
                else {
                    proceedButton->setEnabled(false);
                    empNameLabel->hide();
                    empAdhaarLabel->hide();
                    cdDepartmentLabel->hide();
                    nameLabel->hide();
                    adhaarLabel->hide();
                    depLabel->hide();
                    empDesgLabel->hide();
                    desgEdit->hide();
                    sDepLabel->hide();
                    departmentBox->hide();
                    return true;
                }
            }

            QString en, ea, di, dn, ed;
            if (query.size() > 0) {
                if(query.next()) {
                    en = query.value("EN").toString();
                    ea  = query.value("A").toString();
                    di = query.value("DID").toString();
                    dn = query.value("DN").toString();
                    ed = query.value("EDD").toString();
                }
            } else {
                QMessageBox::information(this,
                                      tr("Not Found! - %1").arg(qApp->applicationName()),
                                      tr("<html><qt>No employee found with id no <b><i>%1</i></b><hr>"
                                         "Please try with valid id no.</hr>Thank You!</qt></html>").arg(searchEdit->text()),
                                         QMessageBox::Ok | QMessageBox::Default);
                nameLabel->setText("");
                adhaarLabel->setText("");
                depLabel->setText("");
                desgEdit->setText("");
                proceedButton->setEnabled(false);
                empNameLabel->hide();
                empAdhaarLabel->hide();
                cdDepartmentLabel->hide();
                nameLabel->hide();
                adhaarLabel->hide();
                depLabel->hide();
                empDesgLabel->hide();
                desgEdit->hide();
                sDepLabel->hide();
                departmentBox->hide();
                return true;
            }

            //set all the values to the widgets
            this->eID = searchEdit->text();
            nameLabel->setText(en);
            adhaarLabel->setText(ea);
            depLabel->setText(dn+" ("+di+")");
            desgEdit->setText(ed);
            tmpID = di;

            proceedButton->setEnabled(true);
            empNameLabel->show();
            empAdhaarLabel->show();
            cdDepartmentLabel->show();
            nameLabel->show();
            adhaarLabel->show();
            depLabel->show();
            empDesgLabel->show();
            desgEdit->show();
            sDepLabel->show();
            departmentBox->show();
            return true;
        }
    }

    return QWidget::eventFilter(object, event);
}

EmployeeDepartment::~EmployeeDepartment()
{
    disconnectDatabase();
}

void EmployeeDepartment::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}

void EmployeeDepartment::rLoad(int i)
{
    if(i == 1){
        searchEdit->setEnabled(false);
        departmentBox->setEnabled(false);
        desgEdit->setEnabled(false);
        cancelButton->setEnabled(false);
        proceedButton->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 -64;
        loadingLabel->setGeometry(x,y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        searchEdit->setEnabled(true);
        departmentBox->setEnabled(true);
        desgEdit->setEnabled(true);
        cancelButton->setEnabled(true);
        proceedButton->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}
