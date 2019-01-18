#include "mydairy.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QHeaderView>
#include <QStringList>
#include <QImage>
#include <QMessageBox>
#include <QTableWidgetItem>

MyDairy::MyDairy(QWidget *parent) :
  QWidget(parent)
{
  //setting ui window to the class
  setupUi(this);

  //setting connections to the all the push buttons
  connect(quitButton, SIGNAL(clicked(bool)),
          this, SLOT(quitPressed()));
  connect(dDetailsButton, SIGNAL(clicked(bool)),
          this, SLOT(dairyDetails()));
  connect(dPaymentButton, SIGNAL(clicked(bool)),
          this, SLOT(dairyPayment()));
  connect(oDetailsButton, SIGNAL(clicked(bool)),
          this, SLOT(ownerDetails()));
  connect(nDeparmentButton, SIGNAL(clicked(bool)),
          this, SLOT(addNewDepartment()));
  connect(dManagerButton, SIGNAL(clicked(bool)),
          this, SLOT(departmentHead()));
  connect(eFDepartmentButton, SIGNAL(clicked(bool)),
          this, SLOT(aREmployee()));
  connect(transportButton, SIGNAL(clicked(bool)),
          this, SLOT(transportDetails()));
  connect(consumerBox, SIGNAL(stateChanged(int)),
          this, SLOT(consumerChecked()));
  connect(producerBox, SIGNAL(stateChanged(int)),
          this, SLOT(producerChecked()));
  connect(optionBox, SIGNAL(currentIndexChanged(int)),
          this, SLOT(optionChanged(int)));
  //connections is completed!

  //setting widgets of the MyDairy
  setWidgets();
}

//setting widgets of the MyDairy()
void MyDairy::setWidgets()
{
    //set basicinformation of dairy
    setThings();
  //set dairy logo and owner profile pic
  QImage image(mDetail.getLogo());
  dairyLogo->setPixmap(QPixmap::fromImage(image.scaled(100, 100, Qt::IgnoreAspectRatio)));
  image = QImage(mDetail.getpPic());
  ownerPhoto->setPixmap(QPixmap::fromImage(image.scaled(100, 100, Qt::IgnoreAspectRatio)));

  //by default set checked to the producer and consumer check box
  consumerBox->setCheckState(Qt::Checked);
  producerBox->setCheckState(Qt::Checked);

  //set default option 0
  optionBox->currentIndexChanged(0);
}

//querying for the model and set value to the table widget
void MyDairy::setTableValues()
{
  //removing table data from table widget
  int total = tableWidget->rowCount();
  for(int row=0; row< total; row++){
      tableWidget->removeRow(tableWidget->rowCount()-1);
    }

  QString queryString;

  //set different table headers for different options
  int index = optionBox->currentIndex();
  QStringList headerList;
  QStringList dataList;
  if(index == 0){
      //for employees
      headerList << "Employee Name" << "Employee Designation" << "Adhaar No" << "Date of Birth" << "Primary Contact"
                 << "Secondary Contact" << "Address" << "Date of Join" << "Highest Qualification"
                 << "Salary" << "Email ID";
      dataList << "EN"<< "EDD" << "AN" << "DOB" << "PC" << "SC" << "A" << "DOJ" << "HQ" << "S"
               << "EID";
      //set column count to table widget
      tableWidget->setColumnCount(headerList.count());

      tableWidget->setHorizontalHeaderLabels(headerList);

      //setting query for employees
      queryString = "select concat_ws(' ', E.EMPFName, E.EMPMName, E.EMPLName) as EN, ED.Designation as EDD, EPAE.AdhaarNo as AN, E.EmpDOB as DOB, "
                            "E.Pcontact as PC, E.Scontact as SC, concat_ws(' ', E.Street, E.City, E.State, E.Pincode) as A, E.DOJoin as DOJ, "
                            "E.HQualification as HQ, E.Salary as S, E.Email_ID as EID "
                            "from Employee E, EmployeePAE EPAE, EmployeeDep ED "
                            "where E.EmpID = EPAE.EmpID"
                            " and E.EmpID = ED.EmpID"
                            " and E.LocalDID = '"+ mDetail.getDID() + "';";
    } else if(index == 1) {
      //for customersx
      headerList << "Customer ID" << "Customer Name" << "Adhaar No" << "Primary Contact" << "Secondary Contact"
                 << "Address" << "Email ID" << "Have Android?";
      dataList << "CID" << "CN" << "AN" << "PC" << "SC" << "A" << "EID" << "HA";
      //set column count to table widget
      tableWidget->setColumnCount(headerList.count());

      tableWidget->setHorizontalHeaderLabels(headerList);

      //setting query for customer depending on cosumer and producer check box status
      if(consumerBox->isChecked() && producerBox->isChecked()){
          queryString = "select C.ConsID as CID, concat_ws(' ', C.ConsFName, C.ConsMName, C.ConsLName) as CN, CPAE.AdhaarNo as AN, C.Pcontact as PC, C.Scontact as SC, concat_ws(' ', C.Street, C.City, C.State, C.Pincode) as A, C.Email_ID as EID, C.IsApp as HA "
              "from Consumer C, ConsumerPAE CPAE "
              "where C.ConsID = CPAE.ConsID "
              "and C.LocalDID = '" + mDetail.getDID() + "' "
                                                  "union "
              "select P.ProdID as CID, concat_ws(' ', P.ProdFName, P.ProdMName, P.ProdLName) as CN, PPAE.AdhaarNo as AN, P.Pcontact as PC, P.Scontact as SC, concat_ws(' ', P.Street, P.City, P.State, P.Pincode) as A, P.Email_ID as EID, P.IsApp as HA "
              "from Producer P, ProducerPAE PPAE "
              "where P.ProdID = PPAE.ProdID "
              "and P.LocalDID = '" + mDetail.getDID() + "';";
        } else if(consumerBox->isChecked()){
          queryString = "select C.ConsID as CID, concat_ws(' ', C.ConsFName, C.ConsMName, C.ConsLName) as CN, CPAE.AdhaarNo as AN, C.Pcontact as PC, C.Scontact as SC, concat_ws(' ', C.Street, C.City, C.State, C.Pincode) as A, C.Email_ID as EID, C.IsApp as HA "
                        "from Consumer C, ConsumerPAE CPAE "
                        "where C.ConsID = CPAE.ConsID "
                        "and C.LocalDID = '" + mDetail.getDID() + "';";
        } else {
          queryString = "select P.ProdID as CID, concat_ws(' ', P.ProdFName, P.ProdMName, P.ProdLName) as CN, PPAE.AdhaarNo as AN, P.Pcontact as PC, P.Scontact as SC, concat_ws(' ', P.Street, P.City, P.State, P.Pincode) as A, P.Email_ID as EID, P.IsApp as HA "
                        "from Producer P, ProducerPAE PPAE "
                        "where P.ProdID = PPAE.ProdID "
                        "and P.LocalDID = '" + mDetail.getDID() + "';";
        }
    } else if(index == 2) {
      //for departments
      headerList << "Department ID" << "Department Name" << "Manager Name" << "From" << "Description";
      dataList << "DID" << "DN" << "MN" << "F" << "D";
      //set column count to table widget
      tableWidget->setColumnCount(headerList.count());

      tableWidget->setHorizontalHeaderLabels(headerList);

      //query for departments
      queryString = "select D.DepID as DID, D.DepName as DN, concat_ws(' ', E.EMPFName, E.EMPMName, E.EMPLName) as MN, MDL.FromDate as F, D.Description as D "
                    "from Department D, DepartmentMang DM, ManagerDepLog MDL, Employee E "
                    "where D.DepID = DM.DepID "
                    "and DM.DepID = MDL.DepID "
                    "and DM.MangID = MDL.MangID "
                    "and E.EmpID = MDL.MangID "
                    "and D.LocalDID ='" + mDetail.getDID() + "';";
    } else if(index == 3) {
      //for local branches
      headerList << "Dairy ID" << "Dairy Name" << "Email ID" << "Primary Contact" << "Secondary Contact" << "Address" << "Owner Name" << "Website" << "Description";
      dataList << "DID" << "DN" << "ED" << "PC" << "SC" << "A" << "ONT" << "W" << "D";
      //set column count to table widget
      tableWidget->setColumnCount(headerList.count());

      tableWidget->setHorizontalHeaderLabels(headerList);

      //query for local branches
      queryString = "select D.LocalDID as DID, D.Name as DN, DW.Email_id as ED, DOT.pContact as PC, DOT.sContact as SC, "
                    "concat_ws(' ', D.Street, D.City, D.State, D.Pincode) as A, concat_ws(' ', DOT.DOFName, DOT.DOMName, DOT.DOLName) as ONT,D.Website as W, D.Description as D  "
                    "from Dairy D, DairyOwner DOT, DairyOwnerLog DOL , DairyHB DHB, DairyWPED DW  "
                    "where D.LocalDID = DOL.LocalDID "
                    "and DOL.OwnerID  = DOT.OwnerID "
                    "and DHB.LocalDID = D.LocalDID "
                    "and DW.LocalDID = D.LocalDID "
                    "and DHB.IsActive = 1 "
                    "and DHB.HBID = '" + mDetail.getDID() + "';";
    } else {
      //for local branches
      headerList << "Dairy ID" << "Dairy Name" << "Email ID" << "Primary Contact" << "Secondary Contact" << "Address" << "Owner Name" << "Website" << "Description";
      dataList << "DID" << "DN" << "ED" << "PC" << "SC" << "A" << "ONT" << "W" << "D";
      //set column count to table widget
      tableWidget->setColumnCount(headerList.count());

      tableWidget->setHorizontalHeaderLabels(headerList);

      //query for local branches
      queryString = "select D.LocalDID as DID, D.Name as DN, DW.Email_id as ED, DOT.pContact as PC, DOT.sContact as SC, "
                    "concat_ws(' ', D.Street, D.City, D.State, D.Pincode) as A, concat_ws(' ', DOT.DOFName, DOT.DOMName, DOT.DOLName) as ONT,D.Website as W, D.Description as D  "
                    "from Dairy D, DairyOwner DOT, DairyOwnerLog DOL , DairyHB DHB, DairyWPED DW  "
                    "where D.LocalDID = DOL.LocalDID "
                    "and DOL.OwnerID  = DOT.OwnerID "
                    "and DHB.HBID = D.LocalDID "
                    "and DW.LocalDID = D.LocalDID "
                    "and DHB.IsActive = 1 "
                    "and DHB.HBID = '" + mDetail.getAhb()+ "';";
  }

  //checking connection of database
  if(!myDatabase.isOpen()){
      if(!connectDatabase()){
          return;
        }
    }
  QSqlQuery query(myDatabase);

  //setting value to the table widget
  if(query.exec(queryString)){
      totalLabel->setText(tr("<qt><b>Total:</b> (0)</qt>"));
      if(query.size() > 0){
          int row = 0;
          QTableWidgetItem *item;
          while (query.next()){
              tableWidget->insertRow(tableWidget->rowCount());
              for (int column =0; column < dataList.count(); column++){
                  item = new QTableWidgetItem();
                  item->setTextAlignment(Qt::AlignHCenter);
                  item->setText(query.value(dataList.at(column)).toString());
                  tableWidget->setItem(row, column, item);
                }
              row++;
              totalLabel->setText(tr("<qt><b>Total:</b> (%1)</qt>").arg(row));
            }
        }
    }
}

//quit from the program
void MyDairy::quitPressed()
{
 this->close();
}

//show the diary detail dialog box
void MyDairy::dairyDetails()
{
    //showing DairyUpdate widget to update information about dairy
    dairyUpdate = new DairyUpdate(this);
    dairyUpdate->exec();
    delete dairyUpdate;
}

//show dairy payment details dialog box
void MyDairy::dairyPayment()
{
    paymentUpdate = new PaymentUpdate();
    //setting remake of payment to remakePayment slot
    connect(paymentUpdate, SIGNAL(remakeMe()),
            this, SLOT(remakePayment()));

    paymentUpdate->exec();
}

void MyDairy::remakePayment()
{
    delete paymentUpdate;

    paymentUpdate = new PaymentUpdate();
    //setting remake of payment to remakePayment slot
    connect(paymentUpdate, SIGNAL(remakeMe()),
            this, SLOT(remakePayment()));

    paymentUpdate->exec();
}

//show owner details dialog box
void MyDairy::ownerDetails()
{
    // showing dialog box to update details of diary owner
    ownerUpdate = new OwnerUpdate(this);
    ownerUpdate->exec();
    delete ownerUpdate;
}

//show add new department dialog box
void MyDairy::addNewDepartment()
{
    newDepartment = new NewDepartment(this);
    newDepartment->exec();
    delete newDepartment;
}

//show department head dialog box
void MyDairy::departmentHead()
{
    newHead = new NewHead(this);
    newHead->exec();
    delete newHead;
}

//show add or remove employees from department dialog box
void MyDairy::aREmployee()
{
    employeeDepartment = new EmployeeDepartment(this);
    employeeDepartment->exec();
    delete employeeDepartment;
}

//show transport details dialog box
void MyDairy::transportDetails()
{
    transportEdit = new TransportEdit(this);
    transportEdit->exec();
    if(transportEdit) {
        delete transportEdit;
    }
}

//requery the model and set value to the table widget when state of the consumer checkbox
//is changed
void MyDairy::consumerChecked()
{
    //it will ensures that both the boxes never get empty together
    if (!(consumerBox->isChecked() || producerBox->isChecked())){
        consumerBox->setCheckState(Qt::Checked);
        producerBox->setCheckState(Qt::Checked);
    }
    //it will call setTablevalues() to set table values for consumer(s)
    setTableValues();
}

//requery the model and set value to the table widget when state of the producer checkbox
//is changed
void MyDairy::producerChecked()
{
    //it will ensures that both the boxes never get empty together
    if (!(consumerBox->isChecked() || producerBox->isChecked())){
        consumerBox->setCheckState(Qt::Checked);
        producerBox->setCheckState(Qt::Checked);
    }
    //it will call setTableValues() to set table values for producer(s)
    setTableValues();
}

/*
 * connect to the database and return true if database is connected else
 * return false
 */
bool MyDairy::connectDatabase()
{
  if(!myDatabase.contains("myDairy")){
      myDatabase = QSqlDatabase::addDatabase("QMYSQL", "myDairy");
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

//disconnect from database connection
void MyDairy::disconnectDatabase()
{
  myDatabase = QSqlDatabase();
  myDatabase.removeDatabase("myDairy");
}

//when option is changed from option box
void MyDairy::optionChanged(int index)
{
  if(index == 0){
      //for employees
      producerBox->hide();
      consumerBox->hide();
    } else if(index == 1) {
      //for costomers
      producerBox->show();
      consumerBox->show();

    } else if (index == 2) {
      //for department
      producerBox->hide();
      consumerBox->hide();

    } else {
      //for local/high branch
      producerBox->hide();
      consumerBox->hide();

    }
  //set table values accroding to the index
  setTableValues();
}

void MyDairy::setThings()
{
    //setting general information of the dairy to the label
    dairyNameLabel->setText(tr("%1").arg(mDetail.getdName()));
    tagLabel->setText(tr("%1").arg(mDetail.gettagline()));
    ownerLabel->setText(tr("<html><b>Owner:</b>%1, %2</html>").arg(mDetail.getofName() + mDetail.getomName() + mDetail.getolName()).arg(mDetail.getoCity()));
    dIDLable->setText(tr("<html><b>Dairy ID:</b> %1</html>").arg(mDetail.getDID()));
}
