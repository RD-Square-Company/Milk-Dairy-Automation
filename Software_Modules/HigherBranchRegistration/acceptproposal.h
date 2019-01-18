#ifndef ACCEPTPROPOSAL_H
#define ACCEPTPROPOSAL_H

#include <QWidget>
#include "ui_acceptproposal.h"
#include "../LocalBranchRegistration/sqlquerymodel.h"
#include <QDataWidgetMapper>
#include <QSqlDatabase>
#include <QMovie>
#include <QList>
#include <QCheckBox>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "../MyDetail/higherbranch.h"

class AcceptProposal : public QWidget, public Ui::AcceptProposal
{
    Q_OBJECT
public:
    AcceptProposal(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

private slots:
    void cancelPressed();
    void rAllPressed();
    void aSelPressed();
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
    OnlineDetail oDetail;
    QMovie *loading;
    QLabel *loadingLabel;
    QLabel *mapLabel;
    QPushButton *refreshButton;
    QList<QCheckBox *> checkList;
    QList<int> statusList;
    GraphicDetail gDetail;
    MyDetail mDetail;
};

#endif // ACCEPTPROPOSAL_H
