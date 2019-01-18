#ifndef GRAPHICDETAIL_H
#define GRAPHICDETAIL_H

/*
 * This class is used to seve
 * graphic details of mds
 * It will save animation, pictures, stylesheets
 * and other graphical items
 *
 */

#include <QString>
#include <QMovie>
#include <QDataStream>

class GraphicDetail
{
public:
    GraphicDetail();
    QMovie* getLoadAnimation() const;
    QString getNormalStylesheet() const;
    QString getErrorStylesheet() const;
private:
    QString normalStylesheet;
    QString errorStylesheet;
};

#endif // GRAPHICDETAIL_H
