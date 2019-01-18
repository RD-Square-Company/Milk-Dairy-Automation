#include "localbranch.h"
#include <QDebug>
#include <QMessageBox>

LocalBranch::LocalBranch()
{
    //setting file
    file.setFileName("/media/rd_square/Important/Qt projects/MyDetail/detailDoc/localbranch.dat");

    //reading data from file
    readData();
}

QDataStream& operator <<(QDataStream& ds, const LocalBranch& md)
{
    ds << md.localDID << md.dName << md.dStreet << md.dCity << md.dState << md.dPincode
       << md.logo  << md.ofName << md.omName << md.olName << md.pContact
       << md.sContact ;
    return ds;
}

QDataStream& operator >>(QDataStream& ds, LocalBranch& md)
{
    QStringList ts;
    QList<QImage> ti;

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

void LocalBranch::setDairyInfo(QString ld, QString dn, QString ds, QString dc, QString dst,QString pin, QImage l,
                               QString ofn, QString omn, QString oln, QString pc, QString sc)
{
    if(!localDID.contains(ld)){
        // setting dairy information variables
        localDID.append(ld);
        dName.append(dn);
        dStreet.append(ds);
        dCity.append(dc);
        dState.append(dst);
        dPincode.append(pin);
        logo.append(l);

        //setting owner info
        ofName.append(ofn);
        omName.append(omn);
        olName.append(oln);
        pContact.append(pc);
        sContact.append(sc);

        //saving data to file
        saveData();
    }
}


QStringList LocalBranch::getDID()
{
    return localDID;
}

QStringList LocalBranch::getdName()
{
    return dName;
}

QStringList LocalBranch::getdStreet()
{
    return dStreet;
}

QStringList LocalBranch::getdCity()
{
    return dCity;
}

QStringList LocalBranch::getdPin()
{
    return dPincode;
}

QStringList LocalBranch::getdState()
{
    return dState;
}

QList<QImage> LocalBranch::getLogo()
{
    return logo;
}

LocalBranch& LocalBranch::operator =(LocalBranch& md)
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

QStringList LocalBranch::getofName()
{
    return ofName;
}

QStringList LocalBranch::getomName()
{
    return omName;
}

QStringList LocalBranch::getolName()
{
    return olName;
}

QStringList LocalBranch::getpc()
{
    return pContact;
}

QStringList LocalBranch::getsc()
{
    return sContact;
}

void LocalBranch::readData()
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

void LocalBranch::saveData()
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
