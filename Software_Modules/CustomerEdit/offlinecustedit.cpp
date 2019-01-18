#include "offlinecustedit.h"
#include <QMessageBox>
#include <QDebug>
#include "../MyDetail/mydetail.h"

QDomDocument OfflineCustEdit::doc = QDomDocument();

OfflineCustEdit::OfflineCustEdit()
{
    /*
     * empty constructor
     */
}

bool OfflineCustEdit::readData()
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

bool OfflineCustEdit::saveData()
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

void OfflineCustEdit::editGeneral(QString cID, QString isApp,QString fName, QString mName,
        QString lName, QString pC, QString sC, QString street, QString city, QString state, QString pin,
        QString email)
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

    QDomElement root = doc.elementsByTagName(cID).at(0).toElement();
    if(root.hasAttribute("id")) {
        root.setAttribute("id", isApp);
    }

    QDomElement fna = root.elementsByTagName("first").at(0).toElement();
    if(fna.hasChildNodes()) {
        QDomText fn = fna.firstChild().toText();
        fn.setData(fName);
    }
    QDomElement mna = root.elementsByTagName("middle").at(0).toElement();
    if(mna.hasChildNodes()) {
        QDomText fn = mna.firstChild().toText();
        fn.setData(mName);
    } else {
        QDomText tmp = doc.createTextNode(mName);
        mna.appendChild(tmp);
    }
    QDomElement lna = root.elementsByTagName("last").at(0).toElement();
    if(lna.hasChildNodes()) {
        QDomText fn = lna.firstChild().toText();
        fn.setData(lName);
    } else {
        QDomText tmp = doc.createTextNode(lName);
        lna.appendChild(tmp);
    }

    QDomElement pce = root.elementsByTagName("primary").at(0).toElement();
    if(pce.hasChildNodes()) {
        QDomText tmp = pce.firstChild().toText();
        tmp.setData(pC);
    }

    QDomElement sce = root.elementsByTagName("secondary").at(0).toElement();
    if(sce.hasChildNodes()) {
        QDomText tmp = sce.firstChild().toText();
        tmp.setData(sC);
    } else {
        QDomText tmp = doc.createTextNode(sC);
        sce.appendChild(tmp);
    }

    QDomElement str = root.elementsByTagName("street").at(0).toElement();
    if(str.hasChildNodes()) {
        QDomText tmp = str.firstChild().toText();
        tmp.setData(street);
    }

    QDomElement ct = root.elementsByTagName("city").at(0).toElement();
    if(ct.hasChildNodes()) {
        QDomText tmp = ct.firstChild().toText();
        tmp.setData(city);
    }

    QDomElement stt = root.elementsByTagName("state").at(0).toElement();
    if(stt.hasChildNodes()) {
        QDomText tmp = stt.firstChild().toText();
        tmp.setData(state);
    }

    QDomElement pcd = root.elementsByTagName("pincode").at(0).toElement();
    if(pcd.hasChildNodes()) {
        QDomText tmp = pcd.firstChild().toText();
        tmp.setData(pin);
    }

    QDomElement em = root.elementsByTagName("email").at(0).toElement();
    if(em.hasChildNodes()) {
        QDomText tmp = em.firstChild().toText();
        tmp.setData(email);
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

void OfflineCustEdit::editPayment(QString cID, QString bid, QString noa, QString accNo, QString actype, QString bName,
        QString ifsc, QString branch, QString cvv, QString expDate)
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

    QDomElement custElem= doc.documentElement().elementsByTagName(cID).at(0).toElement();
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


void OfflineCustEdit::removePayment(QString cID, QString bid)
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

    QDomElement customer = doc.documentElement().elementsByTagName(cID).at(0).toElement();
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
