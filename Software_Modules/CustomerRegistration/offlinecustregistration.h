#ifndef OFFLINECUSTREGISTRATION_H
#define OFFLINECUSTREGISTRATION_H

#include <QtXml>
#include <QDomNodeList>
#include <QFile>

/*
 * This class is used to save offline detail of
 * registered customers.
 * It will be further used to show this information offline
 * to user
 *
 */

class OfflineCustRegistration
{
public:
    OfflineCustRegistration();
    static void registerOffline(QString cID, QString isApp,QString adhaar, QString fName, QString mName, QString lName,
                                QString pC, QString sC, QString street, QString city, QString state, QString pin,
                                QString email, QString bid, QString noa, QString accNo, QString actype, QString bName, QString ifsc,
                                QString branch, QString cvv, QString expDate);
    static QString searchCustomer(QString cID);
private:
    static bool readData();
    static bool saveData();

    static QDomDocument doc;
};

#endif // OFFLINECUSTREGISTRATION_H
