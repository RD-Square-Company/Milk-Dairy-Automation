#include "offlinecustregistration.h"
#include <QMessageBox>
#include <QDebug>
#include "../MyDetail/mydetail.h"

QDomDocument OfflineCustRegistration::doc = QDomDocument();

OfflineCustRegistration::OfflineCustRegistration()
{
    /*
     * empty constructor
     */
}

bool OfflineCustRegistration::readData()
{
    QFile file("/media/rd_square/Important/Qt projects/CustomerRegistration/registrationFiles/customerregistration.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(NULL,
                              QObject::tr("Critical Internal File Error!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "There is some error in opening file. Your application may misbehave due this. Please restart or"
                                          " the application</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    QByteArray content = file.readAll();
    file.close();
    doc.setContent(content);
    return true;
}

bool OfflineCustRegistration::saveData()
{
    QFile file("/media/rd_square/Important/Qt projects/CustomerRegistration/registrationFiles/customerregistration.xml");
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(NULL,
                              QObject::tr("Critical Internal File Error!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "There is some error in opening file. Your application may misbehave due this. Please restart or"
                                          " the application</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    QByteArray content = doc.toByteArray();
    file.write(content);
    file.close();
    return true;
}

void OfflineCustRegistration::registerOffline(QString cID, QString isApp,QString adhaar, QString fName, QString mName,
        QString lName, QString pC, QString sC, QString street, QString city, QString state, QString pin,
        QString email, QString bid, QString noa, QString accNo, QString actype, QString bName, QString ifsc, QString branch,
                                              QString cvv, QString expDate)
{
    //reading data from file
    if(!readData()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }
    if(doc.doctype().name() != "customerinfo") {
        QMessageBox::critical(NULL,
                              QObject::tr("Data File Removed!"),
                              QObject::tr("<html><p>Offline Saving Failed - File Removed!</p><p>"
                                          "Data file is removed please run update on software otherwise your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }
    QDomElement root = doc.documentElement();
    MyDetail mDetail;
    if(root.tagName() != mDetail.getDID()) {
        QMessageBox::critical(NULL,
                              QObject::tr("File Permission Denied!"),
                              QObject::tr("<html><p>Dairy ID Changed!</p><p>"
                                          "You are using file of different dairy which is not permissible."
                                          " Please delete the required file or update settings to correct the details. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    //making xml document fragment for editing
    QDomDocumentFragment fragment = doc.createDocumentFragment();
    QDomElement custID = doc.createElement(cID);
    QDomAttr id = doc.createAttribute("id");
    id.setValue(isApp);
    custID.setAttributeNode(id);

    // settting adhaar no
    QDomElement xadhaar = doc.createElement("adhaar");
    QDomText adh = doc.createTextNode(adhaar);
    xadhaar.appendChild(adh);
    custID.appendChild(xadhaar);

    //setting name tag field
    QDomElement name = doc.createElement("name");
    QDomElement first = doc.createElement("first");
    QDomElement middle = doc.createElement("middle");
    QDomElement last  = doc.createElement("last");
    QDomText fn = doc.createTextNode(fName);
    QDomText mn = doc.createTextNode(mName);
    QDomText ln = doc.createTextNode(lName);
    first.appendChild(fn);
    middle.appendChild(mn);
    last.appendChild(ln);
    name.appendChild(first);
    name.appendChild(middle);
    name.appendChild(last);
    custID.appendChild(name);

    //setting contact tag field
    QDomElement contact = doc.createElement("contact");
    QDomElement primary = doc.createElement("primary");
    QDomElement secondary = doc.createElement("secondary");
    QDomText pcont = doc.createTextNode(pC);
    QDomText scont = doc.createTextNode(sC);
    primary.appendChild(pcont);
    secondary.appendChild(scont);
    contact.appendChild(primary);
    contact.appendChild(secondary);
    custID.appendChild(contact);

    //setting address tag field
    QDomElement address = doc.createElement("address");
    QDomElement xstreet = doc.createElement("street");
    QDomElement xcity = doc.createElement("city");
    QDomElement xstate = doc.createElement("state");
    QDomElement xpincode = doc.createElement("pincode");
    QDomText st = doc.createTextNode(street);
    QDomText ci = doc.createTextNode(city);
    QDomText sta = doc.createTextNode(state);
    QDomText pi = doc.createTextNode(pin);
    xstreet.appendChild(st);
    xcity.appendChild(ci);
    xstate.appendChild(sta);
    xpincode.appendChild(pi);
    address.appendChild(xstreet);
    address.appendChild(xcity);
    address.appendChild(xstate);
    address.appendChild(xpincode);
    custID.appendChild(address);

    //setting email id tag field
    QDomElement emailid = doc.createElement("email");
    QDomText eid = doc.createTextNode(email);
    emailid.appendChild(eid);
    custID.appendChild(emailid);

    //settig bank information tag field
    if (!bid.isEmpty()) {
        QDomElement bankinfo = doc.createElement("bankinfo");
        QDomElement xbid = doc.createElement("B" + bid);
        QDomAttr acc = doc.createAttribute("id");
        acc.setValue(accNo);
        xbid.setAttributeNode(acc);
        QDomElement xnoa = doc.createElement("noa");
        QDomElement act = doc.createElement("actype");
        QDomElement bankName = doc.createElement("bankname");
        QDomElement ifscCode = doc.createElement("ifsc");
        QDomElement branchName = doc.createElement("branch");
        QDomElement cvvN = doc.createElement("cvv");
        QDomElement xexpDate = doc.createElement("expdate");

        QDomText xn = doc.createTextNode(noa);
        QDomText ac = doc.createTextNode(actype);
        QDomText bn = doc.createTextNode(bName);
        QDomText cv = doc.createTextNode(cvv);
        QDomText ed = doc.createTextNode(expDate);
        QDomText ifs = doc.createTextNode(ifsc);
        QDomText bra = doc.createTextNode(branch);

        xnoa.appendChild(xn);
        act.appendChild(ac);
        bankName.appendChild(bn);
        cvvN.appendChild(cv);
        xexpDate.appendChild(ed);
        ifscCode.appendChild(ifs);
        branchName.appendChild(bra);

        xbid.appendChild(xnoa);
        xbid.appendChild(act);
        xbid.appendChild(bankName);
        xbid.appendChild(ifscCode);
        xbid.appendChild(branchName);
        xbid.appendChild(cvvN);
        xbid.appendChild(xexpDate);
        bankinfo.appendChild(xbid);
        custID.appendChild(bankinfo);
    }

    //appending document fragment to document
    fragment.appendChild(custID);
    root.insertAfter(fragment, root.lastChild());

    //saving data to file
    if(!saveData()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }
}
QString OfflineCustRegistration::searchCustomer(QString cID)
{
    if(!readData())
        return "";
    if(doc.doctype().name() != "customerinfo")
        return "";
    QDomElement root = doc.documentElement();
    MyDetail mDetail;
    if(root.tagName() != mDetail.getDID())
        return "";
    QDomNodeList custList = root.elementsByTagName(cID);
    if(custList.length() == 0)
        return "";
    QDomElement customer = custList.at(0).toElement();
    QString name = customer.elementsByTagName("first").at(0).toElement().text();
    name += " ";
    name += customer.elementsByTagName("middle").at(0).toElement().text();
    name += " ";
    name += customer.elementsByTagName("last").at(0).toElement().text();
    return name;
}
