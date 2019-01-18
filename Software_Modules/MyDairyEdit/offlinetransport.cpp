#include "offlinetransport.h"
#include <QMessageBox>
#include <QDebug>
#include "../MyDetail/mydetail.h"

QDomDocument OfflineTransport::doc = QDomDocument();

OfflineTransport::OfflineTransport()
{
    /*
     * empty constructor
     */
}

bool OfflineTransport::readData()
{
    QFile file("/media/rd_square/Important/Qt projects/MyDairyEdit/documents/transportregistration.xml");
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

bool OfflineTransport::saveData()
{
    QFile file("/media/rd_square/Important/Qt projects/MyDairyEdit/documents/transportregistration.xml");
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

void OfflineTransport::registerOffline(QString tID, QString fName, QString mName, QString lName,
                                       QString pc, QString sc, QString lic, QString veh)
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
    if(doc.doctype().name() != "transportinfo") {
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
    QDomElement transID = doc.createElement("T"+tID);

    QDomElement name = doc.createElement("name");
    QDomElement first = doc.createElement("first");
    QDomElement middle = doc.createElement("middle");
    QDomElement last = doc.createElement("last");

    QDomText fn = doc.createTextNode(fName);
    QDomText mn = doc.createTextNode(mName);
    QDomText ln = doc.createTextNode(lName);

    first.appendChild(fn);
    middle.appendChild(mn);
    last.appendChild(ln);

    name.appendChild(first);
    name.appendChild(middle);
    name.appendChild(last);

    QDomElement contact  = doc.createElement("contact");
    QDomElement primary = doc.createElement("primary");
    QDomElement secondary = doc.createElement("secondary");

    QDomText p = doc.createTextNode(pc);
    QDomText s = doc.createTextNode(sc);

    primary.appendChild(p);
    secondary.appendChild(s);
    contact.appendChild(primary);
    contact.appendChild(secondary);

    QDomElement license = doc.createElement("license");
    QDomText tlic = doc.createTextNode(lic);
    license.appendChild(tlic);

    QDomElement vehical = doc.createElement("vehical");
    QDomText tveh = doc.createTextNode(veh);
    vehical.appendChild(tveh);

    transID.appendChild(name);
    transID.appendChild(contact);
    transID.appendChild(license);
    transID.appendChild(vehical);
    fragment.appendChild(transID);
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

void OfflineTransport::editOffline(QString tID, QString fName, QString mName, QString lName,
                                   QString pc, QString sc, QString lic, QString veh)
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
    if(doc.doctype().name() != "transportinfo") {
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

    QDomElement transID = root.elementsByTagName("T"+tID).at(0).toElement();

    QDomElement first = transID.elementsByTagName("first").at(0).toElement();
    if(first.hasChildNodes()) {
        QDomText tmp = first.firstChild().toText();
        tmp.setData(fName);
    }

    QDomElement middle = transID.elementsByTagName("middle").at(0).toElement();
    if(middle.hasChildNodes()) {
        QDomText tmp = middle.firstChild().toText();
        tmp.setData(mName);
    } else {
        QDomText tmp = doc.createTextNode(mName);
        middle.appendChild(tmp);
    }

    QDomElement last = transID.elementsByTagName("last").at(0).toElement();
    if(last.hasChildNodes()) {
        QDomText tmp = last.firstChild().toText();
        tmp.setData(lName);
    } else {
        QDomText tmp = doc.createTextNode(lName);
        last.appendChild(tmp);
    }

    QDomElement primary = transID.elementsByTagName("primary").at(0).toElement();
    if(primary.hasChildNodes()) {
        QDomText tmp = primary.firstChild().toText();
        tmp.setData(pc);
    }

    QDomElement secondary = transID.elementsByTagName("secondary").at(0).toElement();
    if(secondary.hasChildNodes()) {
        QDomText tmp  = secondary.firstChild().toText();
        tmp.setData(sc);
    } else {
        QDomText tmp = doc.createTextNode(sc);
        secondary.appendChild(tmp);
    }

    QDomElement license = transID.elementsByTagName("license").at(0).toElement();
    if(license.hasChildNodes()) {
        QDomText tmp = license.firstChild().toText();
        tmp.setData(lic);
    } else {
        QDomText tmp = doc.createTextNode(lic);
        license.appendChild(tmp);
    }

    QDomElement vehical = transID.elementsByTagName("vehical").at(0).toElement();
    if(vehical.hasChildNodes()) {
        QDomText tmp = vehical.firstChild().toText();
        tmp.setData(veh);
    } else {
        QDomText tmp = doc.createTextNode(veh);
        vehical.appendChild(tmp);
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
