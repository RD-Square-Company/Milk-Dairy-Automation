#include "customerofflineentry.h"
#include <QMessageBox>
#include <QDebug>
#include "../MyDetail/mydetail.h"
#include <QList>

QDomDocument CustomerOfflineEntry::doc = QDomDocument();
QDomDocument CustomerOfflineEntry::tempDoc = QDomDocument();

CustomerOfflineEntry::CustomerOfflineEntry()
{
    /*
     * empty constructor
     */
}

bool CustomerOfflineEntry::readData()
{
    QFile file("/media/rd_square/Important/Qt projects/AdditionalCustomer/xmlFiles/additionalcustomer.xml"); //file for savign additinal customers offline
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

bool CustomerOfflineEntry::readTempData()
{
    QFile file("/media/rd_square/Important/Qt projects/AdditionalCustomer/xmlFiles/tempadditionalcustomer.xml"); //file for saving additional customers temporarily
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
    tempDoc.setContent(content);
    return true;
}

bool CustomerOfflineEntry::readLog()
{
    QFile file("/media/rd_square/Important/Qt projects/AdditionalCustomer/xmlFiles/addcustlog.xml");
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

bool CustomerOfflineEntry::readTempLog()
{
    QFile file("/media/rd_square/Important/Qt projects/AdditionalCustomer/xmlFiles/tempaddcustlog.xml"); //file for saving additional customers temporarily
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
    tempDoc.setContent(content);
    return true;
}

bool CustomerOfflineEntry::saveData()
{
    QFile file("/media/rd_square/Important/Qt projects/AdditionalCustomer/xmlFiles/additionalcustomer.xml"); //file to saving additional customers offline
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

bool CustomerOfflineEntry::saveTempData()
{
    QFile file("/media/rd_square/Important/Qt projects/AdditionalCustomer/xmlFiles/tempadditionalcustomer.xml"); //file to saving additional customer temporarily
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
    QByteArray content = tempDoc.toByteArray();
    file.write(content);
    file.close();
    return true;
}

bool CustomerOfflineEntry::saveLog()
{
    QFile file("/media/rd_square/Important/Qt projects/AdditionalCustomer/xmlFiles/addcustlog.xml");
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

bool CustomerOfflineEntry::saveTempLog()
{
    QFile file("/media/rd_square/Important/Qt projects/AdditionalCustomer/xmlFiles/tempaddcustlog.xml"); //file to saving additional customer temporarily
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
    QByteArray content = tempDoc.toByteArray();
    file.write(content);
    file.close();
    return true;
}

bool CustomerOfflineEntry::saveCustomer(QString mobileNo, QString name)
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
        return false;
    }
    if(doc.doctype().name() != "additionalcustomer") {
        QMessageBox::critical(NULL,
                              QObject::tr("Data File Removed!"),
                              QObject::tr("<html><p>Offline Saving Failed - File Removed!</p><p>"
                                          "Data file is removed please run update on software otherwise your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
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
        return false;
    }

    QDomElement root = doc.documentElement();
    QDomNodeList searched = root.elementsByTagName("m"+mobileNo);
    if(searched.length() != 0)
        return true;
    QDomElement newCust = doc.createElement("m"+mobileNo);
    QDomText custName = doc.createTextNode(name);
    newCust.appendChild(custName);
    root.appendChild(newCust);

    //saving data to file
    if(!saveData()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    return true;
}

bool CustomerOfflineEntry::saveTempCustomer(QString mobileNo, QString name)
{
    //reading data from file
    if(!readTempData()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    if(tempDoc.doctype().name() != "additionalcustomer") {
        QMessageBox::critical(NULL,
                              QObject::tr("Data File Removed!"),
                              QObject::tr("<html><p>Offline Saving Failed - File Removed!</p><p>"
                                          "Data file is removed please run update on software otherwise your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    MyDetail mDetail;
    if(tempDoc.documentElement().tagName() != mDetail.getDID()) {
        QMessageBox::critical(NULL,
                              QObject::tr("File Permission Denied!"),
                              QObject::tr("<html><p>Dairy ID Changed!</p><p>"
                                          "You are using file of different dairy which is not permissible."
                                          " Please delete the required file or update settings to correct the details. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }

    //reading data from file
    if(!readData()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    if(doc.doctype().name() != "additionalcustomer") {
        QMessageBox::critical(NULL,
                              QObject::tr("Data File Removed!"),
                              QObject::tr("<html><p>Offline Saving Failed - File Removed!</p><p>"
                                          "Data file is removed please run update on software otherwise your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    if(doc.documentElement().tagName() != mDetail.getDID()) {
        QMessageBox::critical(NULL,
                              QObject::tr("File Permission Denied!"),
                              QObject::tr("<html><p>Dairy ID Changed!</p><p>"
                                          "You are using file of different dairy which is not permissible."
                                          " Please delete the required file or update settings to correct the details. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }

    QDomElement root = doc.documentElement();
    QDomElement tempRoot = tempDoc.documentElement();
    QDomNodeList searched = root.elementsByTagName("m"+mobileNo);
    if(searched.length() != 0)
        return true;
    QDomNodeList tempSearched = tempRoot.elementsByTagName("m"+mobileNo);
    if(tempSearched.length() != 0)
        return true;
    QDomElement newCust = tempDoc.createElement("m"+mobileNo);
    QDomText custName = tempDoc.createTextNode(name);
    newCust.appendChild(custName);
    tempRoot.appendChild(newCust);

    //saving data to file

    if(!saveTempData()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    return true;
}

bool CustomerOfflineEntry::saveCustLog(QString custID, QString date, QString curDateTime, QString shift,
                                       QString AnimalName, QString quantity, QString price, QString isKg)
{
    if(!readLog()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    if(doc.doctype().name() != "additionalcustlog") {
        QMessageBox::critical(NULL,
                              QObject::tr("Data File Removed!"),
                              QObject::tr("<html><p>Offline Saving Failed - File Removed!</p><p>"
                                          "Data file is removed please run update on software otherwise your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
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
        return false;
    }

    QDomElement root = doc.documentElement();
    QDomNodeList custlist = root.elementsByTagName("a"+custID);
    QDomElement cust;
    QDomElement dateNode;
    if(custlist.length() == 0){
        cust = doc.createElement("a"+custID);
        dateNode = doc.createElement("d"+date);
        cust.appendChild(dateNode);
        root.appendChild(cust);
    } else {
        cust = custlist.at(0).toElement();
        QDomNodeList ifexist = cust.elementsByTagName("d"+date);
        if (ifexist.length() != 0)
            dateNode = ifexist.at(0).toElement();
        else {
            dateNode = doc.createElement("d"+date);
            cust.appendChild(dateNode);
        }
    }

    QDomElement shiftNode = doc.createElement("s"+shift);
    QDomAttr curDate = doc.createAttribute("curDateTime");
    curDate.setValue(curDateTime);
    shiftNode.setAttributeNode(curDate);

    QDomAttr animalNode  = doc.createAttribute("animal");
    animalNode.setValue(AnimalName);
    QDomAttr kgAttr = doc.createAttribute("iskg");
    kgAttr.setValue(isKg);
    shiftNode.setAttributeNode(animalNode);
    shiftNode.setAttributeNode(kgAttr);

    QDomElement quantityNode = doc.createElement("quantity");
    QDomText quantityText = doc.createTextNode(quantity);
    quantityNode.appendChild(quantityText);

    QDomElement priceNode = doc.createElement("price");
    QDomText priceText = doc.createTextNode(price);
    priceNode.appendChild(priceText);

    shiftNode.appendChild(quantityNode);
    shiftNode.appendChild(priceNode);
    dateNode.appendChild(shiftNode);

    if(!saveLog()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    return true;
}

bool CustomerOfflineEntry::saveTempCustLog(QString custID, QString date, QString curDateTime, QString shift,
                                           QString AnimalName, QString quantity, QString price, QString isKg)
{
    if(!readTempLog()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    if(tempDoc.doctype().name() != "additionalcustlog") {
        QMessageBox::critical(NULL,
                              QObject::tr("Data File Removed!"),
                              QObject::tr("<html><p>Offline Saving Failed - File Removed!</p><p>"
                                          "Data file is removed please run update on software otherwise your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    MyDetail mDetail;
    if(tempDoc.documentElement().tagName() != mDetail.getDID()) {
        QMessageBox::critical(NULL,
                              QObject::tr("File Permission Denied!"),
                              QObject::tr("<html><p>Dairy ID Changed!</p><p>"
                                          "You are using file of different dairy which is not permissible."
                                          " Please delete the required file or update settings to correct the details. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }

    QDomElement root = tempDoc.documentElement();
    QDomNodeList custlist = root.elementsByTagName("a"+custID);
    QDomElement cust;
    QDomElement dateNode;
    if(custlist.length() == 0){
        cust = tempDoc.createElement("a"+custID);
        dateNode = tempDoc.createElement("d"+date);
        cust.appendChild(dateNode);
        root.appendChild(cust);
    } else {
        cust = custlist.at(0).toElement();
        QDomNodeList ifexist = cust.elementsByTagName("d"+date);
        if (ifexist.length() != 0)
            dateNode = ifexist.at(0).toElement();
        else {
            dateNode = tempDoc.createElement("d"+date);
            cust.appendChild(dateNode);
        }
    }


    QDomElement shiftNode = tempDoc.createElement("s"+shift);
    QDomAttr curDate = tempDoc.createAttribute("curDateTime");
    curDate.setValue(curDateTime);
    shiftNode.setAttributeNode(curDate);
    QDomAttr animalNode  = tempDoc.createAttribute("animal");
    animalNode.setValue(AnimalName);
    QDomAttr kgAttr = tempDoc.createAttribute("iskg");
    kgAttr.setValue(isKg);
    shiftNode.setAttributeNode(animalNode);
    shiftNode.setAttributeNode(kgAttr);
    QDomElement quantityNode = tempDoc.createElement("quantity");
    QDomText quantityText = tempDoc.createTextNode(quantity);
    quantityNode.appendChild(quantityText);
    QDomElement priceNode = tempDoc.createElement("price");
    QDomText priceText = tempDoc.createTextNode(price);
    priceNode.appendChild(priceText);
    shiftNode.appendChild(quantityNode);
    shiftNode.appendChild(priceNode);
    dateNode.appendChild(shiftNode);

    if(!saveTempLog()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }

    return true;
}

QList<QStringList> CustomerOfflineEntry::getTempCust()
{
    //reading data from file
    if(!readTempData()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return QList<QStringList>();
    }
    if(tempDoc.doctype().name() != "additionalcustomer") {
        return QList<QStringList>();
    }
    MyDetail mDetail;
    if(tempDoc.documentElement().tagName() != mDetail.getDID()) {
        return QList<QStringList>();
    }

    QDomElement root = tempDoc.documentElement();
    QList<QStringList> custList;
    QDomNode node = root.firstChild();
    while(!node.isNull()){
        if(node.isElement()){
            QStringList singleCust;
            singleCust.append(node.toElement().tagName().right(10));
            singleCust.append(node.toElement().text());
            custList.append(singleCust);
            node = node.nextSibling();
        }
    }
    return custList;
}

bool CustomerOfflineEntry::delTempCust(QString mobileNo)
{
    //reading data from file
    if(!readTempData()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    if(tempDoc.doctype().name() != "additionalcustomer") {
        return true;
    }
    MyDetail mDetail;
    if(tempDoc.documentElement().tagName() != mDetail.getDID()) {
        return true;
    }

    QDomElement root = tempDoc.documentElement();
    QDomNode node = root.elementsByTagName("m"+mobileNo).at(0);
    root.removeChild(node);
    //saving data to file

    if(!saveTempData()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    return true;
}

QList<QStringList> CustomerOfflineEntry::getTempLog()
{
    if(!readTempLog()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return QList<QStringList>();
    }
    if(tempDoc.doctype().name() != "additionalcustlog") {
        return QList<QStringList>();
    }
    MyDetail mDetail;
    if(tempDoc.documentElement().tagName() != mDetail.getDID()) {
        return QList<QStringList>();
    }

    QDomElement root = tempDoc.documentElement();
    QDomNode node = root.firstChild();
    QList<QStringList> mainList;
    while(!node.isNull()) {
        QStringList oneEntry;
        if (node.toElement().tagName() == "aDEFAULT")
            oneEntry.append("DEFAULT");
        else
            oneEntry.append(node.toElement().tagName().right(10));
        QDomNode date = node.firstChild();
        while(!date.isNull()) {
            oneEntry.append(date.toElement().tagName().right(10));
            QDomNode shift = date.firstChild();
            while(!shift.isNull()){
                oneEntry.append(shift.toElement().tagName().right(1));
                oneEntry.append(shift.toElement().attribute("curDateTime"));
                oneEntry.append(shift.toElement().attribute("iskg"));
                oneEntry.append(shift.toElement().attribute("animal"));
                oneEntry.append(shift.firstChild().toElement().text());
                oneEntry.append(shift.firstChild().nextSibling().toElement().text());
                mainList.append(oneEntry);
                oneEntry.removeLast();
                oneEntry.removeLast();
                oneEntry.removeLast();
                oneEntry.removeLast();
                oneEntry.removeLast();
                oneEntry.removeLast();
                shift = shift.nextSibling();
            }
            oneEntry.removeLast();
            date = date.nextSibling();
        }
        node = node.nextSibling();
    }
    return mainList;
}

bool CustomerOfflineEntry::delTempLog(QString custID,QString date, QString shift, QString dateTime)
{
    if(!readTempLog()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }
    if(tempDoc.doctype().name() != "additionalcustlog") {
        return false;
    }
    MyDetail mDetail;
    if(tempDoc.documentElement().tagName() != mDetail.getDID()) {
        return false;
    }

    QDomElement root = tempDoc.documentElement();
    QDomElement dateElement = root.elementsByTagName("a"+custID).at(0).toElement().elementsByTagName("d"+date).at(0).toElement();
    QDomNodeList shiftList = dateElement.elementsByTagName("s"+shift);
    for(int i =0; i<shiftList.length(); i++){
        QDomElement element = shiftList.at(i).toElement();
        if(element.attribute("curDateTime") == dateTime){
            element.parentNode().removeChild(element);
            break;
        }
    }

    if(!saveTempLog()) {
        QMessageBox::critical(NULL,
                              QObject::tr("Offline Data Saving Failed!"),
                              QObject::tr("<html><p>File opening error!</p><p>"
                                          "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                          "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                          "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                              QMessageBox::Ok | QMessageBox::Default);
        return false;
    }

    return true;
}
