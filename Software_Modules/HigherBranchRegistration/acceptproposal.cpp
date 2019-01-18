#include "acceptproposal.h"
#include <QStringList>
#include "../LocalBranchRegistration/picload.h"
#include <QCheckBox>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QTimer>
#include "../CustomerRegistration/smtp.h"
#include <QDateTime>
#include <QImage>

AcceptProposal::AcceptProposal(QWidget *parent)
    :  QWidget(parent)
{
    //setting ui  to accept request
    setupUi(this);
    refreshButton = new QPushButton("Refresh", this);
    refreshButton->setGeometry(this->rect().right()-70,20, 60, 25);
    refreshButton->show();

    //hiding mapLabel
    mapLabel = new QLabel(this);
    mapLabel->hide();

    //loading
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //set attribute to the window
    setAttribute(Qt::WA_DeleteOnClose);

    //setting query model
    queryModel = new SqlQueryModel;

    //setting basic mapper
    mapper = new QDataWidgetMapper(this);

    //connections of accept request class
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    connect(rAllButton, SIGNAL(clicked(bool)),
            this, SLOT(rAllPressed()));
    connect(aSellButton, SIGNAL(clicked(bool)),
            this, SLOT(aSelPressed()));
    connect(refreshButton, SIGNAL(clicked(bool)),
            this, SLOT(refreshPressed()));
    //all the connections are done

    //setting all the widgets according to the request's count;
    setWidgets();
}

void AcceptProposal::setWidgets()
{
    //setting properties of mapper
    PicLoad *delegate = new PicLoad(mapper);
    mapper->setModel(queryModel);
    mapper->setItemDelegate(delegate);
    mapper->addMapping(mapLabel, 1);

    //header name list

    QStringList headerList;
    headerList << "Dairy ID" << "Dairy Logo" << "Dairy Name" << "Secratary Name" << "Primary Contact" << "Secondary Contact"
               << "Email ID" <<"Address" << "About Dairy";
    //setting coloumn count to the table widget
    tableWidget->setColumnCount(headerList.count());

    //setting header to the table widget
    for(int i=0; i<headerList.count(); i++){
        tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(headerList.at(i)));
    }

    doTask();
}

void AcceptProposal::refreshPressed()
{
    emit transformMe();
}

void AcceptProposal::doTask()
{
    if(checkList.count() > 0){
        checkList.clear();
    }
    //checking if database is open or not, if not then open it or show message if error is occured
    if(!myDatabase.isOpen()){
        if(!connectDatabase()){
            return;
        }
    }

    //setting query to query model
    queryModel->setQuery("select "
                         "Dairy.LocalDID, Dairy.Logo, Dairy.Name, concat_ws(' ', DairyOwner.DOFName, DairyOwner.DOMName, DairyOwner.DOLName), DairyOwner.PContact, DairyOwner.SContact, "
                         "DairyWPED.Email_id ,concat_ws(' ', Dairy.Street, Dairy.City, Dairy.State, Dairy.Pincode), Dairy.Description "
                         "from Dairy, DairyOwner, DairyRequestLog, DairyOwnerLog, DairyWPED "
                         "where binary Dairy.LocalDID = DairyOwnerLog.LocalDID "
                         "and binary DairyWPED.LocalDID = Dairy.LocalDID "
                         "and binary DairyOwnerLog.OwnerID = DairyOwner.OwnerID "
                         "and binary Dairy.LocalDID = DairyRequestLog.SendDairy "
                         "and DairyRequestLog.IsDeniedAccept = '0'  "
                         "and DairyRequestLog.RForHD = '0'  "
                         "and binary DairyRequestLog.ToDairy = '" + mDetail.getDID() + "';", myDatabase);

    if(!queryModel->hasIndex(0,0)){
        tableWidget->setEnabled(false);;
        rAllButton->setEnabled(false);
        aSellButton->setEnabled(false);
        disconnectDatabase();
        return;
    }

    tableWidget->setEnabled(true);
    rAllButton->setEnabled(true);
    aSellButton->setEnabled(true);


    //setting table widget to requests

    QLabel *label;

    for(int row =0; row < queryModel->rowCount(); row++){

        //adding new row to qtablewidget
        if(queryModel->rowCount() > tableWidget->rowCount())
            tableWidget->insertRow(tableWidget->rowCount());

        for(int column =0; column < queryModel->columnCount(); column++){

            if(row == 0)
                mapper->toFirst();
            else
                mapper->toNext();

            label = mapLabel;

            if(column == 1){
                tableWidget->setCellWidget(row, column, label);
            } else if(column == 0){
                QCheckBox *checkBox = new QCheckBox(queryModel->data(queryModel->index(row, column)).toString(), tableWidget);
                checkBox->setChecked(false);
                checkList.insert(row, new QCheckBox());
                checkList[row] = checkBox;
                tableWidget->setCellWidget(row, column, checkList.at(row));
            } else {
                tableWidget->setItem(row, column,
                                     new QTableWidgetItem(queryModel->data(queryModel->index(row, column)).toString()));
                //tableWidget->setColumnWidth(column, 400);
            }
        }
    }

    totalLabel->setText(tr("<html><p><font align=\"center\" color=\"red\">You got total %1 Proposal(s) for branch registration</font></p></html>")
                        .arg(queryModel->rowCount()));

    disconnectDatabase();
}

bool AcceptProposal::connectDatabase()
{
    if(!myDatabase.contains("remoteDBase")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "remoteDBase");
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

void AcceptProposal::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("remoteDBase");
}

void AcceptProposal::cancelPressed()
{
    delete queryModel;
    disconnectDatabase();
    this->close();
}


void AcceptProposal::transformAndMessage()
{
    rLoad(0);
    QMessageBox::information(this, tr("Saved! - %1").arg(qApp->applicationName()),
                             tr("Information Uploaded!\n"
                                "Your information is  updated to the server. Please restart the app.\n\nThank You"),
                             QMessageBox::Ok|QMessageBox::Default);
    emit transformMe();
}

void AcceptProposal::rAllPressed()
{
    rLoad(1);
    for(int row=0 ; row < tableWidget->rowCount(); row++){
        if(checkList.at(row)->isChecked()){
            checkList[row]->setChecked(false);
        }
        statusList.insert(row, 2);
        statusList[row] = 2;
    }

    if(!saveData()){
        QMessageBox::information(this, tr("Internal Error - %1").arg(qApp->applicationName()),
                                 tr("Something went wrong!\n"
                                    "Your information is not updated due to some errors, possibly network connection problem!"
                                    "Please try after some time.\n\nThank You"),
                                 QMessageBox::Ok|QMessageBox::Default);
        //generating a signal to delete itself and transform in new
        emit transformMe();
    } else {
        sendMail();
        int mul =0;
        for(int co=0; co<checkList.count(); co++){
            if(checkList.at(co)->isChecked())
                mul += 1;
        }
        QTimer::singleShot(mul*10000, this, SLOT(transformAndMessage()));
    }
}

void AcceptProposal::aSelPressed()
{
    rLoad(1);
    //setting restriction
    int counter = 0;
    for(int row =0; row<tableWidget->rowCount(); row++){
        if(checkList.at(row)->isChecked())
            counter++;
    }

    if(counter > 1){
        QMessageBox::information(this, tr("Selection Exceeded - %1").arg(qApp->applicationName()),
                                 tr("Select only one dairy sir!"),
                                 QMessageBox::Ok| QMessageBox::Default);
        rLoad(0);
        return;
    } else if( counter == 0){
        QMessageBox::information(this, tr("No Selection - %1").arg(qApp->applicationName()),
                                 tr("You not selected any diary sir!"),
                                 QMessageBox::Ok| QMessageBox::Default);
        rLoad(0);
        return;
    }

    for(int row=0; row<tableWidget->rowCount(); row++){
        if(checkList.at(row)->isChecked()){
            statusList.insert(row, 1);
            statusList[row] = 1;
        } else {
            statusList.insert(row, 0);
            statusList[row] = 0;
        }
    }
    if(!saveData()){
        QMessageBox::information(this, tr("Internal Error - %1").arg(qApp->applicationName()),
                                 tr("Something went wrong!\n"
                                    "Your information is not updated due to some errors, possibly network connection problem!"
                                    "Please try after some time.\n\nThank You"),
                                 QMessageBox::Ok|QMessageBox::Default);
        //generating a signal to delete itself and transform in new
        emit transformMe();
    } else {
        sendMail();
        QTimer::singleShot(2000, this, SLOT(transformAndMessage()));
        QString hb = "";
        for(int row=0; row<tableWidget->rowCount(); row++){
            if(statusList.at(row) == 1) {
                hb = checkList.at(row)->text();
                break;
            }
        }
        QString tmpString = " select D.Name as name,DO.DOFName as first, DO.DOMName as middle, DO.DOLName as last, D.Street as street , D.City as city, D.State as state, D.Pincode as pincode, D.Logo as logo, DO.pContact  as pc, "
                  "DO.sContact as sc, DW.Email_id as email from Dairy D, DairyOwner DO, DairyWPED DW, DairyOwnerLog DOL "
                  "where D.LocalDID = DOL.LocalDID and "
                  "DO.OwnerID = DOL.OwnerID and "
                  "D.LocalDID = DW.LocalDID and "
                  " binary D.LocalDID = '"+ hb + "';";
        if(myDatabase.isOpen()) {
            QSqlQuery tmpQuery(myDatabase);
            if(!tmpQuery.exec(tmpString)) {
                return;
            }
            if(tmpQuery.size()>0){
                if(tmpQuery.next()) {
                    QString name = tmpQuery.value("name").toString();
                    QString first = tmpQuery.value("first").toString();
                    QString middle = tmpQuery.value("middle").toString();
                    QString last = tmpQuery.value("last").toString();
                    QString street = tmpQuery.value("street").toString();
                    QString city = tmpQuery.value("city").toString();
                    QString state = tmpQuery.value("state").toString();
                    QString pincode = tmpQuery.value("pincode").toString();
                    QByteArray ba = tmpQuery.value("logo").toByteArray();
                    QImage logo;
                    logo.loadFromData(ba, "JPG");
                    QString pc = tmpQuery.value("pc").toString();
                    QString sc = tmpQuery.value("sc").toString();
                    HigherBranch hbranch;
                    hbranch.setDairyInfo(hb,name,street, city,state,pincode,logo);
                    hbranch.setOwnerInfo(first, middle, last, pc, sc);
                    mDetail.setAhb(hb);
                }
            }
        }
        disconnectDatabase();
    }
}

bool AcceptProposal::saveData()
{
    bool isOk = true;
    QString queryString;

    //connect database if not connected
    if(!myDatabase.isOpen()){
        //if database is not connected then return
        if(!connectDatabase()){
            return false;
        }
    }

    QSqlQuery query(myDatabase);

    //start transaction
    QSqlDatabase::database("remoteDBase").transaction();

    //deactivate the higher dairy of local dairy
    for(int row=0; row<tableWidget->rowCount();row++){
        if(statusList.at(row) == 1){
            queryString = "update DairyHB set IsActive = '0' where "
                                     "binary LocalDID = '" + mDetail.getDID() +
                                     "' and IsActive = '1'; ";
            if(!query.exec(queryString)){
                 isOk = false;
                //finish transaction, show error message and return;
            }
        }
    }

    if(isOk){
        queryString = " START TRANSACTION; ";

        //accept or denied request of local dairy
        for(int row=0 ; row<tableWidget->rowCount(); row++){
            if(statusList.at(row) != 0){
                QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm:ss");
                queryString += " update DairyRequestLog set  "
                               "IsDeniedAccept = '" + QString::number(statusList.at(row))  +
                        "' where binary SendDairy = '" + checkList.at(row)->text() + "' and binary ToDairy = '" + mDetail.getDID() + "' and RForHD = '0';";
                queryString += " update DairyRequestLog set  "
                               "AcceptDeniedDate = '" +dateTime +"' where binary SendDairy = '" + checkList.at(row)->text() + "' and binary ToDairy = '" +
                        mDetail.getDID() + "' and RForHD = '0';";
            }
        }

        queryString += " COMMIT;";

        if(!query.exec(queryString)){
            isOk = false;
        }

        if(isOk){
            //activate over dairy as a higher dairy of the local diary
            for(int row = 0; row < tableWidget->rowCount(); row++){
                if(statusList.at(row) == 1){
                    queryString = "select * from DairyHB where binary LocalDID = '" + mDetail.getDID() + "' and "
                                  "binary HBID = '" + checkList.at(row)->text() + "';";
                    //check if the dairy is already a previous higher dairy of local diary or not?
                    if(query.exec(queryString)){
                        if(query.size() > 0){
                            if(query.next()){
                                queryString = " update DairyHB set IsActive  = '1' where binary LocalDID = '" +mDetail.getDID() + "' and "
                                               "binary HBID = '" + checkList.at(row)->text() + "';";
                                if(!query.exec(queryString)){
                                    isOk = false;
                                    //finish transaction, show error message and return ;
                                }
                            }
                        } else {
                            queryString = " insert into DairyHB (LocalDID, HBID, IsActive ) values ('" + mDetail.getDID() + "', '" + checkList.at(row)->text() + "', '1');";
                            if(!query.exec(queryString)){
                                isOk = false;
                                //finish transaction, show error message and return;
                            }
                        }
                    } else {
                        isOk = false;
                        //finish transaction, show error message and retrun;
                    }
                }
            }
        }

    }

    QSqlDatabase::database("remoteDBase").commit();
    return isOk;
}


void AcceptProposal::sendMail()
{
    for(int row=0; row<tableWidget->rowCount(); row++){
        if(statusList.at(row) == 1){
            QString subject = "Request Accepted!";
            QString message = tr("Congratulations ! \n\nDear %1,\n This is %2 and we are very happy to inform you that we are now act as your local branch."
                                 "For further details, please call us on +91 %3").arg(checkList.at(row)->text()).arg(mDetail.getDID()).arg(mDetail.getpc());

            Smtp *smtp = new Smtp(oDetail.getHostEmail(), oDetail.getHostEmailPass(), "smtp.gmail.com");

            //sending message to dairy
            smtp->sendMail(oDetail.getHostEmail(), tableWidget->item(row, 6)->text() ,subject, message);
        }
    }
}


void AcceptProposal::rLoad(int i)
{
    if(i == 1){
        tableWidget->setEnabled(false);
        cancelButton->setEnabled(false);
        rAllButton->setEnabled(false);
        aSellButton->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 -64;
        loadingLabel->setGeometry(x,y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        tableWidget->setEnabled(true);
        cancelButton->setEnabled(true);
        rAllButton->setEnabled(true);
        aSellButton->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}

void AcceptProposal::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}
