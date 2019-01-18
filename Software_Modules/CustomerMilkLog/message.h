#ifndef MESSAGE_H
#define MESSAGE_H

#include "ui_message.h"

class Message : public QWidget, public Ui::Message
{
public:
    Message(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void setValue(QString name, QString quantity, QString price, QString amount);
};

#endif // MESSAGE_H
