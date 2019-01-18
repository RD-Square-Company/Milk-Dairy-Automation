#include "offlineempedit.h"
#include <QMessageBox>
#include <QDebug>
#include "../MyDetail/mydetail.h"

QDomDocument OfflineEmpEdit::doc = QDomDocument();

OfflineEmpEdit::OfflineEmpEdit()
{
    /*
     * empty constructor
     */
}

bool OfflineEmpEdit::readData()
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

bool OfflineEmpEdit::saveData()
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

void OfflineEmpEdit::editGeneral(QString pID, QString isAct, QString fName, QString mName,
        QString lName, QString pC, QString sC, QString street, QString city, QString state, QString pin,
        QString email, QString dob, QString qualification, QString salary)
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
    MyDetail mDetail;
    if(doc.documentElement().tagName() != mDetail.getDID()) {
        QMessageBox::critical(NULL,
                              QObject::tr("File Permission Denied!"),
                              QObject::tr("<html><p>Dairy ID Changed!</p><p>"
                                          "You are using file of different dairy which is not permissible."
                                          " Please delete the required file or update settings to correct the details. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QDomElement root = doc.elementsByTagName("E"+pID).at(0).toElement();
    root.setAttribute("id", isAct);

    //setting name of employee
    QDomElement first = root.elementsByTagName("first").at(0).toElement();
    QDomElement middle = root.elementsByTagName("middle").at(0).toElement();
    QDomElement last = root.elementsByTagName("last").at(0).toElement();

    QDomText pn = first.firstChild().toText();
    pn.setData(fName);

    if(middle.hasChildNodes() && (!mName.isEmpty())){
        QDomText tmp = middle.firstChild().toText();
        tmp.setData(mName);
    } else if (!middle.hasChildNodes()  & (!mName.isEmpty())) {
        QDomText tmp = doc.createTextNode(mName);
        middle.appendChild(tmp);
    }

    if(last.hasChildNodes() && (!lName.isEmpty())) {
        QDomText tmp = last.firstChild().toText();
        tmp.setData(lName);
    } else if (!last.hasChildNodes() && (!lName.isEmpty())) {
        QDomText tmp = doc.createTextNode(lName);
        last.appendChild(tmp);
    }

    QDomElement dobirth = root.elementsByTagName("dob").at(0).toElement();
    if(dobirth.hasChildNodes()){
        QDomText tmp = dobirth.firstChild().toText();
        tmp.setData(dob);
    }

    QDomElement primary = root.elementsByTagName("primary").at(0).toElement();
    QDomElement secondary = root.elementsByTagName("secondary").at(0).toElement();
    if(primary.hasChildNodes()){
        QDomText tmp = primary.firstChild().toText();
        tmp.setData(pC);
    }
    if(secondary.hasChildNodes() && (!sC.isEmpty())){
        QDomText tmp = secondary.firstChild().toText();
        tmp.setData(sC);
    } else if(!secondary.hasChildNodes() && (!sC.isEmpty())) {
        QDomText tmp = doc.createTextNode(sC);
        secondary.appendChild(tmp);
    }

    QDomElement xstreet = root.elementsByTagName("street").at(0).toElement();
    QDomElement xcity = root.elementsByTagName("city").at(0).toElement();
    QDomElement xstate = root.elementsByTagName("state").at(0).toElement();
    QDomElement pincode = root.elementsByTagName("pincode").at(0).toElement();

    if(xstreet.hasChildNodes()) {
        QDomText tmp = xstreet.firstChild().toText();
        tmp.setData(street);
    }
    if(xcity.hasChildNodes()) {
        QDomText tmp = xcity.firstChild().toText();
        tmp.setData(city);
    }
    if(xstate.hasChildNodes()) {
        QDomText tmp = xstate.firstChild().toText();
        tmp.setData(state);
    }
    if(pincode.hasChildNodes()) {
        QDomText tmp = pincode.firstChild().toText();
        tmp.setData(pin);
    }

    QDomElement emailid = root.elementsByTagName("email").at(0).toElement();
    if(emailid.hasChildNodes() && (!email.isEmpty())){
        QDomText tmp = emailid.firstChild().toText();
        tmp.setData(email);
    } else if(!emailid.hasChildNodes() && (!email.isEmpty())) {
        QDomText tmp = doc.createTextNode(email);
        emailid.appendChild(tmp);
    }

    QDomElement qual = root.elementsByTagName("qualification").at(0).toElement();
    if(qual.hasChildNodes()) {
        QDomText tmp = qual.firstChild().toText();
        tmp.setData(qualification);
    }

    QDomElement sal  = root.elementsByTagName("salary").at(0).toElement();
    if(sal.hasChildNodes()) {
        QDomText tmp = sal.firstChild().toText();
        tmp.setData(salary);
    }

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

void OfflineEmpEdit::editPayment(QString pID, QString bid, QString noa, QString accNo, QString actype,
       QString bName, QString ifsc, QString branch, QString cvv, QString expDate)
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
    MyDetail mDetail;
    if(doc.documentElement().tagName() != mDetail.getDID()) {
        QMessageBox::critical(NULL,
                              QObject::tr("File Permission Denied!"),
                              QObject::tr("<html><p>Dairy ID Changed!</p><p>"
                                          "You are using file of different dairy which is not permissible."
                                          " Please delete the required file or update settings to correct the details. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QDomElement custElem= doc.documentElement().elementsByTagName("E"+pID).at(0).toElement();
    QDomElement root;
    int biCount = custElem.elementsByTagName("bankinfo").count();
    if (biCount > 0) {
        root = custElem.elementsByTagName("bankinfo").at(0).toElement();
    } else {
        root = doc.createElement("bankinfo");
        custElem.appendChild(root);
    }

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

    root.appendChild(xbid);

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

void OfflineEmpEdit::removePayment(QString pID, QString bid)
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
    MyDetail mDetail;
    if(doc.documentElement().tagName() != mDetail.getDID()) {
        QMessageBox::critical(NULL,
                              QObject::tr("File Permission Denied!"),
                              QObject::tr("<html><p>Dairy ID Changed!</p><p>"
                                          "You are using file of different dairy which is not permissible."
                                          " Please delete the required file or update settings to correct the details. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QDomElement customer = doc.documentElement().elementsByTagName("E"+pID).at(0).toElement();
    QDomNode account = customer.elementsByTagName("B"+bid).at(0);
    QDomNode bankinfo = account.parentNode();
    bankinfo.removeChild(account);
    if(!bankinfo.hasChildNodes()){
        bankinfo.parentNode().removeChild(bankinfo);
    }

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

void OfflineEmpEdit::editDepInfo(QString eID, QString dID, QString desg, QString salary)
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
    MyDetail mDetail;
    if(doc.documentElement().tagName() != mDetail.getDID()) {
        QMessageBox::critical(NULL,
                              QObject::tr("File Permission Denied!"),
                              QObject::tr("<html><p>Dairy ID Changed!</p><p>"
                                          "You are using file of different dairy which is not permissible."
                                          " Please delete the required file or update settings to correct the details. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QDomElement root = doc.elementsByTagName("E"+eID).at(0).toElement();
    QDomElement dep = root.elementsByTagName("depid").at(0).toElement();
    QDomElement des = root.elementsByTagName("designation").at(0).toElement();
    QDomElement sal = root.elementsByTagName("salary").at(0).toElement();

    if(dep.hasChildNodes()) {
        QDomText tmp = dep.firstChild().toText();
        tmp.setData(dID);
    }
    if(des.hasChildNodes()) {
        QDomText tmp = des.firstChild().toText();
        tmp.setData(desg);
    }
    if(sal.hasChildNodes()) {
        QDomText tmp = sal.firstChild().toText();
        tmp.setData(salary);
    }

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

void OfflineEmpEdit::editSalary(QString eID, QString salary)
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
    MyDetail mDetail;
    if(doc.documentElement().tagName() != mDetail.getDID()) {
        QMessageBox::critical(NULL,
                              QObject::tr("File Permission Denied!"),
                              QObject::tr("<html><p>Dairy ID Changed!</p><p>"
                                          "You are using file of different dairy which is not permissible."
                                          " Please delete the required file or update settings to correct the details. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QDomElement root = doc.elementsByTagName("E"+eID).at(0).toElement();
    QDomElement sal = root.elementsByTagName("salary").at(0).toElement();

    if(sal.hasChildNodes()) {
        QDomText tmp = sal.firstChild().toText();
        tmp.setData(salary);
    }

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

void OfflineEmpEdit::editDesignation(QString eID, QString desg)
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
    MyDetail mDetail;
    if(doc.documentElement().tagName() != mDetail.getDID()) {
        QMessageBox::critical(NULL,
                              QObject::tr("File Permission Denied!"),
                              QObject::tr("<html><p>Dairy ID Changed!</p><p>"
                                          "You are using file of different dairy which is not permissible."
                                          " Please delete the required file or update settings to correct the details. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QDomElement root = doc.elementsByTagName("E"+eID).at(0).toElement();
    QDomElement des = root.elementsByTagName("designation").at(0).toElement();

    if(des.hasChildNodes()) {
        QDomText tmp = des.firstChild().toText();
        tmp.setData(desg);
    }

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

void OfflineEmpEdit::editDepID(QString eID, QString dID)
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
    MyDetail mDetail;
    if(doc.documentElement().tagName() != mDetail.getDID()) {
        QMessageBox::critical(NULL,
                              QObject::tr("File Permission Denied!"),
                              QObject::tr("<html><p>Dairy ID Changed!</p><p>"
                                          "You are using file of different dairy which is not permissible."
                                          " Please delete the required file or update settings to correct the details. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return;
    }

    QDomElement root = doc.elementsByTagName("E"+eID).at(0).toElement();
    QDomElement dep = root.elementsByTagName("depid").at(0).toElement();

    if(dep.hasChildNodes()) {
        QDomText tmp = dep.firstChild().toText();
        tmp.setData(dID);
    }

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
