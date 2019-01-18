#include "picloadingdelegate.h"
#include <QLabel>
#include <QPixmap>

PicLoadingDelegate::PicLoadingDelegate(QObject *parent)
    : QItemDelegate(parent)
{
    //empty now
}

void PicLoadingDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLabel *label = qobject_cast<QLabel*> (editor);

    if(label){
        QByteArray byte = index.data(Qt::EditRole).toByteArray();
        QPixmap pixmap;
        if(pixmap.loadFromData(byte)){
            label->setPixmap(pixmap);
        }
    }
}
