#include "acceptrequest.h"
#include <QStringList>
#include "picload.h"
#include <QCheckBox>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QHBoxLayout>

AcceptRequest::AcceptRequest(QWidget *parent)
    : QDialog(parent)
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
    loading = new QMovie(uc.loadImage1);
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
    connect(rSelButton, SIGNAL(clicked(bool)),
            this, SLOT(rSelPressed()));
    connect(rAllButton, SIGNAL(clicked(bool)),
            this, SLOT(rAllPressed()));
    connect(aSellButton, SIGNAL(clicked(bool)),
            this, SLOT(aSelPressed()));
    connect(aAllButton, SIGNAL(clicked(bool)),
            this, SLOT(aAllPressed()));
    connect(refreshButton, SIGNAL(clicked(bool)),
            this, SLOT(doTask()));
    //all the connections are done

    //setting all the widgets according to the request's count;
    setWidgets();
}

void AcceptRequest::setWidgets()
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

void AcceptRequest::doTask()
{
    //checking if database is open or not, if not then open it or show message if error is occured
    if(!myDatabase.isOpen()){
        if(!connectDatabase()){
            return;
        }
    }

    //setting query to query model
    queryModel->setQuery("select "
                         "dairy.LocalDID, dairy.Logo, dairy.Name, concat_ws(' ', dairyOwner.DOFName, dairyOwner.DOMName, dairyOwner.DOLName), dairyOwner.PContact, dairyOwner.SContact, "
                         "dairyWPED.Email_id ,concat_ws(' ', dairy.Street, dairy.City, dairy.State, dairy.Pincode) "
                         "from dairy, dairyOwner, dairyrequestlog, dairyownerlog, dairyWPED "
                         "where dairy.LocalDID = dairyOwnerlog.LocalDID "
                         "and dairyWPED.LocalDID = dairy.LocalDID "
                         "and dairyownerlog.OwnerID = dairyowner.OwnerID "
                         "and dairy.LocalDID = dairyrequestlog.SendDairy "
                         "and dairyrequestlog.IsDeniedAccept = '0'  "
                         "and dairyrequestlog.RForHD = '1'  "
                         "and dairyrequestlog.ToDairy = '" + uc.dairyID + "';", myDatabase);

    if(!queryModel->hasIndex(0,0)){
        tableWidget->setEnabled(false);
        rSelButton->setEnabled(false);
        rAllButton->setEnabled(false);
        aSellButton->setEnabled(false);
        aAllButton->setEnabled(false);
        disconnectDatabase();
        return;
    }

    tableWidget->setEnabled(true);
    rSelButton->setEnabled(true);
    rAllButton->setEnabled(true);
    aSellButton->setEnabled(true);
    aAllButton->setEnabled(true);


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
                checkBox->setCheckable(true);
                checkBox->setChecked(false);
                tableWidget->setCellWidget(row, column, checkBox);
            } else {
                tableWidget->setItem(row, column,
                                     new QTableWidgetItem(queryModel->data(queryModel->index(row, column)).toString()));
                //tableWidget->setColumnWidth(column, 400);
            }
        }
    }

    totalLabel->setText(tr("<html><p><font align=\"center\" color=\"red\">You got total %1 request(s) for branch registration</font></p></html>")
                        .arg(queryModel->rowCount()));

    disconnectDatabase();
}

bool AcceptRequest::connectDatabase()
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

void AcceptRequest::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("remoteDBase");
}

void AcceptRequest::cancelPressed()
{
    delete queryModel;
    disconnectDatabase();
    this->close();
}

void AcceptRequest::rSelPressed()
{
    
}

void AcceptRequest::rAllPressed()
{

}

void AcceptRequest::aSelPressed()
{
    for(int row =0; tableWidget->rowCount(); row++){

    }
}

void AcceptRequest::aAllPressed()
{

}
