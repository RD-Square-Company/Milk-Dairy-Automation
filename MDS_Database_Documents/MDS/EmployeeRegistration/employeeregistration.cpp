#include "employeeregistration.h"
#include "../CustomerRegistration/smtp.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>

EmployeeRegistration::EmployeeRegistration(QWidget *parent)
    : QWidget(parent)
{
    registrationDialog = new ERegistration;
    paymentDialog = new Payment;
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(registrationDialog, 0, 0);

    //defining properties of window
    setAttribute(Qt::WA_DeleteOnClose);
    setLayout(mainLayout);

    //setting connections
    connect(registrationDialog, SIGNAL(nextByER()),
            this, SLOT(nextFromERF()));
    connect(registrationDialog, SIGNAL(closeByER()),
            this, SLOT(quit()));
    connect(registrationDialog, SIGNAL(setConnection()),
            this, SLOT(tempDBConnetion()));
    connect(paymentDialog, SIGNAL(regByPay()),
            this, SLOT(regFromPay()));
    connect(paymentDialog, SIGNAL(prevByPay()),
            this, SLOT(prevFromPay()));
    connect(paymentDialog, SIGNAL(quitByPay()),
            this, SLOT(quit()));
    connect(this, SIGNAL(sendDeptValues(QStringList)),
            registrationDialog, SLOT(getDeptValues(QStringList)));

    //all connections are done
}

void EmployeeRegistration::nextFromERF()
{
    registrationDialog->hide();
    paymentDialog->show();
    mainLayout->removeWidget(registrationDialog);
    mainLayout->addWidget(paymentDialog, 0,0);
}

void EmployeeRegistration::quit()
{
    int status = QMessageBox::warning(this, tr("Cancel Registration - %1").arg(qApp->applicationName()),
                                      tr("Your information will not be saved!\n\n"
                                         "Do you want to cancel Registration ? "),
                                      tr("&Yes"), tr("&No"), QString() , 0 , 1);

    if(status == 0) {
        delete paymentDialog;
        delete registrationDialog;
        this->close();
    }
}


void EmployeeRegistration::regFromPay()
{
    paymentDialog->rLoad(1);
    if(connectDatabase()){
        QString emp, empAcc, empPae, bank, bankAc, empDept;
        emp =  "INSERT INTO employee(EmpID, EMPFName, EMPMName, EMPLName, DOJoin, EmpDOB, Pcontact, Scontact,"
               " Street, City, State, Hqualification, IsActive, Pincode, Email_ID, Salary, LocalDID) VALUES (";

        bank = "INSERT INTO bankinfo(BID, NameOnAccount, ACType, BankName, IFSC_Code, BranchName,"
               " CVV, Expdate, LocalDID) VALUES (";

        QString value = getDeptID();

       QSqlDatabase::database().transaction();
        QSqlQuery query(mydatabase);

        if(!mydatabase.isOpen())
            connectDatabase();

        if(!query.exec("select max(EmpID) as maxID from Employee;")){
            QMessageBox::critical(this,
                                  tr("Connection Error! : %1").arg(qApp->applicationName()),
                                  tr("\tDatabase Connection Problem!\n"
                                     "Please make sure, you are connected to the internet service. "
                                     "Retry after connecting to the internet."
                                     "SQL Error Code - %1").arg(query.lastError().nativeErrorCode()),
                                  QMessageBox::Ok|QMessageBox::Default);
            disconnectDatabase();
            return ;
        }
        int empID;
        if(query.size()>0){
            if(query.next())
                empID = query.value("maxID").toInt();
        } else
            empID = 0;
        ++empID;

        emp += QString::number(empID) + ", '" + registrationDialog->firstNameEdit->text() + "', '" + registrationDialog->middleNameEdit->text() + "','" +
                registrationDialog->lastNameEdit->text() + "','" + registrationDialog->dojEdit->date().toString("yyyy-MM-dd") + "','" +registrationDialog->dobEdit->date().toString("yyyy-MM-dd") + "','" +
                registrationDialog->pContactEdit->text() + "','" + registrationDialog->sContactEdit->text() + "','" + registrationDialog->line1Edit->text() + "','" +
                registrationDialog->line2Edit->text() + "','"  + registrationDialog->stateBox->currentText() + "','" + registrationDialog->hQBox->currentText() + "','1', '" + registrationDialog->pincodeEdit->text() + "','" +
                registrationDialog->emailEdit->text() + "'," + registrationDialog->salaryEdit->text()+ ", '" + uc.dairyID + "');";
        QString adhaarNo = registrationDialog->ad1Edit->text() + registrationDialog->ad2Edit->text() +  registrationDialog->ad3Edit->text();
        empPae = "INSERT INTO EmployeePae (EmpID, AdhaarNo) VALUES  (" + QString::number(empID) + ",'" + adhaarNo + "');";

        empDept = "INSERT INTO EmployeeDep (EmpID, DepID, Designation) VALUES (" + QString::number(empID) + ",'" + value + "','" + registrationDialog->designationEdit->text() + "');";

        if(paymentDialog->acTypeBox->currentIndex() != 0) {
            //retreive highest bid from bankinfo
            if(!mydatabase.isOpen())
                connectDatabase();
            if(!query.exec("select max(BID) as maxBID from BankInfo;")){
                QMessageBox::critical(this,
                                      tr("Connection Error! : %1").arg(qApp->applicationName()),
                                      tr("\tDatabase Connection Problem!\n"
                                         "Please make sure, you are connected to the internet service. "
                                         "Retry after connecting to the internet."
                                         "SQL Error Code - %1").arg(query.lastError().nativeErrorCode()),
                                      QMessageBox::Ok|QMessageBox::Default);
                disconnectDatabase();
                return ;
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

            //insert values into bankinfo
            bank +=  QString::number(bid) + ",'" + paymentDialog->noaEdit->text() + "','" + paymentDialog->acTypeBox->currentText() + "','" +
                                            paymentDialog->bNameEdit->text() + "','" + paymentDialog->ifscEdit->text() + "','" +
                                            paymentDialog->bAddEdit->text() + "','" + paymentDialog->cvvEdit->text() + "','" + date + "','" + uc.dairyID + "');";

            //insert values into bankaccountno
            bankAc = "insert into BankAccountNo (BID, DCAccount) "
                         "values (" + QString::number(bid) + ",'" + paymentDialog->aNumberEdit->text() + "');";

            //insert values in employeeaccount
            empAcc = "insert into EmployeeAccount (EmpID, BID) values (" +
                    QString::number(empID) + "," + QString::number(bid) + ");";

            //selected query in casse of no payment account is registere by user
            QString allQuery = "START TRANSACTION;" +
                    emp +bank + bankAc + empAcc +  empPae + empDept  +
                    " COMMIT;";

            if(!mydatabase.isOpen())
                connectDatabase();
            if(!query.exec(allQuery)){
                //do something here
                QSqlDatabase::database().commit();
                paymentDialog->rLoad(0);
                disconnectDatabase();
                return;
            } else {
               QSqlDatabase::database().commit();
                disconnectDatabase();
                if(!registrationDialog->emailEdit->text().isEmpty()){
                    sentMail(registrationDialog->emailEdit->text(), registrationDialog->firstNameEdit->text() + " " + registrationDialog->lastNameEdit->text(),
                             registrationDialog->departmentBox->currentText(), registrationDialog->designationEdit->text(), registrationDialog->salaryEdit->text());
                }
                QTimer::singleShot(10000, this, SLOT(completionMessage()));
            }
            return;
        }

        //all query are done in single query by transaction in the case of payment account is no register by user
        QString allQuery = "START TRANSACTION;" +
                emp + empPae + empDept +
                " COMMIT;";

        if(!mydatabase.isOpen())
            connectDatabase();
        if(!query.exec(allQuery)){
            //do something here
            QSqlDatabase::database().commit();
            paymentDialog->rLoad(0);
            disconnectDatabase();
            return;
        } else {
           QSqlDatabase::database().commit();
            disconnectDatabase();
            if(!registrationDialog->emailEdit->text().isEmpty()){
                sentMail(registrationDialog->emailEdit->text(), registrationDialog->firstNameEdit->text() + " " + registrationDialog->lastNameEdit->text(),
                         registrationDialog->departmentBox->currentText(), registrationDialog->designationEdit->text(), registrationDialog->salaryEdit->text());
                QTimer::singleShot(10000, this, SLOT(completionMessage()));
            } else
                QTimer::singleShot(10000, this, SLOT(completionMessage()));

        }

    }
}

void EmployeeRegistration::prevFromPay()
{
    paymentDialog->hide();
    registrationDialog->show();
    mainLayout->removeWidget(paymentDialog);
    mainLayout->addWidget(registrationDialog, 0,0);
}

bool EmployeeRegistration::connectDatabase()
{
    mydatabase = QSqlDatabase::addDatabase("QMYSQL", "remoteDBase");
    mydatabase.setHostName(uc.hostName);
    mydatabase.setDatabaseName(uc.dataBase);
    mydatabase.setUserName(uc.databaseUName);
    mydatabase.setPassword(uc.databaseUPass);
    mydatabase.setPort(3306);
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

void EmployeeRegistration::disconnectDatabase()
{
    mydatabase = QSqlDatabase();
    mydatabase.removeDatabase("remoteDBase");
}

void EmployeeRegistration::bye()
{
    delete regCompDialog;
    registrationDialog->setDefault();
    paymentDialog->setDefault();
}

void EmployeeRegistration::sentMail(QString to, QString empName, QString deptName, QString designation, QString salary)
{
    QString subject  = tr("Job Letter");

    QString message = tr("Congratulations!\n"
                         "\tDear %1,\n\n"
                         "Great day sir! You have got a new job of %2 in %3 of %4. "
                         "Your salary is %5 Rs per month. You are kindly informed that you have to join on "
                         "today onwards.\n"
                         "%6 works on two shifts a day. One is morning shift and other is evening shift. So you may "
                         "hire to work full day or on shift only, it depends on milk dairy.You will be paid at end of the month "
                         "on the basis of your shift attendence.\n"
                         "\tThank you!\n\n"
                         "This message is generated by Milk Dairy Management System so for further information please visit %7"
                         " or call on '+91 %8'\n"
                         "\t\t\t\tvisit our website 'www.msysdairy.com'")
            .arg(empName)
            .arg(designation)
            .arg(deptName)
            .arg(uc.dairyName)
            .arg(salary)
            .arg(uc.dairyName)
            .arg(uc.dairyName)
            .arg(uc.dairyMobNo);

    Smtp *smtp = new Smtp(uc.hostEmail, uc.hostEPass, "smtp.gmail.com");

    //sending message to employee
    smtp->sendMail(uc.hostEmail, to, subject, message);
}

void EmployeeRegistration::tempDBConnetion()
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
        else
            sendDeptValues(deptValues);
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
        else
            sendDeptValues(deptValues);
    }

    deptValues.append("No Any Department  (A0)");
    if(query.size() > 0){
        while(query.next()){
            value = query.value("DepName").toString();
            value += "  (" + query.value("DepID").toString() + ")";
            deptValues.append(value);
        }
    }
    sendDeptValues(deptValues);
    localDatabase = QSqlDatabase();
    localDatabase.removeDatabase("localDBase");
}

QString EmployeeRegistration::getDeptID()
{
    QString tempText = registrationDialog->departmentBox->currentText();

    int index = tempText.indexOf('(');
    QString text = tempText.at(index+1);
    text += tempText.at(index + 2);
    return text;
}

void EmployeeRegistration::completionMessage()
{
    regCompDialog = new ERegComplete;
    regCompDialog->setValue(registrationDialog->firstNameEdit->text() + " " + registrationDialog->lastNameEdit->text(), registrationDialog->departmentBox->currentText(),
                            registrationDialog->designationEdit->text(), uc.dairyID);

    //connection for regComDialog
    connect(regCompDialog, SIGNAL(okBye()),
            this, SLOT(bye()));
    //complete connections of regcompdialog

    paymentDialog->rLoad(0);
    paymentDialog->hide();
    registrationDialog->show();
    mainLayout->removeWidget(paymentDialog);
    mainLayout->addWidget(registrationDialog);

    //setting all widgets to empty
    regCompDialog->exec();
}
