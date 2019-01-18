#include "higherbranchregistration.h"
#include <QMessageBox>
#include <QDebug>

HigherBranchRegistration::HigherBranchRegistration(QWidget *parent)
    : QWidget(parent)
{
    gridLayout = new QGridLayout(this);

    //select any one window to be open
    selectOption();
}

void HigherBranchRegistration::selectOption()
{
    int status = QMessageBox::question(this, tr("Select an option! - %1").arg(qApp->applicationName()),
                          tr("What you want to do ?"),
                          tr("Send Request to other dairies"), tr("Accept proposal from other dairies"), QString(), 0, 1);

    if(status == 0){
        sendP = new SendRequest(this);
        gridLayout->addWidget(sendP, 0, 0);
        setLayout(gridLayout);
    } else {
        acceptReq = new AcceptProposal(this);
        gridLayout->addWidget(acceptReq, 0, 0);
        setLayout(gridLayout);

        //connections
        connect(acceptReq, SIGNAL(transformMe()),
                this, SLOT(makeNew()));
        //CONNECTION END
    }
}

void HigherBranchRegistration::makeNew()
{
    delete acceptReq;
    acceptReq = new AcceptProposal(this);
    delete gridLayout;
    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(acceptReq, 0, 0);
    setLayout(gridLayout);

    //connections
    connect(acceptReq, SIGNAL(transformMe()),
            this, SLOT(makeNew()));
    //CONNECTION END
}
