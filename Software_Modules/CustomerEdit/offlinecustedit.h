#ifndef OFFLINECUSTEDIT_H
#define OFFLINECUSTEDIT_H

#include <QtXml>
#include <QDomNodeList>
#include <QFile>

/*
 * This class is used to edit offline detail of
 * registered customers.
 * It will be further used to show this information offline
 * to user
 *
 */

class OfflineCustEdit
{
public:
    OfflineCustEdit();
    static void editGeneral(QString cID, QString isApp, QString fName, QString mName, QString lName,
                                QString pC, QString sC, QString street, QString city, QString state, QString pin,
                                QString email);
    static void editPayment(QString cID, QString bid, QString noa, QString accNo, QString actype, QString bName, QString ifsc,
                            QString branch, QString cvv, QString expDate);
    static void removePayment(QString cID, QString bid);
private:
    static bool readData();
    static bool saveData();

    static QDomDocument doc;
};

#endif // OFFLINECUSTEDIT_H
