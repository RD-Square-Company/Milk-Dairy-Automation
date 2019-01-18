#include "localbranchregistration.h"
#include <QMessageBox>
#include <QDebug>

LocalBranchRegistration::LocalBranchRegistration(QWidget *parent)
    : QWidget(parent)
{
    gridLayout = new QGridLayout(this);

    //select any one window to be open
    selectOption();
}

void LocalBranchRegistration::selectOption()
{
    int status = QMessageBox::question(this, tr("Select an option! - %1").arg(qApp->applicationName()),
                          tr("What you want to do ?"),
                          tr("Send Proposal to other dairies"), tr("Accept request from other dairies"), QString(), 0, 1);

    if(status == 0){
        sendP = new SendProposal(this);
        gridLayout->addWidget(sendP, 0, 0);
        setLayout(gridLayout);
    } else {
        acceptReq = new AcceptRequest(this);
        gridLayout->addWidget(acceptReq, 0, 0);
        setLayout(gridLayout);

        //connections
        connect(acceptReq, SIGNAL(transformMe()),
                this, SLOT(makeNew()));
        //CONNECTION END
    }
}

void LocalBranchRegistration::makeNew()
{
    delete acceptReq;
    acceptReq = new AcceptRequest(this);
    delete gridLayout;
    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(acceptReq, 0, 0);
    setLayout(gridLayout);

    //connections
    connect(acceptReq, SIGNAL(transformMe()),
            this, SLOT(makeNew()));
    //CONNECTION END
}
