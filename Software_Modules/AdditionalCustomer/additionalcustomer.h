#ifndef ADDITIONALCUSTOMER_H
#define ADDITIONALCUSTOMER_H

#include "ui_additionalcustomer.h"
#include <QSqlDatabase>
#include "../MyDetail/mydetail.h"
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/onlinedetail.h"
#include <QDate>

class AdditionalCustomer : public QWidget, public Ui::AdditionalCustomer
{
    Q_OBJECT
public:
    AdditionalCustomer(QString date, int shift, QWidget *parent=0);
    void paintEvent(QPaintEvent *event);

public slots:
    void gotMilkPrice();
    void dateChanged(QDate date);
    void shiftChanged(int shift);

private slots:
    void billChecked(bool clicked);
    void printBill(bool clicked);
    void submitPressed();
    void changingText();
    void nameTextChanged();

signals:
    void requireMilkPrice(int index);
    void hideThis();

private:
    void setWidgets();
    bool saveOfflineData();

    QSqlDatabase myDatabase;
    MyDetail mDetail;
    OnlineDetail oDetail;
    GraphicDetail gDetail;
    QString date;
    QString shift;
    bool gotPrice;
    double price;
};

#endif // ADDITIONALCUSTOMER_H
