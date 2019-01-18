#ifndef PRODUCTDETAIL_H
#define PRODUCTDETAIL_H

#include <QWidget>
#include <QStringListModel>
#include <QSqlDatabase>
#include <QDataWidgetMapper>
#include <QSqlQueryModel>
#include <QCompleter>
#include <QMovie>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "ui_productdetail.h"
#include "productregistration.h"

class ProductDetail : public QWidget, public Ui::ProductDetail
{
  Q_OBJECT
public:
    ProductDetail(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

private slots:
    void updatePressed();
    void newPressed();
    void paPressed();
    void productChanged(int row);
    void srdPressed();
    void showMessage();
    void searchProduct();
    void updateDetails();

private:
    void setWidgets();
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
    QMovie *loading;
    QLabel *loadingLabel;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
    ProductRegistration *productRegistration;
};

#endif // PRODUCTDETAIL_H
