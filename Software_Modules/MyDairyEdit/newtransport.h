#ifndef NEWTRANSPORT_H
#define NEWTRANSPORT_H

/*
 * This class is used to
 * register new transportation
 * for milk in dairy
 */

#include <QDialog>
#include "ui_newtransport.h"
#include <QSqlDatabase>
#include "../MyDetail/mydetail.h"
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/onlinedetail.h"
#include "offlinetransport.h"

class NewTransport : public QDialog, public Ui::NewTransport
{
    Q_OBJECT
public:
    NewTransport(QWidget* parent = 0);
    void paintEvent(QPaintEvent *event);
    ~NewTransport();

private slots:
    void cancelPressed();
    void addPressed();
    void showMessage();

private:
    void setWidgets();
    bool connectDatabase();
    void disconnectDatabase();
    void rLoad(int i);

    QSqlDatabase myDatabase;
    MyDetail mDetail;
    GraphicDetail gDetail;
    OnlineDetail oDetail;
    QMovie* loading;
    QLabel* loadingLabel;
    QString transID;
};

#endif // NEWTRANSPORT_H
