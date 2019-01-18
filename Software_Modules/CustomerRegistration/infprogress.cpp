#include "infprogress.h"
#include <QVBoxLayout>
#include <QTimer>
InfProgress::InfProgress(QString text, QWidget *parent)
    : QDialog(parent)
{
    timeID = 0;
    this->text = text;
    QVBoxLayout *layout = new QVBoxLayout(this);
    label = new QLabel(tr("<html><center><p><font color=\"red\" size = \"5\"><b>%1</b></font></p></center></html>").arg(text));
    progress = new QProgressBar;
    progress->setVisible(true);
    progress->setMaximum(0);
    progress->setMinimum(0);
    progress->setTextVisible(true);
    progress->setFormat(tr("%1").arg(text));
    progress->setAlignment(Qt::AlignCenter);
    progress->setOrientation(Qt::Horizontal);
    layout->addWidget(label);
    layout->addWidget(progress);
    setLayout(layout);


    QTimer *timer = new QTimer(this);

    //establishing connections.....
    connect(timer , SIGNAL(timeout()), this, SLOT(changeColor()));
    setFixedSize(300, 70);

    timer->start(400);
}

void InfProgress::changeColor()
{
    if(timeID==0) {
        QString color = "red";
        label->setText(tr("<html><center><p><font color=\"%1\" size = \"5\"><b>%2.</b></font></p></center></html>").arg(color).arg(this->text));
        ++timeID;
    } else if(timeID == 1){
        QString color = "green";
        label->setText(tr("<html><center><p><font color=\"%1\" size = \"5\"><b>%2..</b></font></p></center></html>").arg(color).arg(this->text));
        ++timeID;
    } else if (timeID == 2){
        QString color = "red";
         label->setText(tr("<html><center><p><font color=\"%1\" size = \"5\"><b>%2...</b></font></p></center></html>").arg(color).arg(this->text));
        ++timeID;
    } else {
        QString color = "green";
         label->setText(tr("<html><center><p><font color=\"%1\" size = \"5\"><b>%2....</b></font></p></center></html>").arg(color).arg(this->text));
        timeID = 0;
    }
}

void InfProgress::setText(QString text)
{
    this->text = text;
    timeID = 0;
    label->setText(tr("<html><center><p><font color=\"red\" size = \"5\"><b>%1</b></font></p></center></html>").arg(text));
}

void InfProgress::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
