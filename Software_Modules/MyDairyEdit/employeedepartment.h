#ifndef EMPLOYEEDEPARTMENT_H
#define EMPLOYEEDEPARTMENT_H

/*
 *
 * This class is used  to edit
 * information about department of employee
 * some feature of this class is hidden ( assigning multiple department to employee)
 * but will be enabled later
 *
 */

#include "ui_departmentedit.h"
#include <QDialog>
#include <QSqlDatabase>
#include "../MyDetail/mydetail.h"
#include "../MyDetail/onlinedetail.h"
#include "../MyDetail/graphicdetail.h"
#include "../EmployeeEdit/offlineempedit.h"

class EmployeeDepartment : public QDialog, Ui::EmployeeDepartment
{
    Q_OBJECT
public:
    EmployeeDepartment(QWidget *parent=0);
    bool eventFilter(QObject *object, QEvent *event);
    void paintEvent(QPaintEvent *event);
    ~EmployeeDepartment();

private slots:
    void proceedPressed();
    void cancelPressed();
    void showMessage();

private:
    void setWidgets();
    bool connectDatabase();
    void disconnectDatabase();
    void rLoad(int i);

    QSqlDatabase myDatabase;
    QStringList didList;
    QStringList dNameList;
    QString tmpID;
    MyDetail mDetail;
    OnlineDetail oDetail;
    GraphicDetail gDetail;
    QMovie* loading;
    QLabel* loadingLabel;
    QString eID;
};


#endif // EMPLOYEEDEPARTMENT_H
