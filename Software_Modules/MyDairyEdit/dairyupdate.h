#ifndef DAIRYUPDATE_H
#define DAIRYUPDATE_H
#include "ui_dairyupdate.h"
#include "dairypicture.h"
#include <QDialog>
#include <QSqlDatabase>
#include <QMovie>
#include <QLabel>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"

/*
 * This class is used to update general information about dairy
 *
 */

class DairyUpdate : public QDialog, public Ui::DiaryUpdate
{
    Q_OBJECT
public:
    DairyUpdate(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

private slots:
    void cancelPressed();
    void updatePressed();
    void logoUpdatePressed();
    void upPicturesPressed();
    void showMessage();

private:
    void rLoad(int i);
    void setWidgets();
    bool connectDatabase();
    void disconnectDatabase();
    bool uploadData();
    void saveOffline();

    DairyPicture *dairyPic;
    QSqlDatabase myDatabase;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
    QMovie* loading;
    QLabel* loadingLabel;
};

#endif // DAIRYUPDATE_H
