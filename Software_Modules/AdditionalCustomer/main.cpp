#include "additionalcustomer.h"
#include "customerofflineentry.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //AdditionalCustomer w("2018-01-01",1);
    //w.show();

    //CustomerOfflineEntry::delTempLog("7568577487", "2018-08-04", "0","2018-08-04 23:42:55");
    QList<QStringList> temp  =  CustomerOfflineEntry::getTempLog();
    for (int i = 0; i< temp.length(); i++){
        qDebug() << temp.at(i) << endl;
    }
    return 0;

    return a.exec();
}
