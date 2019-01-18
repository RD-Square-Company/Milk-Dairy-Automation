#include <QApplication>
#include "customerregistration.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString name= "Producer";
    CustomerRegistration *cr = new CustomerRegistration(name);
    cr->show();
    return a.exec();
}
