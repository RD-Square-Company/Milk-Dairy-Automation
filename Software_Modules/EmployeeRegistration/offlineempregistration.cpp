#include "offlineempregistration.h"
#include <QMessageBox>
#include <QDebug>
#include "../MyDetail/mydetail.h"

QDomDocument OfflineEmpRegistration::doc = QDomDocument();

OfflineEmpRegistration::OfflineEmpRegistration()
{
    /*
     * empty constructor
     */
}

bool OfflineEmpRegistration::readData()
{
    QFile file("/media/rd_square/Important/Qt projects/EmployeeRegistration/registrationFiles/employeeregistration.xml");
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

bool OfflineEmpRegistration::saveData()
{
    QFile file("/media/rd_square/Important/Qt projects/EmployeeRegistration/registrationFiles/employeeregistration.xml");
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

void OfflineEmpRegistration::registerOffline(QString pID, QString isAct,QString adhaar, QString fName, QString mName,
        QString lName, QString pC, QString sC, QString street, QString city, QString state, QString pin,
        QString email, QString dJoin, QString dob, QString qualification, QString salary, QString depID,
        QString designation ,QString bid, QString noa, QString accNo, QString actype, QString bName, QString ifsc,
        QString branch,QString cvv, QString expDate)
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
    if(doc.doctype().name() != "employeeinfo") {
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
    QDomElement custID = doc.createElement("E"+pID);
    QDomAttr id = doc.createAttribute("id");
    id.setValue(isAct);
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

    //setting date of join, dob, qualification, salary
    QDomElement datJoin = doc.createElement("dojoin");
    QDomElement edob = doc.createElement("dob");
    QDomElement qual = doc.createElement("qualification");
    QDomElement sal = doc.createElement("salary");

    QDomText dj = doc.createTextNode(dJoin);
    QDomText edb = doc.createTextNode(dob);
    QDomText qlf = doc.createTextNode(qualification);
    QDomText sl = doc.createTextNode(salary);
    datJoin.appendChild(dj);
    edob.appendChild(edb);
    qual.appendChild(qlf);
    sal.appendChild(sl);

    custID.appendChild(datJoin);
    custID.appendChild(edob);
    custID.appendChild(qual);
    custID.appendChild(sal);

    //setting department tag field
    QDomElement department = doc.createElement("department");
    QDomElement did = doc.createElement("depid");
    QDomElement desg = doc.createElement("designation");

    QDomText dpid = doc.createTextNode(depID);
    QDomText dsg = doc.createTextNode(designation);

    did.appendChild(dpid);
    desg.appendChild(dsg);
    department.appendChild(did);
    department.appendChild(desg);
    custID.appendChild(department);

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
