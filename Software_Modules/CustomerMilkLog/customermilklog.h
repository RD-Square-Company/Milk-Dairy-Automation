#ifndef CUSTOMERMILKLOG_H
#define CUSTOMERMILKLOG_H

#include "../AdditionalCustomer/additionalcustomer.h"
#include "ui_customermilklog.h"
#include <QTimer>
#include <QMovie>
#include "../CustomerRegistration/offlinecustregistration.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/onlinedetail.h"
#include "message.h"
#include "syncmilklog.h"

class CustomerMilkLog : public QWidget, public Ui::CustomerMilkLog
{
    Q_OBJECT
public:
    CustomerMilkLog(QWidget *parent = 0);
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *event);

public slots:
    void gotMilkPrice();

private slots:
    void setAddMilkLog(bool set);
    void updateAddCustMilkLog();
    void updateClockTime();
    void consumerCppChanged(int index);
    void producerPpChanged(int index);
    void clrActivated(bool stat);
    void searchCustomer();
    void submitPressed();
    void showMessage();
    void hideAddCustLog();
    void syncData();

signals:
    void requireMilkPrice(int index);

private:
    void setWidgets();
    void rLoad(int i);
    bool saveDataOffline();

    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
    AdditionalCustomer *addCustLog;
    QString prodID;
    QString consID;
    bool set;
    QTimer *timer;
    QTimer *clockTimer;
    QTimer *messageTimer;
    QMovie *namePoint;
    QLabel *loadingLabel;
    QMovie *loading;
    bool gotPrice;
    float milkPrice;
    Message *message;
    int setMessage;
    SyncMilkLog *syncMilkLog;
    QPushButton *syncButton;
};

#endif // CUSTOMERMILKLOG_H
