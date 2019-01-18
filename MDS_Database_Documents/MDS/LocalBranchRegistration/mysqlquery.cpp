#include "mysqlquery.h"
#include <QPixmap>
MySqlQuery::MySqlQuery(QObject *parent)
    : QSqlQueryModel(parent)
{
    //empty now
}

QVariant MySqlQuery::data(const QModelIndex &item, int role) const
{
    QVariant variant = QSqlQueryModel::data(item, role);

    if((variant.isValid()) && (item.column() == 0) && (role == Qt::DecorationRole)){
        QPixmap pixmap;
        pixmap.loadFromData(variant.toByteArray());
        return pixmap;
    }
    return QSqlQueryModel::data(item, role);
}
