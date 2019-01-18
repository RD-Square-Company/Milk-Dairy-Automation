#include <QApplication>
#include "customerregistration.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString name= "Producer";
    CustomerRegistration *cr = new CustomerRegistration(name);
    cr->show();

    //OfflineCustRegistration::registerOffline("MP00010001","1","123412341234","Rahul", "", "Dangi", "7568577487", "9993621661",
     //                                       "Jk Lakshmipat University", "Jaipur", "Rajasthan", "302026", "rdsquare144@gmail.com",
     //                                       "1", "RAHUL DANGI", "9789689080", "Bank Account", "HDFC Bank Mandsaur", "HDFC000134", "HDFC Bank On Road, Mandsaur",
     //                                       "", "");
    //return 0;

    return a.exec();
}
