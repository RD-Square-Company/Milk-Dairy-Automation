#ifndef NEWDEPARTMENT_H
#define NEWDEPARTMENT_H

/*
 *
 * This class used to add new department to the
 * milk diary.
 *
 */

#include "ui_newdepartment.h"
#include <QDialog>
#include <QSqlDatabase>
#include <QStringList>
#include <QList>
#include "../MyDetail/graphicdetail.h"
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "offlinedepregistration.h"
#include "../EmployeeEdit/offlineempedit.h"

class NewDepartment : public QDialog, public Ui::NewDepartment
{
    Q_OBJECT
public:
    NewDepartment(QWidget* parent=0);
    void paintEvent(QPaintEvent *event);
    ~NewDepartment();

private slots:
    void editPressed();
    void addPressed();
    void cancelPressed();
    void updateSalary(int ind);
    void showMessage();
    void rLoad(int i);

private:
    void setWidgets();
    bool connectDatabase();
    void disconnectDatabase();

    QSqlDatabase myDatabase;
    QStringList mangNames;
    QStringList salaryList;
    QStringList mangIDs;
    QStringList mangID;
    GraphicDetail gDetail;
    MyDetail mDetail;
    OnlineDetail oDetail;
    QMovie *loading;
    QLabel *loadingLabel;
    QString depID;
};

#endif // NEWDEPARTMENT_H
