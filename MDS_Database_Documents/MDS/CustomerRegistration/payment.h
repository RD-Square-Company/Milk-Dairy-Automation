#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDialog>
#include "ui_payment.h"
#include <QMovie>
#include "universalconst.h"

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
     Payment(QWidget *parent = nullptr);
     void setWidgets();
     void closeEvent(QCloseEvent *);
     void rLoad(int i);
     void setDefault();
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
     UniversalConst uc;
};

#endif // PAYMENT_H
