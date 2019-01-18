#ifndef PRODUCTREGISTRATION_H
#define PRODUCTREGISTRATION_H

#include <QDialog>
#include <QSqlDatabase>
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "../MyDetail/graphicdetail.h"
#include "ui_productregistration.h"

class ProductRegistration : public QDialog, Ui::ProductRegistration
{
    Q_OBJECT
public:
    ProductRegistration(QWidget *parent = 0);
    ~ProductRegistration();
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void registerPressed();
    void cancelPressed();
    void productTypeChanged(int ind);
    void WeightTypeChanged(int ind);
    void packingChange(int ind);
    void generateID();
    void setProductID();
    void showSpecify(bool checked);
    void gstChanged(int ind);
    void rLoad(int i);
    void showMessage();

private:
    void setWidgets();
    void setDefault();
    bool connectDatabase();
    void disconnectDatabase();
    bool saveData();

    MyDetail mDetail;
    GraphicDetail gDetail;
    OnlineDetail oDetail;
    QSqlDatabase myDatabase;
    QMovie *loading;
    QLabel *loadingLabel;
};

#endif // PRODUCTREGISTRATION_H
