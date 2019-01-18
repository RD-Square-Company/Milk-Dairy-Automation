#ifndef OFFLINEEMPREGISTRATION_H
#define OFFLINEEMPREGISTRATION_H

#include <QtXml>
#include <QDomNodeList>
#include <QFile>

/*
 * This class is used to save offline detail of
 * registered employees.
 * It will be further used to show this information offline
 * to user
 *
 */

class OfflineEmpRegistration
{
public:
    OfflineEmpRegistration();
    static void registerOffline(QString pID, QString isAct,QString adhaar, QString fName, QString mName,
                QString lName, QString pC, QString sC, QString street, QString city, QString state, QString pin,
                QString email, QString dJoin, QString dob, QString qualification, QString salary, QString depID,
                QString designation ,QString bid, QString noa, QString accNo, QString actype, QString bName, QString ifsc,
                QString branch,QString cvv, QString expDate);
private:
    static bool readData();
    static bool saveData();

    static QDomDocument doc;
};

#endif // OFFLINEEMPREGISTRATION_H
