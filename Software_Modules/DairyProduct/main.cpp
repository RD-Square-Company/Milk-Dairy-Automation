#include "productdetail.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProductDetail w;
    w.show();

    return a.exec();
}
