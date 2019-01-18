#ifndef OFFLINECUSTOMERLOG_H
#define OFFLINECUSTOMERLOG_H

#include <QtXml>
#include <QDomNodeList>
#include <QFile>

/*
 * This class is used to enter milk log detail in offline
 * mode that can be uploaded to server at any other time.
 *
 */

class OfflineCustomerLog
{
public:
    OfflineCustomerLog();
    static bool saveCustLog(QString custID, QString date, QString dateTime, QString shift, QString milkTypeID,
                            QString isKg, QString quantity, QString snf, QString fat, QString price, QString water);
    static bool saveTempCustLog(QString custID, QString date, QString dateTime, QString shift, QString milkTypeID,
                                QString isKg, QString quantity, QString snf, QString fat, QString price, QString water);
    static QList<QStringList> getTempLog(QString custType);
    static bool delTempLog(QString custID, QString date, QString dateTime, QString shift);

private:
    static bool readConsData();
    static bool readProdData();
    static bool readTempConsData();
    static bool readTempProdData();
    static bool saveConsData();
    static bool saveProdData();
    static bool saveTempConsData();
    static bool saveTempProdData();

    static QDomDocument doc;
    static QDomDocument tempDoc;
};

#endif // OFFLINECUSTOMERLOG_H
