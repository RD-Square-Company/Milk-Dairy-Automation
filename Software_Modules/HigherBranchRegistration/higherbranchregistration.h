#ifndef HIGHERBRANCHREGISTRATION_H
#define HIGHERBRANCHREGISTRATION_H

#include "acceptproposal.h"
#include "sendrequest.h"
#include <QWidget>
#include <QGridLayout>

class HigherBranchRegistration : public QWidget
{
    Q_OBJECT
public:
    HigherBranchRegistration(QWidget *parent = 0);

private slots:
    void makeNew();

private:
    void selectOption();

    SendRequest *sendP;
    AcceptProposal *acceptReq;
    QGridLayout *gridLayout;
};

#endif // HIGHERBRANCHREGISTRATION_H
