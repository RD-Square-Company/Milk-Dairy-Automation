#include "higherbranch.h"
#include <QDebug>
#include <QMessageBox>

HigherBranch::HigherBranch()
{
    //setting file
    file.setFileName("/media/rd_square/Important/Qt projects/MyDetail/detailDoc/highbranch.dat");

    //reading data from file
    readData();
}

QDataStream& operator <<(QDataStream& ds, const HigherBranch& md)
{
    ds << md.localDID << md.dName << md.dStreet << md.dCity << md.dState << md.dPincode
       << md.logo  << md.ofName << md.omName << md.olName << md.pContact
       << md.sContact ;
    return ds;
}

QDataStream& operator >>(QDataStream& ds, HigherBranch& md)
{
    QString ts;
    QStringList tsl;
    QImage ti;
    QList<QImage> til;

    //getting dairy information variables
    ds >> ts; md.localDID = ts;
    ds >> ts; md.dName = ts;
    ds >> ts; md.dStreet = ts;
    ds >> ts; md.dCity = ts;
    ds >> ts; md.dState = ts;
    ds >> ts; md.dPincode = ts;
    ds >> ti; md.logo = ti;

    //getting owner information variables
    ds >> ts; md.ofName = ts;
    ds >> ts; md.omName = ts;
    ds >> ts; md.olName = ts;
    ds >> ts; md.pContact = ts;
    ds >> ts; md.sContact = ts;

    return ds;
}

void HigherBranch::setDairyInfo(QString ld, QString dn, QString ds, QString dc, QString dst,QString pin, QImage l)
{
    // setting dairy information variables
    localDID = ld;
    dName = dn;
    dStreet = ds;
    dCity = dc;
    dState = dst;
    dPincode = pin;
    logo = l;

    //saving data to file
    saveData();
}

void HigherBranch::setOwnerInfo(QString ofn, QString omn, QString oln, QString pc, QString sc)
{
    // setting owner information variables
    ofName = ofn;
    omName = omn;
    olName = oln;
    pContact = pc;
    sContact = sc;

    //saving data to file
    saveData();
}

void HigherBranch::setDID(QString ins)
{
    localDID = ins;
    //saving data to file
    saveData();
}

void HigherBranch::setdName(QString ins)
{
    dName = ins;

    //saving data to file
    saveData();
}

void HigherBranch::setdStreet(QString ins)
{
    dStreet = ins;

    //saving data to file
    saveData();
}

void HigherBranch::setdCity(QString ins)
{
    dCity = ins;

    //saving data to file
    saveData();
}

void HigherBranch::setdPin(QString ins)
{
    dPincode = ins;

    //saving data to file
    saveData();
}

void HigherBranch::setdState(QString ins)
{
    dState = ins;

    //saving data to file
    saveData();
}

void HigherBranch::setLogo(QImage ins)
{
    logo = ins;

    //saving data to file
    saveData();
}

QString HigherBranch::getDID()
{
    return localDID;
}

QString HigherBranch::getdName()
{
    return dName;
}

QString HigherBranch::getdStreet()
{
    return dStreet;
}

QString HigherBranch::getdCity()
{
    return dCity;
}

QString HigherBranch::getdPin()
{
    return dPincode;
}

QString HigherBranch::getdState()
{
    return dState;
}

QImage HigherBranch::getLogo()
{
    return logo;
}

HigherBranch& HigherBranch::operator =(HigherBranch& md)
{
    // dairy information variables
    localDID=md.localDID ;
    dStreet = md.dStreet ;
    dCity = md.dCity ;
    dPincode = md.dPincode ;
    dState = md.dState;
    logo = md.logo ;

    //owner information variables
    ofName = md.ofName ;
    omName = md.omName ;
    olName = md.olName ;
    pContact = md.pContact;
    sContact = md.sContact ;

    file.setFileName(md.file.fileName());

    return md;
}

void HigherBranch::setofName(QString ins)
{
    ofName = ins;

    //saving data to file
    saveData();
}

void HigherBranch::setomName(QString ins)
{
    omName = ins;

    //saving data to file
    saveData();
}

void HigherBranch::setolName(QString ins)
{
    olName = ins;

    //saving data to file
    saveData();
}

void HigherBranch::setpc(QString ins)
{
    pContact = ins;

    //saving data to file
    saveData();
}

void HigherBranch::setsc(QString ins)
{
    sContact = ins;

    //saving data to file
    saveData();
}

QString HigherBranch::getofName()
{
    return ofName;
}

QString HigherBranch::getomName()
{
    return omName;
}

QString HigherBranch::getolName()
{
    return olName;
}

QString HigherBranch::getpc()
{
    return pContact;
}

QString HigherBranch::getsc()
{
    return sContact;
}

void HigherBranch::readData()
{
    if(!file.open(QIODevice::ReadWrite)){
        QMessageBox::critical(NULL,
                              QObject::tr("Critical Internal File Error!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "There is some error in opening file. Your application may misbehave due this. Please restart or"
                                          " the application</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_5_5);
    ds >> *this;
    file.close();
}

void HigherBranch::saveData()
{
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(NULL,
                              QObject::tr("Critical Internal File Error!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "There is some error in opening file. Your application may misbehave due this. Please restart or"
                                          " the application</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_5_5);
    ds << *this;
    file.close();
}
