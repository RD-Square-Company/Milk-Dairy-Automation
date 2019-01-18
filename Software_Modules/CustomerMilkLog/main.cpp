#include "customermilklog.h"
#include "offlinecustomerlog.h"
#include <QApplication>
#include "syncmilklog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomerMilkLog w;
    w.show();
    //return 0;
    return a.exec();
}
