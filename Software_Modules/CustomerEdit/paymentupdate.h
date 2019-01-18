#ifndef PAYMENTUPDATE_H
#define PAYMENTUPDATE_H

#include <QDialog>
#include "ui_paymentupdate.h"
#include <QMovie>
#include <QCheckBox>
#include <QList>
#include <QSqlDatabase>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "offlinecustedit.h"

class PaymentUpdate : public QDialog, public Ui::PaymentUpdate
{
    Q_OBJECT
public:
    PaymentUpdate(QString type, QString custID,QString emailID,QWidget *parent = 0);
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

    QString type;
    QString custID;
    QString bID;
    QString emailID;
    QSqlDatabase myDatabase;
    QMovie *loading;
    QLabel *loadingLabel;
    QList<QCheckBox *> checkList;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
};

#endif // PAYMENTUPDATE_H
