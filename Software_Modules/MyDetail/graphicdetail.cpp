#include "graphicdetail.h"
#include <QLabel>
#include <QDebug>

GraphicDetail::GraphicDetail()
{
    //setting stylesheets
    normalStylesheet = "QLineEdit {"
                       "background-color: white;"
                       "background-repeat: no-repeat;"
                       "}";
    errorStylesheet = "QLineEdit {"
                      "background-color: yellow;"
                      "background-repeat: no-repeat;"
                      "}" ;
}

QMovie* GraphicDetail::getLoadAnimation() const
{
    QMovie* loadingAnimation = new QMovie(":/media/rd_square/Important/Qt projects/MyDetail/detailDoc/loading.gif");
    loadingAnimation->setScaledSize(QSize(150,150));
    loadingAnimation->start();
    return loadingAnimation;
}

QString GraphicDetail::getNormalStylesheet() const
{
    return normalStylesheet;
}

QString GraphicDetail::getErrorStylesheet() const
{
    return errorStylesheet;
}
