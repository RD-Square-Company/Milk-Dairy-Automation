#ifndef EMPLOYEEUPDATE_H
#define EMPLOYEEUPDATE_H

#include <QWidget>
#include "ui_employeeupdate.h"
#include <QMovie>
#include <QCompleter>
#include <QSqlDatabase>
#include <QDataWidgetMapper>
#include <QSqlQueryModel>
#include "epaymentupdate.h"
#include <QStringListModel>
#include "../MyDetail/onlinedetail.h"
#include "../MyDetail/graphicdetail.h"
#include "offlineempedit.h"

class EmployeeUpdate : public QWidget, public Ui::EmployeeUpdate
{
    Q_OBJECT
public:
    EmployeeUpdate(QWidget *parent = 0);
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void updatePressed();
    void showPayment();
    void remakePayment();
    void employeeChanged(int row);
    void showMessage();

public slots:
    //void getDeptValues(QStringList depNames);

private:
    void setWidgets();
    void sendMail();
    bool connectDatabase();
    void disconnectDatabase();
    void modelQuery();
    void updateValue();
    void rLoad(int i);
    bool checkInfo();
    void setDepartment();
    void editSetting(int i);
    //void setTempConnection();

    OnlineDetail oDetail;
    QSqlDatabase myDatabase;
    QSqlQueryModel *model;
    QDataWidgetMapper *mapper;
    QCompleter *completer;
    QStringListModel *stringModel;
    EPaymentUpdate *paymentUpdate;
    QMovie *loading;
    QLabel *loadingLabel;
    int setDept;
    GraphicDetail gDetail;
};

#endif // EMPLOYEEUPDATE_H
