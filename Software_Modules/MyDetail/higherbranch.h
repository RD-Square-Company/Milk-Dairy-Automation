#ifndef HIGHERBRANCH_H
#define HIGHERBRANCH_H

/*
 *
 * This class is used to save
 * details of higher branch diary, dairy secretary and dairy payment account details.
 * It will provide all the details offline
 *
 */

#include <QString>
#include <QStringList>
#include <QImage>
#include <QList>
#include <QDataStream>
#include <QFile>

class HigherBranch
{
public:
    HigherBranch();
    void setDairyInfo(QString ld, QString dn, QString ds, QString dc, QString dst,QString pin, QImage l);
    void setOwnerInfo(QString ofn, QString omn, QString oln, QString pc, QString sc );

    //some oprational setting functions
    //dairy functions
    void setDID(QString ins);
    void setdName(QString ins);
    void setdStreet(QString ins);
    void setdCity(QString ins);
    void setdPin(QString ins);
    void setdState(QString ins);
    void setLogo(QImage ins);

    //owner functions
    void setofName(QString ins);
    void setomName(QString ins);
    void setolName(QString ins);
    void setpc(QString ins);
    void setsc(QString ins);

    //some operational getting functions
    //dairy functions
    QString getDID();
    QString getdName();
    QString getdStreet();
    QString getdCity();
    QString getdPin();
    QString getdState();
    QImage getLogo();

    //owner functions
    QString getofName();
    QString getomName();
    QString getolName();
    QString getpc();
    QString getsc();

    //operator overloading
    friend QDataStream& operator <<(QDataStream& ds, const HigherBranch& md);
    friend QDataStream& operator >>(QDataStream& ds, HigherBranch& md);
    HigherBranch& operator =(HigherBranch& md);

private:
    void saveData();
    void readData();

    //variables about dairy
    QString localDID;
    QString dName;
    QString dStreet;
    QString dCity;
    QString dPincode;
    QString dState;
    QImage logo;

    //variables about owner
    QString ofName;
    QString omName;
    QString olName;
    QString pContact;
    QString sContact;

    QFile file;
};

#endif // HIGHERBRANCH_H
