#ifndef DAIRYPICTURE_H
#define DAIRYPICTURE_H

#include "ui_dairypicture.h"
#include <QDialog>
#include <QImage>
#include <QSqlDatabase>
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "../MyDetail/graphicdetail.h"

class DairyPicture : public QDialog, public Ui::DairyPicture
{
    Q_OBJECT
public:
    DairyPicture(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

private slots:
    void p1Pressed();
    void p2Pressed();
    void p3Pressed();
    void p4Pressed();
    void p5Pressed();
    void cancelPressed();
    void updatePressed();
    void showMessage();

private:
    void updateOffline();
    bool connectDatabase();
    void disconnectDatabase();
    void setWidgets();
    void rLoad(int i);

    QImage pc[5];
    int pcId[5];
    QSqlDatabase myDatabase;
    MyDetail mDetail;
    OnlineDetail oDetail;
    GraphicDetail gDetail;
    QMovie* loading;
    QLabel* loadingLabel;
};

#endif // DAIRYPICTURE_H
