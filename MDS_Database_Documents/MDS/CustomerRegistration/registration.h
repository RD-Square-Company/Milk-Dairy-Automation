#ifndef REGISTRATION_H
#define REGISTRATION_H

/*
 * Registration Class
 * This class is used to register the basic information of producer and consumer
 *
*/

#include <QDialog>
#include "ui_registration.h"
#include "universalconst.h"

class Registration : public QDialog, public Ui::Registration
{
    Q_OBJECT

public:
    Registration(QString title, QWidget *parent = nullptr);
    void setWidgets(QString title);
    void closeEvent(QCloseEvent *);
    void setDefault();

private slots:
    void nextPressed();
    void cancelPressed();

signals:
    void cancelByCRF();
    void nextByCRF();
private:
    UniversalConst uc;

};

#endif // REGISTRATION_H
