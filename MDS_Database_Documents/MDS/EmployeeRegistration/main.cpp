#include "employeeregistration.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    EmployeeRegistration *er = new EmployeeRegistration;
    er->show();

    return a.exec();
}
