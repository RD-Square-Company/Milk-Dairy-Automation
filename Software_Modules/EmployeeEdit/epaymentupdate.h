#ifndef EPAYMENTUPDATE_H
#define EPAYMENTUPDATE_H

#include <QDialog>
#include "ui_paymentupdate.h"
#include <QMovie>
#include <QCheckBox>
#include <QList>
#include <QSqlDatabase>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "offlineempedit.h"

class EPaymentUpdate : public QDialog, public Ui::PaymentUpdate
{
    Q_OBJECT
public:
    EPaymentUpdate(QString empID, QString emailID, QWidget *parent = 0);
    void closeEvent(QCloseEvent *);
    void paintEvent(QPaintEvent *event);

signals:
    void remakeMe();

private slots:
    void okPressed();
    void deletePressed();
    void newPressed();
    void cancelPressed();
    void updatePressed();
    void accountTypeChanged(int type);
    void showMessage();
    void sendSignal();

private:
    bool connectDatabase();
    void disconnectDatabase();
    void rLoad(int i);
    void setWidgets();
    void setTableValue();
    bool saveData();
    void sendMail();

    QString custID; //it will save empid of employee
    QString emailID;
    QString eID; //it will save bid of payment account
    //Both needs to be change to empID and bID in future
    QSqlDatabase myDatabase;
    QMovie *loading;
    QLabel *loadingLabel;
    QList<QCheckBox *> checkList;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
};

#endif // EPAYMENTUPDATE_H
