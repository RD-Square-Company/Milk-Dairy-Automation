#ifndef PICLOADINGDELEGATE_H
#define PICLOADINGDELEGATE_H

#include <QItemDelegate>

class PicLoadingDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    PicLoadingDelegate (QObject *parent = nullptr);
     void setEditorData(QWidget *editor, const QModelIndex &index) const;
};

#endif // PICLOADINGDELEGATE_H
