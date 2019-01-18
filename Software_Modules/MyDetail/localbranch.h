#ifndef LOCALBRANCH_H
#define LOCALBRANCH_H

/*
 *
 * This class is used to save
 * details of local branch diary, dairy secretary and dairy payment account details.
 * It will provide all the details offline
 *
 */

#include <QStringList>
#include <QString>
#include <QString>
#include <QImage>
#include <QList>
#include <QDataStream>
#include <QFile>

class LocalBranch
{
public:
    LocalBranch();
    void setDairyInfo(QString ld, QString dn, QString ds, QString dc, QString dst,QString pin, QImage l,
                      QString ofn, QString omn, QString oln, QString pc, QString sc);

    //some operational getting functions
    //dairy functions
    QStringList getDID();
    QStringList getdName();
    QStringList getdStreet();
    QStringList getdCity();
    QStringList getdPin();
    QStringList getdState();
    QList<QImage> getLogo();

    //owner functions
    QStringList getofName();
    QStringList getomName();
    QStringList getolName();
    QStringList getpc();
    QStringList getsc();

    //operator overloading
    friend QDataStream& operator <<(QDataStream& ds, const LocalBranch& md);
    friend QDataStream& operator >>(QDataStream& ds, LocalBranch& md);
    LocalBranch& operator =(LocalBranch& md);

private:
    void saveData();
    void readData();

    //variables about dairy
    QStringList localDID;
    QStringList dName;
    QStringList dStreet;
    QStringList dCity;
    QStringList dPincode;
    QStringList dState;
    QList<QImage> logo;

    //variables about owner
    QStringList ofName;
    QStringList omName;
    QStringList olName;
    QStringList pContact;
    QStringList sContact;

    QFile file;
};

#endif // LOCALBRANCH_H
