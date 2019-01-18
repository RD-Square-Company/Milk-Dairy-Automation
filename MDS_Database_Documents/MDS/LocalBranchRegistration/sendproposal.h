#ifndef SENDPROPOSAL_H
#define SENDPROPOSAL_H
#include  "ui_sendproposal.h"
#include <QWidget>
#include <QDataWidgetMapper>
#include "mysqlquery.h"
#include <QSqlDatabase>
#include <QMovie>
#include "../CustomerRegistration/universalconst.h"

class SendProposal : public QWidget, Ui::SendProposal
{
    Q_OBJECT
public:
    SendProposal(QWidget *parent = nullptr);
    void rLoad(int i);
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
    UniversalConst uc;
    QMovie *loading;
    QLabel *loadingLabel;
};

#endif // SENDPROPOSAL_H
