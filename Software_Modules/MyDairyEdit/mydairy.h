#ifndef MYDAIRY_H
#define MYDAIRY_H
#include <QWidget>
#include "ui_mydairy.h"
#include <QSqlDatabase>
#include "ownerupdate.h"
#include "dairyupdate.h"
#include "paymentupdate.h"
#include "newdepartment.h"
#include "newhead.h"
#include "employeedepartment.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "transportedit.h"

/*
 * This class is for showing dairy details, its employees, customer, departments and
 * local branches and giving fuctionality to update the information of transport, diary, owner
 * and dairy payment details and also add or remove employees from or to department.
 * This class doesn't directly implement the updation.......
 *
 */

class MyDairy : public QWidget, public Ui::MyDairy
{
  Q_OBJECT
public:
  MyDairy(QWidget *parent=0);

private slots:
  void quitPressed();
  void dairyDetails();
  void dairyPayment();
  void ownerDetails();
  void addNewDepartment();
  void departmentHead();
  void aREmployee();
  void transportDetails();
  void consumerChecked();
  void producerChecked();
  void optionChanged(int index);
  void remakePayment();

private:
  void setWidgets();
  void setTableValues();
  bool connectDatabase();
  void disconnectDatabase();
  void setThings();

  QSqlDatabase myDatabase;
  DairyUpdate *dairyUpdate;
  OwnerUpdate *ownerUpdate;
  PaymentUpdate *paymentUpdate;
  NewDepartment *newDepartment;
  NewHead *newHead;
  EmployeeDepartment *employeeDepartment;
  MyDetail mDetail;
  OnlineDetail oDetail;
  TransportEdit *transportEdit;
};

#endif // MYDAIRY_H
