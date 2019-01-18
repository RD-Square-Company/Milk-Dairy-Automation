#ifndef LOCALBRANCHREGISTRATION_H
#define LOCALBRANCHREGISTRATION_H

#include "acceptrequest.h"
#include "sendproposal.h"
#include <QWidget>
#include <QGridLayout>

class LocalBranchRegistration : public QWidget
{
    Q_OBJECT
public:
    LocalBranchRegistration(QWidget *parent = 0);

private slots:
    void makeNew();

private:
    void selectOption();

    SendProposal *sendP;
    AcceptRequest *acceptReq;
    QGridLayout *gridLayout;
};

#endif // LOCALBRANCHREGISTRATION_H
