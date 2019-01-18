#include "sqlquerymodel.h"
#include <QPixmap>
SqlQueryModel::SqlQueryModel(QObject *parent)
    : QSqlQueryModel(parent)
{
    //empty now
}

QVariant SqlQueryModel::data(const QModelIndex &item, int role) const
{
    QVariant variant = QSqlQueryModel::data(item, role);

    if((variant.isValid()) && (item.column() == 0) && (role == Qt::DecorationRole)){
        QPixmap pixmap;
        pixmap.loadFromData(variant.toByteArray());
        return pixmap;
    }
    return QSqlQueryModel::data(item, role);
}
