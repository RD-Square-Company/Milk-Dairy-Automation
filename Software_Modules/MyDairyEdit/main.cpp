#include "mydairy.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  MyDairy *du = new MyDairy();
  du->show();

  return a.exec();
}
