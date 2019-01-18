#ifndef ACCEPTREQUEST_H
#define ACCEPTREQUEST_H

#include <QWidget>
#include "ui_acceptrequest.h"
#include "sqlquerymodel.h"
#include <QDataWidgetMapper>
#include <QSqlDatabase>
#include <QMovie>
#include <QList>
#include <QCheckBox>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "../MyDetail/localbranch.h"

class AcceptRequest : public QWidget, public Ui::AcceptRequest
{
    Q_OBJECT
public:
    AcceptRequest(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

private slots:
    void cancelPressed();
    void rSelPressed();
    void rAllPressed();
    void aSelPressed();
    void aAllPressed();
    bool connectDatabase();
    void disconnectDatabase();
    void doTask();
    void refreshPressed();
    void transformAndMessage();

signals:
    void transformMe() ;

private:
    void setWidgets();
    bool saveData();
    void sendMail();
    void rLoad(int i);

    SqlQueryModel *queryModel;
    QDataWidgetMapper *mapper;
    QSqlDatabase myDatabase;
    QMovie *loading;
    QLabel *loadingLabel;
    QLabel *mapLabel;
    QPushButton *refreshButton;
    QList<QCheckBox *> checkList;
    QList<int> statusList;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
};

#endif // ACCEPTREQUEST_H
