#include "graphicdetail.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QMovie>
#include <QPixmap>
#include "mydetail.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GraphicDetail lb;

    QLabel* label = new QLabel();
    QMovie *movie = new QMovie();
    movie = lb.getLoadAnimation();
    label->setMovie(movie);
    //label->setMovie(lb.getLoadAnimation());
    label->setFixedSize(200,200);
    label->show();

    return a.exec();
}
