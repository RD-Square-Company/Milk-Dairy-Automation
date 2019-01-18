#ifndef CUSTOMEROFFLINEENTRY_H
#define CUSTOMEROFFLINEENTRY_H

#include <QtXml>
#include <QDomNodeList>
#include <QFile>
#include <QStringList>

/*
 * This class is used to enter additional
 * customer detail and milk log detail in offline
 * mode that can be uploaded to server at any other time.
 *
 */

class CustomerOfflineEntry
{
public:
    CustomerOfflineEntry();
    static bool saveCustomer(QString mobileNo, QString name);
    static bool saveTempCustomer(QString mobileNo, QString name);
    static bool saveCustLog(QString custID, QString date, QString curDateTime, QString shift, QString AnimalName,
                        QString quantity, QString price, QString isKg);
    static bool saveTempCustLog(QString custID, QString date, QString curDateTime, QString shift, QString AnimalName,
                            QString quantity, QString price, QString isKg);
    static QList<QStringList> getTempCust();
    static bool delTempCust(QString mobileNo);
    static QList<QStringList> getTempLog();
    static bool delTempLog(QString custID, QString date, QString shift, QString dateTime);


private:
    static bool readData();
    static bool readTempData();
    static bool readLog();
    static bool readTempLog();
    static bool saveTempData();
    static bool saveData();
    static bool saveLog();
    static bool saveTempLog();

    static QDomDocument doc;
    static QDomDocument tempDoc;
};
#endif // CUSTOMEROFFLINEENTRY_H
