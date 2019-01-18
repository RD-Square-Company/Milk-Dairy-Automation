#include "picload.h"
#include <QLabel>
#include <QPixmap>

PicLoad::PicLoad(QObject *parent)
    : QItemDelegate(parent)
{
    //empty now
}

void PicLoad::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLabel *label = qobject_cast<QLabel*> (editor);

    if(label){
        QByteArray byte = index.data(Qt::EditRole).toByteArray();
        QPixmap pixmap;
        if(pixmap.loadFromData(byte)){
            pixmap = pixmap.scaled(30, 30);
            label->setPixmap(pixmap);
        }
    }
}
