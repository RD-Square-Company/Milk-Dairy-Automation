#include "mydetail.h"
#include <QDebug>
#include <QMessageBox>

MyDetail::MyDetail()
{
    //setting file
    file.setFileName("/media/rd_square/Important/Qt projects/MyDetail/detailDoc/mydetail.dat");

    //reading data from file
    readData();
}

QDataStream& operator <<(QDataStream& ds, const MyDetail& md)
{
    ds << md.localDID << md.dName << md.dStreet << md.dCity << md.dState << md.dPincode
       << md.estDate << md.tagline << md.dDescription << md.website << md.hbids
       << md.activehb << md.emailID << md.imageNums << md.logo << md.pictures
       << md.ownerID << md.ofName << md.omName << md.olName << md.pContact
       << md.sContact << md.oStreet << md.oCity << md.oPincode << md.oState
       << md.oDescription << md.adhaarNo << md.profilePic << md.fap << md.bap
       << md.bID << md.nameOnAccount << md.acType << md.bankName << md.ifscCode
       << md.branchName << md.cvv << md.expDate << md.accountNo;
    return ds;
}

QDataStream& operator >>(QDataStream& ds, MyDetail& md)
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
    ds >> ts; md.estDate = ts;
    ds >> ts; md.tagline = ts;
    ds >> ts; md.dDescription = ts;
    ds >> ts; md.website = ts;
    ds >> tsl; md.hbids = tsl;
    ds >> ts; md.activehb  = ts;
    ds >> ts; md.emailID = ts;
    ds >> tsl; md.imageNums = tsl;
    ds >> ti; md.logo = ti;
    ds >> til; md.pictures = til;

    //getting owner information variables
    ds >> ts; md.ownerID = ts;
    ds >> ts; md.ofName = ts;
    ds >> ts; md.omName = ts;
    ds >> ts; md.olName = ts;
    ds >> ts; md.pContact = ts;
    ds >> ts; md.sContact = ts;
    ds >> ts; md.oStreet = ts;
    ds >> ts; md.oCity = ts;
    ds >> ts; md.oPincode = ts;
    ds >> ts; md.oState = ts;
    ds >> ts; md.oDescription = ts;
    ds >> ts; md.adhaarNo = ts;
    ds >> ti; md.profilePic = ti;
    ds >> ti; md.fap = ti;
    ds >> ti; md.bap = ti;

    //getting payment information variables
    ds >> tsl; md.bID = tsl;
    ds >> tsl; md.nameOnAccount = tsl;
    ds >> tsl; md.acType = tsl;
    ds >> tsl; md.bankName = tsl;
    ds >> tsl; md.ifscCode = tsl;
    ds >> tsl; md.branchName = tsl;
    ds >> tsl; md.cvv = tsl;
    ds >> tsl; md.expDate = tsl;
    ds >> tsl; md.accountNo = tsl;
    return ds;
}

void MyDetail::setDairyInfo(QString ld, QString dn, QString ds, QString dc, QString dst,QString pin, QString ed, QString tl, QString dd,
                            QString w, QStringList hbs, QString hb, QString eid, QStringList in, QImage l, QList<QImage> p)
{
    // setting dairy information variables
    localDID = ld;
    dName = dn;
    dStreet = ds;
    dCity = dc;
    dState = dst;
    dPincode = pin;
    estDate = ed;
    tagline = tl;
    dDescription = dd;
    website = w;
    hbids = hbs;
    activehb = hb;
    emailID = eid;
    imageNums = in;
    logo = l;
    pictures = p;

    //saving data to file
    saveData();
}

void MyDetail::setOwnerInfo(QString oid, QString ofn, QString omn, QString oln, QString pc, QString sc, QString os, QString oc,
                            QString op, QString ost, QString od, QString a, QImage pp)
{
    // setting owner information variables
    ownerID = oid ;
    ofName = ofn;
    omName = omn;
    olName = oln;
    pContact = pc;
    sContact = sc;
    oStreet = os;
    oCity = oc;
    oPincode = op;
    oState = ost;
    oDescription = od;
    adhaarNo = a;
    profilePic = pp;

    //saving data to file
    saveData();
}

void MyDetail::setBankInfo(QString bd, QString noa, QString at, QString bn, QString ifc, QString brn,
                           QString cv, QString ed, QString acn)
{
    if(!bID.contains(bd)) {
        //setting bank account information variables
        bID.append(bd);
        nameOnAccount.append(noa);
        acType.append(at);
        bankName.append(bn);
        ifscCode.append(ifc);
        branchName.append(brn);
        cvv.append(cv);
        expDate.append(ed);
        accountNo.append(acn);

        //saving data to file
        saveData();
    }
}

void MyDetail::setDID(QString ins)
{
    localDID = ins;
    //saving data to file
    saveData();
}

void MyDetail::setdName(QString ins)
{
    dName = ins;

    //saving data to file
    saveData();
}

void MyDetail::setdStreet(QString ins)
{
    dStreet = ins;

    //saving data to file
    saveData();
}

void MyDetail::setdCity(QString ins)
{
    dCity = ins;

    //saving data to file
    saveData();
}

void MyDetail::setdPin(QString ins)
{
    dPincode = ins;

    //saving data to file
    saveData();
}

void MyDetail::setdState(QString ins)
{
    dState = ins;

    //saving data to file
    saveData();
}

void MyDetail::setestDate(QString ins)
{
    estDate = ins;

    //saving data to file
    saveData();
}

void MyDetail::settagline(QString ins)
{
    tagline = ins;

    //saving data to file
    saveData();
}

void MyDetail::setdD(QString ins)
{
    dDescription = ins;

    //saving data to file
    saveData();
}

void MyDetail::setWebsite(QString ins)
{
    website = ins;

    //saving data to file
    saveData();
}

void MyDetail::sethbids(QStringList ins)
{
    hbids = ins;

    //saving data to file
    saveData();
}

void MyDetail::setAhb(QString ins)
{
    if(!hbids.contains(activehb)) {
        hbids.append(activehb);
    }
    activehb = ins;

    //saving data to file
    saveData();
}

void MyDetail::setemailID(QString ins)
{
    emailID = ins;

    //saving data to file
    saveData();
}

void MyDetail::setiNums(QStringList ins)
{
    imageNums = ins;

    //saving data to file
    saveData();
}

void MyDetail::setLogo(QImage ins)
{
    logo = ins;

    //saving data to file
    saveData();
}

void MyDetail::setPictures(QList<QImage> ins)
{
    pictures = ins;

    //saving data to file
    saveData();
}

QString MyDetail::getDID()
{
    return localDID;
}

QString MyDetail::getdName()
{
    return dName;
}

QString MyDetail::getdStreet()
{
    return dStreet;
}

QString MyDetail::getdCity()
{
    return dCity;
}

QString MyDetail::getdPin()
{
    return dPincode;
}

QString MyDetail::getdState()
{
    return dState;
}

QString MyDetail::getestDate()
{
    return estDate;
}

QString MyDetail::gettagline()
{
    return tagline;
}

QString MyDetail::getdD()
{
    return dDescription;
}

QString MyDetail::getWebsite()
{
    return website;
}

QStringList MyDetail::gethbids()
{
    return hbids;
}

QString MyDetail::getAhb()
{
    return activehb;
}

QString MyDetail::getemailID()
{
    return emailID;
}

QStringList MyDetail::getiNums()
{
    return imageNums;
}

QImage MyDetail::getLogo()
{
    return logo;
}

QList<QImage> MyDetail::getPictures()
{
    return pictures;
}

MyDetail& MyDetail::operator =(MyDetail& md)
{
    // dairy information variables
    localDID=md.localDID ;
    dStreet = md.dStreet ;
    dCity = md.dCity ;
    dPincode = md.dPincode ;
    dState = md.dState;
    estDate = md.estDate ;
    tagline = md.tagline ;
    dDescription = md.dDescription ;
    website = md.website ;
    hbids = md.hbids;
    activehb = md.activehb ;
    emailID = md.emailID ;
    imageNums = md.imageNums ;
    logo = md.logo ;
    pictures  = md.pictures;

    //owner information variables
    ownerID = md.ownerID ;
    ofName = md.ofName ;
    omName = md.omName ;
    olName = md.olName ;
    pContact = md.pContact;
    sContact = md.sContact ;
    oStreet = md.oStreet ;
    oCity = md.oCity ;
    oPincode = md.oPincode ;
    oState = md.oState;
    oDescription = md.oDescription ;
    adhaarNo = md.adhaarNo ;
    profilePic = md.profilePic ;
    fap = md.fap ;
    bap = md.bap;

    // diary account information variables
    bID = md.bID ;
    nameOnAccount = md.nameOnAccount ;
    acType = md.acType ;
    bankName = md.bankName ;
    ifscCode = md.ifscCode;
    branchName = md.branchName ;
    cvv = md.cvv ;
    expDate = md.expDate ;
    accountNo = md.accountNo;

    file.setFileName(md.file.fileName());

    return md;
}

void MyDetail::setOID(QString ins)
{
    ownerID = ins;

    //saving data to file
    saveData();
}

void MyDetail::setofName(QString ins)
{
    ofName = ins;

    //saving data to file
    saveData();
}

void MyDetail::setomName(QString ins)
{
    omName = ins;

    //saving data to file
    saveData();
}

void MyDetail::setolName(QString ins)
{
    olName = ins;

    //saving data to file
    saveData();
}

void MyDetail::setpc(QString ins)
{
    pContact = ins;

    //saving data to file
    saveData();
}

void MyDetail::setsc(QString ins)
{
    sContact = ins;

    //saving data to file
    saveData();
}

void MyDetail::setoStreet(QString ins)
{
    oStreet = ins;

    //saving data to file
    saveData();
}

void MyDetail::setoCity(QString ins)
{
    oCity = ins;

    //saving data to file
    saveData();
}

void MyDetail::setoPin(QString ins)
{
    oPincode = ins;

    //saving data to file
    saveData();
}

void MyDetail::setoState(QString ins)
{
    oState = ins;

    //saving data to file
    saveData();
}

void MyDetail::setoD(QString ins)
{
    oDescription = ins;

    //saving data to file
    saveData();
}

void MyDetail::setAdhaar(QString ins)
{
    adhaarNo = ins;

    //saving data to file
    saveData();
}

void MyDetail::setpPic(QImage ins)
{
    profilePic  = ins;

    //saving data to file
    saveData();
}

void MyDetail::setfap(QImage ins)
{
    fap  = ins;

    //saving data to file
    saveData();
}

void MyDetail::setbap(QImage ins)
{
     bap = ins;

     //saving data to file
     saveData();
}

QString MyDetail::getOID()
{
    return ownerID;
}

QString MyDetail::getofName()
{
    return ofName;
}

QString MyDetail::getomName()
{
    return omName;
}

QString MyDetail::getolName()
{
    return olName;
}

QString MyDetail::getpc()
{
    return pContact;
}

QString MyDetail::getsc()
{
    return sContact;
}

QString MyDetail::getoStreet()
{
    return oStreet;
}

QString MyDetail::getoCity()
{
    return oCity;
}

QString MyDetail::getoPin()
{
    return oPincode;
}

QString MyDetail::getoState()
{
    return oState;
}

QString MyDetail::getoD()
{
    return oDescription;
}

QString MyDetail::getAdhaar()
{
    return adhaarNo;
}

QImage MyDetail::getpPic()
{
    return profilePic;
}

QImage MyDetail::getfap()
{
    return fap;
}

QImage MyDetail::getbap()
{
    return bap;
}

QStringList MyDetail::getBid()
{
    return bID;
}

QStringList MyDetail::getnoa()
{
    return nameOnAccount;
}

QStringList MyDetail::getacType()
{
    return acType;
}

QStringList MyDetail::getbankName()
{
    return bankName;
}

QStringList MyDetail::getifsc()
{
    return ifscCode;
}

QStringList MyDetail::getbranchName()
{
    return branchName;
}

QStringList MyDetail::getcvv()
{
    return cvv;
}

QStringList MyDetail::getexpDate()
{
    return expDate;
}

QStringList MyDetail::getaccountNo()
{
    return accountNo;
}

void MyDetail::readData()
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

void MyDetail::saveData()
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

void MyDetail::removeBankInfo(QString bd)
{
    if(bID.contains(bd)) {
        int ind = bID.indexOf(bd);
        bID.removeAt(ind);
        nameOnAccount.removeAt(ind);
        acType.removeAt(ind);
        bankName.removeAt(ind);
        ifscCode.removeAt(ind);
        branchName.removeAt(ind);
        cvv.removeAt(ind);
        expDate.removeAt(ind);
        accountNo.removeAt(ind);
    }

    //saving updated data to file
    saveData();
}
