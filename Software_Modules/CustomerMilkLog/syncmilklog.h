#ifndef SYNCMILKLOG_H
#define SYNCMILKLOG_H

#include <QSqlDatabase>
#include "ui_syncmilklog.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"

class SyncMilkLog : public QWidget, public Ui::SyncMilkLog
{
    Q_OBJECT
public:
    SyncMilkLog(QWidget *parent =0);
    void paintEvent(QPaintEvent *event);
    bool uploadAddCust(QString mobileNo, QString custName);
    bool uploadAddCustLog(QString custID, QString date, QString shift, QString dateTime, QString animal,
                          QString quantity, QString price, QString isKg);
    bool uploadCustLog(QString custID, QString date, QString shift, QString dateTime, QString iskg, QString milkType,
                       QString quantity, QString snf, QString fat, QString waterPerc, QString price);

public slots:
    void setRange(int minimum, int maximum, QString format);
    void setValue(int value);
    void setText(QString text);

private:
    bool connectDatabase();
    void disconnectDatabase();

    QSqlDatabase myDatabase;
    OnlineDetail oDetail;
    MyDetail mDetail;
};

#endif // SYNCMILKLOG_H
