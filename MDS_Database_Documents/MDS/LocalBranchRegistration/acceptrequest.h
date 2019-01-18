#ifndef ACCEPTREQUEST_H
#define ACCEPTREQUEST_H

#include <QDialog>
#include "ui_acceptrequest.h"
#include "sqlquerymodel.h"
#include <QDataWidgetMapper>
#include "../CustomerRegistration/universalconst.h"
#include <QSqlDatabase>
#include <QMovie>

class AcceptRequest : public QDialog, public Ui::AcceptRequest
{
    Q_OBJECT
public:
    AcceptRequest(QWidget *parent = nullptr);

private slots:
    void cancelPressed();
    void rSelPressed();
    void rAllPressed();
    void aSelPressed();
    void aAllPressed();
    bool connectDatabase();
    void disconnectDatabase();
    void doTask();

private:
    void setWidgets();

    SqlQueryModel *queryModel;
    QDataWidgetMapper *mapper;
    QSqlDatabase myDatabase;
    UniversalConst uc;
    QMovie *loading;
    QLabel *loadingLabel;
    QLabel *mapLabel;
    QPushButton *refreshButton;
};

#endif // ACCEPTREQUEST_H
