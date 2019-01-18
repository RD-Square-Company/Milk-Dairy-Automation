#include "newhead.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>
#include <QDate>
#include <QTimer>

NewHead::NewHead(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    //disabling salary edit
    salaryEdit->setEnabled(false);

    //loading
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //setting up connections of the buttons of widget
    connect(editButton, SIGNAL(clicked(bool)),
            this, SLOT(editPressed()));
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    connect(proceedButton, SIGNAL(clicked(bool)),
            this, SLOT(proceedPressed()));
    connect(headBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(salaryChanged(int)));
    connect(depBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(depChanged(int)));
    //all connections are set

    setWidgets();
}

void NewHead::setWidgets()
{
    //setting stylesheet to line edit of widget
    salaryEdit->setStyleSheet(gDetail.getNormalStylesheet());

    //setting validator to salary edit
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
    QSqlQuery query2(myDatabase);

    QString queryString = "select concat_ws(' ', EMPFName, EMPMName, EMPLName) as EN, EmpID, Salary, Hqualification "
                          "from Employee where LocalDID = '"+mDetail.getDID()+"';";
    QString removeString = "select T.MangID as MID from Department D, DepartmentMang T where "
                           " binary D.LocalDID = '"+mDetail.getDID()+"' and "
                           " binary D.DepID = T.DepID;";
    QString depString = "select DepID, DepName from Department where binary Department.LocalDID = '"+mDetail.getDID()+"';";
    retry:
    if(((!query.exec(queryString)) || (!query1.exec(removeString))) || (!query2.exec(depString))) {
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
            qList.append(query.value("Hqualification").toString());
        }
    }

    QStringList tempList;
    if (query1.size() > 0) {
        while(query1.next()) {
            tempList.append(query1.value("MID").toString());
        }
    }

    if(query2.size() > 0) {
        while (query2.next()) {
            didList.append(query2.value("DepID").toString());
            dnameList.append(query2.value("DepName").toString());
        }
    }

    //setting mangBox values
    for (int item=0; item < mangIDs.length(); item++) {
        if (!tempList.contains(mangIDs.at(item)))
            mangID.append(mangIDs.at(item));
        else {
            mangNames.removeAt(mangID.length());
            salaryList.removeAt(mangID.length());
            qList.removeAt(mangID.length());
        }
    }

    //for (int item=0; item < mangID.length(); item++) {
     //   headBox->addItem(mangNames.at(item));
    //}

    //setting depBox values
    for(int item=0;item<didList.length(); item++){
        depBox->addItem("("+didList.at(item)+") "+dnameList.at(item));
    }
}

void NewHead::depChanged(int ind)
{
    if (ind != 0) {
        QString queryString = "select concat_ws(' ', E.EMPFName, E.EMPMName, E.EMPLName) as EN, EmpID "
                              " from Employee E, DepartmentMang DM "
                              " where binary DM.DepID = '"+didList.at(depBox->currentIndex()-1) + "' "
                              " and binary E.LocalDID = '"+mDetail.getDID()+"' "
                              " and E.EmpID = DM.MangID;";
        if (!myDatabase.isOpen()) {
            if (!connectDatabase()){
                return;
            }
        }

        QSqlQuery query(myDatabase);
        retry:
        if (!query.exec(queryString)){
            int result = QMessageBox::critical(this,
                                  tr("Connection Error! : %1").arg(qApp->applicationName()),
                                  tr("\tDatabase Connection Problem!\n"
                                     "Please make sure, you are connected to the internet service. "
                                     "Retry after connecting to the internet."),
                                  tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
            if(result == 1)
                goto retry;
            else
                return;
        }

        QString tempName=tr("");
        if(query.size() > 0) {
            if(query.next()) {
                tempName = query.value("EN").toString();
                headID = query.value("EmpID").toString();
            }
        }

        QString anotherQuery = " select EmpID from EmployeeDep where DepID = '"+didList.at(depBox->currentIndex()-1) + "';";
        retry1:
        if(!query.exec(anotherQuery)){
            if (!query.exec(queryString)){
                int result = QMessageBox::critical(this,
                                      tr("Connection Error! : %1").arg(qApp->applicationName()),
                                      tr("\tDatabase Connection Problem!\n"
                                         "Please make sure, you are connected to the internet service. "
                                         "Retry after connecting to the internet."),
                                      tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
                if(result == 1)
                    goto retry1;
                else
                    return;
            }
        }

        QStringList rempList;
        if(query.size()>0){
            while(query.next()){
                rempList.append(query.value("EmpID").toString());
            }
        }

        QStringList aTempList = mangID;
        currentMangIDs = QStringList();
        currSalaryList = QStringList();
        currMangNames = QStringList();
        currQList = QStringList();
        //setting mangBox values
        for (int item=0; item < aTempList.length(); item++) {
            if (rempList.contains(aTempList.at(item))){
                currentMangIDs.append(aTempList.at(item));
                currSalaryList.append(salaryList.at(item));
                currMangNames.append(mangNames.at(item));
                currQList.append(qList.at(item));
            }
        }

        int len = headBox->count()-1;
        for(int i=0; i<len; i++){
            headBox->removeItem(headBox->count()-1);
        }

        for(int i = 0; i<currentMangIDs.length(); i++) {
            headBox->addItem(currMangNames.at(i));
        }

        chNameLabel->setText(tr("%1").arg(tempName));
    } else {
        chNameLabel->setText(tr("<qt><b><center>__</center></b></qt>"));
    }
}

void NewHead::salaryChanged(int ind)
{
    if (ind != 0){
        salaryEdit->setText(salaryList.at(ind-1));
        degreeLabel->setText(qList.at(ind-1));
    }
    else {
        salaryEdit->setText("");
        degreeLabel->setText("");
    }
}

void NewHead::editPressed()
{
    salaryEdit->setEnabled(true);
}

void NewHead::cancelPressed()
{
    disconnectDatabase();
    this->close();
}

void NewHead::proceedPressed()
{
    rLoad(1);
    QString error="";
    if(headBox->currentIndex()!=0 && salaryEdit->text().isEmpty()) {
        error  = tr("Please enter salary of the new head of department.");
        salaryEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if (headBox->currentIndex()==0 && !salaryEdit->text().isEmpty()) {
        error = tr("Please select new head of department or set salary to blank.");
        salaryEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(depBox->currentIndex() == 0) {
        error = tr("Please select any department, you want to modify.");
    }

    if (!error.isEmpty()) {
        rLoad(0);
        QMessageBox::information(this,
                                 tr("Error! : %1").arg(qApp->applicationName()),
                                 tr("%1").arg(error),
                                 QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    if(!myDatabase.isOpen()) {
        if(!connectDatabase()) {
            cancelPressed();
        }
    }

    QSqlQuery query(myDatabase);

    QString dateChecking = " select FromDate from ManagerDepLog "
                           " where MangID = "+headID+" and "
                           " DepID = '"+didList.at(depBox->currentIndex()-1)+"' and "
                           " ToDate is NULL;";
    checkAgain:
    rLoad(0);
    if(!query.exec(dateChecking)) {
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."),
                              tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto checkAgain;
        else{
            return;
        }
    }
    rLoad(1);
    if(query.size() > 0) {
        if(query.next()) {
            rLoad(0);
            if(QDate::currentDate().toString("yyyy-MM-dd") == query.value("FromDate").toString()){
                QMessageBox::information(this,
                                      tr("Frequent Change : %1").arg(qApp->applicationName()),
                                      tr("\tChanges are too frequent!\n"
                                         "You changed head of this department today itself, Please "
                                         "try after a day to make further changes."),
                                      QMessageBox::Ok | QMessageBox::Default);
                return;
            }
        }
    }

    QString salaryQuery = "";
    QString udQuery = "";
    QString inQuery = "";
    if(headBox->currentIndex()!= 0){
        if(chNameLabel->text().isEmpty()){
            salaryQuery = " update Employee set Salary = "+salaryEdit->text()+" where "
                          " binary EmpID="+currentMangIDs.at(headBox->currentIndex()-1)+" "
                          " and binary LocalDID='"+mDetail.getDID()+"';";
            udQuery = " INSERT INTO DepartmentMang(MangID, DepID) VALUES ("+ currentMangIDs.at(headBox->currentIndex()-1)+
                      ", '"+didList.at(depBox->currentIndex()-1)+ "');"
                      " update EmployeeDep set Designation = 'HOD' "
                      " where EmpID = '"+currentMangIDs.at(headBox->currentIndex()-1)+"'; ";
            inQuery = " INSERT INTO ManagerDepLog(MangID, DepID, FromDate, ToDate) VALUES ("+currentMangIDs.at(headBox->currentIndex()-1) +
                    ",'" + didList.at(depBox->currentIndex()-1) + "','" +QDate::currentDate().toString("yyyy-MM-dd")+"', NULL);";
        } else {
            salaryQuery = " update Employee set Salary = "+salaryEdit->text()+" where "
                          " binary EmpID="+currentMangIDs.at(headBox->currentIndex()-1)+" "
                          " and binary LocalDID='"+mDetail.getDID()+"';";
            udQuery = " update DepartmentMang set MangID="+currentMangIDs.at(headBox->currentIndex()-1)+" "
                      " where binary MangID="+headID+" and "
                      " binary DepID = '"+didList.at(depBox->currentIndex()-1)+"'; "
                      " update EmployeeDep set Designation = 'worker' "
                      " where EmpID = '"+headID+"'; "
                      " update EmployeeDep set Designation = 'HOD' "
                      " where EmpID = '"+currentMangIDs.at(headBox->currentIndex()-1)+"'; ";
            inQuery = " update ManagerDepLog set ToDate='"+QDate::currentDate().toString("yyyy-MM-dd")+"' "
                      " where binary MangID="+headID+" and "
                      " binary DepID = '"+didList.at(depBox->currentIndex()-1)+"' and ToDate is NULL; "
                      " INSERT INTO ManagerDepLog(MangID, DepID, FromDate, ToDate) VALUES ("+currentMangIDs.at(headBox->currentIndex()-1) +
                      ",'" + didList.at(depBox->currentIndex()-1) + "','" +QDate::currentDate().toString("yyyy-MM-dd")+"', NULL);";
        }
    } else {
        udQuery = " delete from DepartmentMang where binary MangID = '"+headID+"' and binary DepID='"+
                didList.at(depBox->currentIndex()-1)+"'; "
                " update EmployeeDep set Designation = 'worker' "
                " where EmpID = '"+headID+"'; ";
        inQuery = " update ManagerDepLog set ToDate='"+QDate::currentDate().toString("yyyy-MM-dd")+"' "
                  " where binary MangID="+headID+" and "
                  " binary DepID = '"+didList.at(depBox->currentIndex()-1)+"' and ToDate is NULL; ";

        rLoad(0);
        int res = QMessageBox::critical(this,
                              tr("Application Error! - %1").arg(qApp->applicationName()),
                              tr("Please select any new department head otherwise head of department will be"
                                 "unset automatically and some functions of application may not work properly.\n"
                                 "Do you want to continue?"),
                              tr("&Yes"), tr("&No"), QString(), 0, 1);
        if(res == 1){
            return;
        }
        rLoad(1);
    }

    QString queryString = "START TRANSACTION; " +  salaryQuery + udQuery + inQuery + " COMMIT;";

    retry:
    rLoad(0);
    if(!query.exec(queryString)){
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."),
                              tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry;
        else{
            cancelPressed();
        }
    }
    rLoad(1);
    QTimer::singleShot(2000, this, SLOT(showMessage()));
    if(headBox->currentIndex() != 0){
        OfflineEmpEdit::editSalary(currentMangIDs.at(headBox->currentIndex()-1), salaryEdit->text());
        OfflineEmpEdit::editDesignation(currentMangIDs.at(headBox->currentIndex()-1), "HOD");
        OfflineEmpEdit::editDesignation(headID, "Worker");
        OfflineDepRegistration::editHead(didList.at(depBox->currentIndex()-1), currentMangIDs.at(headBox->currentIndex()-1));
    } else {
        OfflineEmpEdit::editDesignation(headID, "Worker");
        OfflineDepRegistration::editHead(didList.at(depBox->currentIndex()-1), "");
    }
}

void NewHead::showMessage()
{
    QString tmp;
    if(headBox->currentIndex() == 0){
        tmp = "NULL";
    } else {
        tmp = mangNames.at(headBox->currentIndex()-1);
    }
    rLoad(0);
    QMessageBox::information(this,
                             tr("Update Successfull! - %1").arg(qApp->applicationName()),
                             tr("<qt>Head of Department of <b>%1</b> is changed to <b>%2</b> successfully.\n\nThank You.</qt>")
                             .arg(depBox->currentText()).arg(tmp),
                             QMessageBox::Ok | QMessageBox::Default);
    cancelPressed();
}

bool NewHead::connectDatabase()
{
    if(!myDatabase.contains("newHead")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "newHead");
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

void NewHead::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("newHead");
}

NewHead::~NewHead()
{
    disconnectDatabase();
}

void NewHead::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}

void NewHead::rLoad(int i)
{
    if(i == 1){
        depBox->setEnabled(false);
        headBox->setEnabled(false);
        salaryEdit->setEnabled(false);
        editButton->setEnabled(false);
        cancelButton->setEnabled(false);
        proceedButton->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 -64;
        loadingLabel->setGeometry(x,y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        depBox->setEnabled(true);
        headBox->setEnabled(true);
        salaryEdit->setEnabled(true);
        editButton->setEnabled(true);
        cancelButton->setEnabled(true);
        proceedButton->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}
