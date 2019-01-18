#ifndef SENDREQUEST_H
#define SENDREQUEST_H

#include  "ui_sendproposal.h"
#include <QWidget>
#include <QDataWidgetMapper>
#include "../LocalBranchRegistration/mysqlquery.h"
#include <QSqlDatabase>
#include <QMovie>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"

class SendRequest : public QWidget, Ui::SendProposal
{
    Q_OBJECT
public:
    SendRequest(QWidget *parent = 0);
    void rLoad(int i);
    void paintEvent(QPaintEvent *event);
private:
    bool connectDatabase();
    void disconnectDatabase();
    void setWidgets();
    void sendMail();

    QString toDairy;
    QString dairyEmail;

private slots:
    void goPressed();
    void closeIt();
    void sendPressed();
    void showMessage();

private:
    MySqlQuery *queryModel;
    QDataWidgetMapper *mapper;
    QSqlDatabase myDatabase;
    QMovie *loading;
    QLabel *loadingLabel;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
};

#endif // SENDREQUEST_H
