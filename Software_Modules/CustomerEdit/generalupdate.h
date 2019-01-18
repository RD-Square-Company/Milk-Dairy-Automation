#ifndef GENERALUPDATE_H
#define GENERALUPDATE_H


#include "ui_generalupdate.h"
#include <QWidget>
#include <QStringListModel>
#include <QSqlDatabase>
#include <QDataWidgetMapper>
#include "paymentupdate.h"
#include <QSqlQueryModel>
#include <QCompleter>
#include <QMovie>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "offlinecustedit.h"

class GeneralUpdate : public QWidget, public Ui::GeneralUpdate
{
  Q_OBJECT
public:
    GeneralUpdate(QString type, QWidget *parent = 0);
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void updatePressed();
    void showPayment();
    void remakePayment();
    void customerChanged(int row);
    void showMessage();

private:
    void setWidgets();
    void sendMail();
    bool connectDatabase();
    void disconnectDatabase();
    void modelQuery();
    void updateValue();
    void rLoad(int i);
    void editSetting(int i);

    QString type;
    QSqlDatabase myDatabase;
    QSqlQueryModel *model;
    QDataWidgetMapper *mapper;
    QCompleter *completer;
    QStringListModel *stringModel;
    PaymentUpdate *paymentUpdate;
    QMovie *loading;
    QLabel *loadingLabel;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
};

#endif // GENERALUPDATE_H
