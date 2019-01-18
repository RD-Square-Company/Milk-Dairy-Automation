#ifndef OFFLINETRANSPORT_H
#define OFFLINETRANSPORT_H

#include <QtXml>
#include <QDomNodeList>
#include <QFile>

/*
 * This class is used to save offline detail of
 * registered transportaion vehical.
 * It will be further used to show this information offline
 * to user
 *
 */

class OfflineTransport
{
public:
    OfflineTransport();
    static void registerOffline(QString tID, QString fName, QString mName, QString lName,
                                QString pc, QString sc, QString lic, QString veh);
    static void editOffline(QString tID, QString fName, QString mName, QString lName,
                                QString pc, QString sc, QString lic, QString veh);
private:
    static bool readData();
    static bool saveData();

    static QDomDocument doc;
};

#endif // OFFLINETRANSPORT_H
