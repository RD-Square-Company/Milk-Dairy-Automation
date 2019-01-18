#ifndef EREGCOMPLETE_H
#define EREGCOMPLETE_H

#include <QDialog>
#include "ui_eregcomplete.h"

/*
 * It will show the employee name, department and his/her designation
 * and congratulation message to user
 *
 */

class ERegComplete : public QDialog, Ui::ERegComplete
{
    Q_OBJECT
public:
    ERegComplete(QWidget *parent = nullptr);
    void setValue(QString empName, QString deptName, QString designation, QString dairyName);
    void closeEvent(QCloseEvent *);

private slots:
    void okPressed();

signals:
    void okBye();
};

#endif // EREGCOMPLETE_H
