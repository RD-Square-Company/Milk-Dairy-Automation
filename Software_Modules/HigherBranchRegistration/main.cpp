#include "higherbranchregistration.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   HigherBranchRegistration *hb = new HigherBranchRegistration;
   hb->show();
    return a.exec();
}
