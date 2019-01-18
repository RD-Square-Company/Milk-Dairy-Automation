#ifndef ONLINEDETAIL_H
#define ONLINEDETAIL_H

/*
 * This class is used to save
 * online database or message sending email
 * id and host details. It can be edited from settigs
 * in mds.
 *
 */

#include <string>
#include <QFile>
#include <QDataStream>

class OnlineDetail
{
public:
    OnlineDetail();
    void setDatabaseInfo(QString hn, QString un, QString up, QString db);
    void setemailInfo(QString he, QString hep);

    QString getHostName() const;
    QString getUserName() const;
    QString getUserPass() const;
    QString getDatabase() const;

    QString getHostEmail() const;
    QString getHostEmailPass() const;

    //operator overloading
    //operator overloading
    friend QDataStream& operator <<(QDataStream& ds, const OnlineDetail& md);
    friend QDataStream& operator >>(QDataStream& ds, OnlineDetail& md);
    OnlineDetail& operator =(OnlineDetail& md);

private:
    void saveData();
    void readData();

    //database information variables
    QString hostName;
    QString userName;
    QString userPass;
    QString database;

    //email gateway information
    QString hostEmail;
    QString hostEmailPass;

    QFile file;
};

#endif // ONLINEDETAIL_H
