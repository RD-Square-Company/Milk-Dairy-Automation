#ifndef MYDETAIL_H
#define MYDETAIL_H

/*
 *
 * This class is used to save
 * details of diary, dairy secretary and dairy payment account details.
 * It will provide all the details offline
 *
 */

#include <QString>
#include <QStringList>
#include <QImage>
#include <QList>
#include <QDataStream>
#include <QFile>

class MyDetail
{
public:
    MyDetail();
    void setDairyInfo(QString ld, QString dn, QString ds, QString dc, QString dst,QString pin, QString ed, QString tl,
                      QString dd, QString w, QStringList hbs, QString hb, QString eid, QStringList in,
                      QImage l, QList<QImage> p);
    void setOwnerInfo(QString oid, QString ofn, QString omn, QString oln, QString pc, QString sc,
                      QString os, QString oc, QString op, QString ost, QString od, QString a, QImage pp);
    void setBankInfo(QString bd, QString noa, QString at, QString bn, QString ifc,
                     QString brn, QString cv, QString ed, QString acn);
    void removeBankInfo(QString bd);

    //some oprational setting functions
    //dairy functions
    void setDID(QString ins);
    void setdName(QString ins);
    void setdStreet(QString ins);
    void setdCity(QString ins);
    void setdPin(QString ins);
    void setdState(QString ins);
    void setestDate(QString ins);
    void settagline(QString ins);
    void setdD(QString ins);
    void setWebsite(QString ins);
    void sethbids(QStringList ins);
    void setAhb(QString ins);
    void setemailID(QString ins);
    void setiNums(QStringList ins);
    void setLogo(QImage ins);
    void setPictures(QList<QImage> ins);

    //owner functions
    void setOID(QString ins);
    void setofName(QString ins);
    void setomName(QString ins);
    void setolName(QString ins);
    void setpc(QString ins);
    void setsc(QString ins);
    void setoStreet(QString ins);
    void setoCity(QString ins);
    void setoPin(QString ins);
    void setoState(QString ins);
    void setoD(QString ins);
    void setAdhaar(QString ins);
    void setpPic(QImage ins);
    void setfap(QImage ins);
    void setbap(QImage ins);

    //some operational getting functions
    //dairy functions
    QString getDID();
    QString getdName();
    QString getdStreet();
    QString getdCity();
    QString getdPin();
    QString getdState();
    QString getestDate();
    QString gettagline();
    QString getdD();
    QString getWebsite();
    QStringList gethbids();
    QString getAhb();
    QString getemailID();
    QStringList getiNums();
    QImage getLogo();
    QList<QImage> getPictures();

    //owner functions
    QString getOID();
    QString getofName();
    QString getomName();
    QString getolName();
    QString getpc();
    QString getsc();
    QString getoStreet();
    QString getoCity();
    QString getoPin();
    QString getoState();
    QString getoD();
    QString getAdhaar();
    QImage getpPic();
    QImage getfap();
    QImage getbap();

    // bank account details
    QStringList getBid();
    QStringList getnoa();
    QStringList getacType();
    QStringList getbankName();
    QStringList getifsc();
    QStringList getbranchName();
    QStringList getcvv();
    QStringList getexpDate();
    QStringList getaccountNo();

    //operator overloading
    friend QDataStream& operator <<(QDataStream& ds, const MyDetail& md);
    friend QDataStream& operator >>(QDataStream& ds, MyDetail& md);
    MyDetail& operator =(MyDetail& md);

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
    QString estDate;
    QString tagline;
    QString dDescription;
    QString website;
    QStringList hbids;
    QString activehb;
    QString emailID;
    QStringList imageNums;
    QImage logo;
    QList<QImage> pictures;

    //variables about owner
    QString ownerID;
    QString ofName;
    QString omName;
    QString olName;
    QString pContact;
    QString sContact;
    QString oStreet;
    QString oCity;
    QString oPincode;
    QString oState;
    QString oDescription;
    QString adhaarNo;
    QImage profilePic;
    QImage fap;
    QImage bap;

    //variables about bank account details of dairy
    QStringList bID;
    QStringList nameOnAccount;
    QStringList acType;
    QStringList bankName;
    QStringList ifscCode;
    QStringList branchName;
    QStringList cvv;
    QStringList expDate;
    QStringList accountNo;
    QFile file;
};

#endif // MYDETAIL_H
