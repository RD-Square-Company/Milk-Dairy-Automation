#ifndef MYSQLQUERY_H
#define MYSQLQUERY_H

#include <QSqlQueryModel>

class MySqlQuery : public QSqlQueryModel {
    Q_OBJECT
public:
    MySqlQuery(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;
};

#endif // MYSQLQUERY_H
