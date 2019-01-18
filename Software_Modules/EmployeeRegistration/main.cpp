#include "employeeregistration.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    EmployeeRegistration *er = new EmployeeRegistration;
    er->show();

    //OfflineEmpRegistration::registerOffline("1","1","123412341234","Rahul", "", "Dangi", "7568577487", "9993621661",
     //                                       "Jk Lakshmipat University", "Jaipur", "Rajasthan", "302026", "rdsquare144@gmail.com","2018-01-01", "2000-01-01", "till 12th", "5000",
      ////                                       "D1", "Manager",
        //                                    "1", "RAHUL DANGI", "9789689080", "Bank Account", "HDFC Bank Mandsaur", "HDFC000134", "HDFC Bank On Road, Mandsaur",
        //                                    "", "");

    //return 0;

    return a.exec();
}
