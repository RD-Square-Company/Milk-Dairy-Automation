#ifndef MYDAIRYEDIT_H
#define MYDAIRYEDIT_H

#include <QMainWindow>

namespace Ui {
  class MyDairyEdit;
}

class MyDairyEdit : public QMainWindow
{
  Q_OBJECT

public:
  explicit MyDairyEdit(QWidget *parent = 0);
  ~MyDairyEdit();

private:
  Ui::MyDairyEdit *ui;
};

#endif // MYDAIRYEDIT_H
