#ifndef OFFLINEDEPREGISTRATION_H
#define OFFLINEDEPREGISTRATION_H

#include <QtXml>
#include <QDomNodeList>
#include <QFile>

/*
 * This class is used to save offline detail of
 * registered department.
 * It will be further used to show this information offline
 * to user
 *
 */

class OfflineDepRegistration
{
public:
    OfflineDepRegistration();
    static void registerOffline(QString dID, QString dName, QString hID, QString desc);
    static void depHeadEdit(QString hID);
    static void editHead(QString dID, QString hID);
private:
    static bool readData();
    static bool saveData();

    static QDomDocument doc;
};

#endif // OFFLINEDEPREGISTRATION_H
