//#include "paymentupdate.h"
#include "generalupdate.h"
#include "offlinecustedit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GeneralUpdate *w = new GeneralUpdate("Consumer");
    w->show();

    //OfflineCustEdit::editGeneral("MP00010001","N","Rahul", "", "Dangi",
      //                           "9993621661", "", "sagor", "Sitamau", "Madhya Pradesh",
      //                           "302026","rahuldangi144@gmail.com");
    //PaymentUpdate *p = new PaymentUpdate("Producer", "MP00010001", "rdsquare144@gmail.com");
    //p->show();

    //OfflineCustEdit::editPayment("MP00010001", "6", "TEST DANGI", "1234567890","Bank Account",
     //                            "HDFC BANK", "HDFC000134", "petrol pumb Mandsaur", "", "");

    //OfflineCustEdit::removePayment("MP00010001", "5");
    //return 0;
    return a.exec();
}
