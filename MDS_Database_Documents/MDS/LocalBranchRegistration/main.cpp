#include "sendproposal.h"
#include "acceptrequest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SendProposal *w = new SendProposal;
    w->show();

    AcceptRequest  *h = new AcceptRequest;
    h->show();

    return a.exec();
}
