#ifndef TRANSPORTEDIT_H
#define TRANSPORTEDIT_H

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
#include "ui_transport.h"
#include "newtransport.h"
#include "offlinetransport.h"

class TransportEdit : public QDialog, public Ui::TransportEdit
{
  Q_OBJECT
public:
    TransportEdit(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    ~TransportEdit();

private slots:
    void updatePressed();
    void transportChanged(int row);
    void showMessage();
    void showID();
    void registerNew();
    void doSearching();
    void cancelPressed();

private:
    void setWidgets();
    bool connectDatabase();
    void disconnectDatabase();
    void modelQuery();
    void updateValue();
    void rLoad(int i);
    void editSetting(int i);

    QSqlDatabase myDatabase;
    QSqlQueryModel *model;
    QDataWidgetMapper *mapper;
    QCompleter *completer;
    QStringListModel *stringModel;
    QMovie *loading;
    QLabel *loadingLabel;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
    NewTransport *newTransport;
};

#endif // TRANSPORTEDIT_H
