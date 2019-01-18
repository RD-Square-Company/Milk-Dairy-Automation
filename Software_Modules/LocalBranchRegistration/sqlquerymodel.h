#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQueryModel>

class SqlQueryModel : public QSqlQueryModel {
    Q_OBJECT
public:
    SqlQueryModel(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;
};

#endif // SQLQUERYMODEL_H
