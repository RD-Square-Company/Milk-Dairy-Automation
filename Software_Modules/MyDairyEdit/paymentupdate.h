#ifndef PAYMENTUPDATE_H
#define PAYMENTUPDATE_H

/*
 * This class is used to update the details of the payment of milk diary
 * which is registered with mds system.
 * It is same as the customer and employee payment info updation with slight
 * change...
 *
 */

#include <QDialog>
#include "ui_paymentupdate.h"
#include <QMovie>
#include <QCheckBox>
#include <QList>
#include <QSqlDatabase>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"

class PaymentUpdate : public QDialog, public Ui::PaymentUpdate
{
    Q_OBJECT
public:
    PaymentUpdate(QWidget *parent = 0);
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
    void updateOffline();
    void deleteOffline();

    QSqlDatabase myDatabase;
    QMovie *loading;
    QLabel *loadingLabel;
    QList<QCheckBox *> checkList;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
    QString bID;
};


#endif // PAYMENTUPDATE_H
