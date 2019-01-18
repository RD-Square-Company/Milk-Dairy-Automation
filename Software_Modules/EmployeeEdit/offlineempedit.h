#ifndef OFFLINEEMPEDIT_H
#define OFFLINEEMPEDIT_H

#include <QtXml>
#include <QDomNodeList>
#include <QFile>

/*
 * This class is used to edit offline detail of
 * registered employees.
 * It will be further used to show this information offline
 * to user
 *
 */

class OfflineEmpEdit
{
public:
    OfflineEmpEdit();
    static void editGeneral(QString pID, QString isAct, QString fName, QString mName,
                QString lName, QString pC, QString sC, QString street, QString city, QString state, QString pin,
                QString email, QString dob, QString qualification, QString salary);
    static void editPayment(QString pID, QString bid, QString noa, QString accNo, QString actype, QString bName, QString ifsc,
                            QString branch,QString cvv, QString expDate);
    static void editDepInfo(QString eID, QString dID, QString desg, QString salary);
    static void editSalary(QString eID, QString salary);
    static void editDesignation(QString eID, QString desg);
    static void editDepID(QString eID, QString dID);
    static void removePayment(QString pID, QString bid);
private:
    static bool readData();
    static bool saveData();

    static QDomDocument doc;
};

#endif // OFFLINEEMPEDIT_H
