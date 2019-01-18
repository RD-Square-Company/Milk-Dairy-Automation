#ifndef NEWHEAD_H
#define NEWHEAD_H

#include <QDialog>
#include <QSqlDatabase>
#include "ui_newhead.h"
#include <QStringList>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "../EmployeeEdit/offlineempedit.h"
#include "offlinedepregistration.h"

class NewHead : public QDialog, public Ui::NewHead
{
    Q_OBJECT
public:
    NewHead(QWidget *parent=0);
    void paintEvent(QPaintEvent *event);
    ~NewHead();

private slots:
    void editPressed();
    void proceedPressed();
    void cancelPressed();
    void salaryChanged(int ind);
    void depChanged(int ind);
    void showMessage();

private:
    void setWidgets();
    bool connectDatabase();
    void disconnectDatabase();
    void rLoad(int i);

    QSqlDatabase myDatabase;
    QStringList didList;
    QStringList dnameList;
    QStringList mangNames;
    QStringList salaryList;
    QStringList mangID;
    QStringList currentMangIDs;
    QStringList currSalaryList;
    QStringList currMangNames;
    QStringList currQList;
    QStringList mangIDs;
    QStringList qList;
    QString headID;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
    QMovie* loading;
    QLabel* loadingLabel;
};

#endif // NEWHEAD_H
