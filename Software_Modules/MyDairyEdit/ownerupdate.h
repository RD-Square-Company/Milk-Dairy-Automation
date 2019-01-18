#ifndef OWNERUPDATE_H
#define OWNERUPDATE_H
#include "ui_ownerupdate.h"
#include <QDialog>
#include <QSqlDatabase>
#include <QImage>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"

/*
 * This class is basically give functionality of updating dairy secretary information to server
 * It also maintain offline record of owner information as well as online record of owner information
 *
 */
class OwnerUpdate : public QDialog, public Ui::OwnerUpdate
{
    Q_OBJECT
public:
    OwnerUpdate(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

private slots:
    void updatePic();
    void updatePressed();
    void cancelPressed();
    void showMessage();

private:
    bool updateData();
    void updateOffline();
    bool connectDatabase();
    void disconnectDatabase();
    void setWidgets();
    void rLoad(int i);

    QSqlDatabase myDatabase;
    QImage profilePic;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
    QMovie* loading;
    QLabel* loadingLabel;
};

#endif // OWNERUPDATE_H
