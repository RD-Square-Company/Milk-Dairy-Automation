#include "localbranchregistration.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LocalBranchRegistration *l = new LocalBranchRegistration;
    l->show();
    return a.exec();
}
