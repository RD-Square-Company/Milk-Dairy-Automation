#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDialog>
#include "ui_payment.h"
#include <QMovie>
#include "../MyDetail/graphicdetail.h"

/*
 *
 * payment section class
 * to handle different types of payment
 *
*/

class Payment : public QDialog, public Ui::Payment
{
    Q_OBJECT
public:
     Payment(QWidget *parent = 0);
     void setWidgets();
     void closeEvent(QCloseEvent *);
     void rLoad(int i);
     void setDefault();
     void paintEvent(QPaintEvent *event);
signals:
     void regByPay();
     void prevByPay();
     void quitByPay();
private slots:
     void regPressed();
     void prevPressed();
     void exitPressed();
     void accountTypeChanged(int type);
private:
     QMovie *loading;
     QLabel *loadingLabel;
     GraphicDetail gDetail;
};

#endif // PAYMENT_H
