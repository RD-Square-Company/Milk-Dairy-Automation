#ifndef EREGISTRATION_H
#define EREGISTRATION_H
#include "ui_eregistration.h"

#include <QDialog>
#include "../CustomerRegistration/universalconst.h"
#include  <QStringList>

/*
 * This is class for registration of the employees
 * of the milk dairy
 *
 */

class ERegistration : public QDialog, public Ui::ERegistration
{
    Q_OBJECT
public:
    ERegistration(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *);
    void setDefault();

private slots:
   void showPressed();
   void cancelPressed();
   void prevPressed();
   void nextPressed();

signals:
   void nextByER();
   void closeByER();
   void setConnection();

public slots:
   void getDeptValues(QStringList depNames);

private:
    void setWidgets();
    bool checkGeneralInfo();
    bool checkOfficeInfo();
    void showOfficeBox();
    UniversalConst uc;
    int setDept;
};

#endif // EREGISTRATION_H
