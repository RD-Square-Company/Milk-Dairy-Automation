#ifndef PICLOAD_H
#define PICLOAD_H

#include <QItemDelegate>

class PicLoad : public QItemDelegate
{
    Q_OBJECT
public:
    PicLoad (QObject *parent = 0);
     void setEditorData(QWidget *editor, const QModelIndex &index) const;
};

#endif // PICLOAD_H
