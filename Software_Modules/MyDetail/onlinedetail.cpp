#include "onlinedetail.h"
#include <QMessageBox>

OnlineDetail::OnlineDetail()
{
    //setting file
    file.setFileName("/media/rd_square/Important/Qt projects/MyDetail/detailDoc/onlinedetail.dat");

    //reading data from file
    readData();
}

void OnlineDetail::setDatabaseInfo(QString hn, QString un, QString up, QString db)
{
    //setting database information variables
    hostName = hn;
    userName = un;
    userPass = up;
    database = db;
}

void OnlineDetail::setemailInfo(QString he, QString hep)
{
    //setting email gateway information
    hostEmail = he;
    hostEmailPass = hep;
}

QString OnlineDetail::getHostName() const
{
    return hostName;
}

QString OnlineDetail::getUserName() const
{
    return userName;
}

QString OnlineDetail::getUserPass() const
{
    return userPass;
}

QString OnlineDetail::getDatabase() const
{
    return database;
}

QString OnlineDetail::getHostEmail() const
{
    return hostEmail;
}

QString OnlineDetail::getHostEmailPass() const
{
    return hostEmailPass;
}

QDataStream& operator <<(QDataStream& ds, const OnlineDetail& od)
{
    ds << od.hostName << od.userName << od.userPass << od.database << od.hostEmail << od.hostEmailPass;
    return ds;
}

QDataStream& operator >>(QDataStream& ds, OnlineDetail& od)
{
    QString temp;
    ds >> temp; od.hostName = temp;
    ds >> temp; od.userName  = temp;
    ds >> temp; od.userPass = temp;
    ds >> temp; od.database = temp;
    ds >> temp; od.hostEmail = temp;
    ds >> temp; od.hostEmailPass = temp;
    return ds;
}

OnlineDetail& OnlineDetail::operator =(OnlineDetail& od)
{
    hostName = od.hostName;
    userName = od.userName;
    userPass = od.userPass;
    database = od.database;
    hostEmail = od.hostEmail;
    hostEmailPass = od.hostEmailPass;
    return od;
}

void OnlineDetail::saveData()
{
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(NULL,
                              QObject::tr("Critical Internal File Error!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "There is some error in opening file. Your application may misbehave due this. Please restart or"
                                          " the application</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_5_5);
    ds << *this;
    file.close();
}

void OnlineDetail::readData()
{
    if(!file.open(QIODevice::ReadWrite)){
        QMessageBox::critical(NULL,
                              QObject::tr("Critical Internal File Error!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "There is some error in opening file. Your application may misbehave due this. Please restart or"
                                          " the application</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_5_5);
    ds >> *this;
    file.close();
}
