#include "employeeupdate.h"
#include "offlineempedit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmployeeUpdate *e = new EmployeeUpdate;
    e->show();

    //OfflineEmpEdit::removePayment("2", "15");

    //OfflineEmpEdit::editPayment("2", "16", "TESTING AGAIN", "123456789", "Bank Account", "HDFC BANK",
    //                            "HDFC005454", "Mandsaur", "", "");

    //OfflineEmpEdit::editGeneral("2", "1", "Rahul", "Kumar","Dangi", "7568577487", "","jk lakshmipat university",
      //                          "jaipur", "Rajasthan", "302026", "rdsquare144@gmail.com", "2018-01-01", "1998-12-15",
        //                        "some college no degree", "10000", "A1", "HOD");
    //return 0;
    return a.exec();
}
