#include "mydairyedit.h"
#include "ui_mydairyedit.h"

MyDairyEdit::MyDairyEdit(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MyDairyEdit)
{
  ui->setupUi(this);
}

MyDairyEdit::~MyDairyEdit()
{
  delete ui;
}
