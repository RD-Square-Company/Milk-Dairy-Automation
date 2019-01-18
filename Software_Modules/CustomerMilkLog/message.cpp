#include "message.h"
#include <QPainter>
#include <QColor>
#include <QRect>
#include <QBrush>

Message::Message(QWidget *parent):
    QWidget(parent)
{
    setupUi(this);
}

void Message::setValue(QString name, QString quantity, QString price, QString amount)
{
    nameEdit->setText(name);
    quantityEdit->setText(quantity);
    priceEdit->setText(price);
    amountEdi->setText(amount);
}

void Message::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter p(this);
    p.setPen(Qt::black);
    p.setRenderHint(QPainter::Antialiasing, true);
    QColor col(150,146,142);
    QBrush brush(Qt::black);
    p.setBrush(brush);

    QRect leftRect(0,0,10,this->rect().height());
    QRect rightRect(this->rect().width()-10,0,10,this->rect().height());
    QRect upperRect(0,0,this->rect().width(), 10);
    QRect lowerRect(0,this->rect().height()-10,this->rect().width(),10);

    p.drawRect(leftRect);
    p.drawRect(rightRect);
    p.drawRect(upperRect);
    p.drawRect(lowerRect);

    QColor color(Qt::white);
    QBrush brush2(color);
    p.setBrush(brush2);
    QRect windowRect (10,10,this->rect().width()-20, this->rect().height()-20);
    p.drawRect(windowRect);
}
