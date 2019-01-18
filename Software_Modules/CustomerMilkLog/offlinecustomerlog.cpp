#include "offlinecustomerlog.h"
#include <QMessageBox>
#include <QDebug>
#include "../MyDetail/mydetail.h"

QDomDocument OfflineCustomerLog::doc = QDomDocument();
QDomDocument OfflineCustomerLog::tempDoc = QDomDocument();

OfflineCustomerLog::OfflineCustomerLog()
{
    /*
     * empty constructor
     */
}

bool OfflineCustomerLog::readConsData()
{
    QFile file("/media/rd_square/Important/Qt projects/CustomerMilkLog/xmlFiles/consumermilklog.xml");
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

bool OfflineCustomerLog::readProdData()
{
    QFile file("/media/rd_square/Important/Qt projects/CustomerMilkLog/xmlFiles/producermilklog.xml");
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

bool OfflineCustomerLog::readTempConsData()
{
    QFile file("/media/rd_square/Important/Qt projects/CustomerMilkLog/xmlFiles/tempconsumermilklog.xml");
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

bool OfflineCustomerLog::readTempProdData()
{
    QFile file("/media/rd_square/Important/Qt projects/CustomerMilkLog/xmlFiles/tempproducermilklog.xml");
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

bool OfflineCustomerLog::saveConsData()
{
    QFile file("/media/rd_square/Important/Qt projects/CustomerMilkLog/xmlFiles/consumermilklog.xml");
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

bool OfflineCustomerLog::saveProdData()
{
    QFile file("/media/rd_square/Important/Qt projects/CustomerMilkLog/xmlFiles/producermilklog.xml");
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

bool OfflineCustomerLog::saveTempConsData()
{
    QFile file("/media/rd_square/Important/Qt projects/CustomerMilkLog/xmlFiles/tempconsumermilklog.xml");
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

bool OfflineCustomerLog::saveTempProdData()
{
    QFile file("/media/rd_square/Important/Qt projects/CustomerMilkLog/xmlFiles/tempproducermilklog.xml");
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

bool OfflineCustomerLog::saveCustLog(QString custID, QString date, QString dateTime, QString shift,
     QString milkTypeID, QString isKg, QString quantity, QString snf, QString fat, QString price, QString water)
{
    if(custID.left(2)=="MP"){
        if(!readProdData()) {
            QMessageBox::critical(NULL,
                                  QObject::tr("Offline Data Saving Failed!"),
                                  QObject::tr("<html><p>File opening error!</p><p>"
                                              "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return false;
        }
        if(doc.doctype().name() != "producermilklog") {
            QMessageBox::critical(NULL,
                                  QObject::tr("Data File Removed!"),
                                  QObject::tr("<html><p>Offline Saving Failed - File Removed!</p><p>"
                                              "Data file is removed please run update on software otherwise your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return false;
        }
    } else {
        if(!readConsData()) {
            QMessageBox::critical(NULL,
                                  QObject::tr("Offline Data Saving Failed!"),
                                  QObject::tr("<html><p>File opening error!</p><p>"
                                              "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return false;
        }
        if(doc.doctype().name() != "consumermilklog") {
            QMessageBox::critical(NULL,
                                  QObject::tr("Data File Removed!"),
                                  QObject::tr("<html><p>Offline Saving Failed - File Removed!</p><p>"
                                              "Data file is removed please run update on software otherwise your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return false;
        }
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
    QDomNodeList tempList = root.elementsByTagName(custID);
    QDomElement customer,dateNode;
    if(tempList.length()==0){
        customer = doc.createElement(custID);
        root.appendChild(customer);
    } else {
        customer = tempList.at(0).toElement();
    }
    tempList = customer.elementsByTagName("d"+date);
    if(tempList.length() == 0){
        dateNode = doc.createElement("d"+date);
        customer.appendChild(dateNode);
    } else {
        dateNode = tempList.at(0).toElement();
    }

    QDomElement shiftNode = doc.createElement("s"+shift);
    QDomAttr curDateTime = doc.createAttribute("curdatetime");
    curDateTime.setValue(dateTime);
    QDomAttr iskgAttr = doc.createAttribute("iskg");
    iskgAttr.setValue(isKg);
    QDomAttr milkTypeAttr = doc.createAttribute("milktypeid");
    milkTypeAttr.setValue(milkTypeID);
    shiftNode.setAttributeNode(curDateTime);
    shiftNode.setAttributeNode(iskgAttr);
    shiftNode.setAttributeNode(milkTypeAttr);
    dateNode.appendChild(shiftNode);

    QDomElement quantityNode = doc.createElement("quantity");
    QDomText quantityText = doc.createTextNode(quantity);
    quantityNode.appendChild(quantityText);
    QDomElement fatNode = doc.createElement("fat");
    QDomText fatText = doc.createTextNode(fat);
    fatNode.appendChild(fatText);
    QDomElement snfNode = doc.createElement("snf");
    QDomText snfText = doc.createTextNode(snf);
    snfNode.appendChild(snfText);
    QDomElement priceNode = doc.createElement("price");
    QDomText priceText = doc.createTextNode(price);
    priceNode.appendChild(priceText);
    QDomElement waterNode = doc.createElement("water");
    QDomText waterText = doc.createTextNode(water);
    waterNode.appendChild(waterText);

    shiftNode.appendChild(quantityNode);
    shiftNode.appendChild(fatNode);
    shiftNode.appendChild(snfNode);
    shiftNode.appendChild(priceNode);
    shiftNode.appendChild(waterNode);

    if(custID.left(2) == "MP"){
        if(!saveProdData()) {
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
    } else {
        if(!saveConsData()) {
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
}

bool OfflineCustomerLog::saveTempCustLog(QString custID, QString date, QString dateTime, QString shift, QString milkTypeID, QString isKg, QString quantity, QString snf, QString fat, QString price, QString water)
{
    if(custID.left(2)=="MP"){
        if(!readTempProdData()) {
            QMessageBox::critical(NULL,
                                  QObject::tr("Offline Data Saving Failed!"),
                                  QObject::tr("<html><p>File opening error!</p><p>"
                                              "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return false;
        }
        if(tempDoc.doctype().name() != "producermilklog") {
            QMessageBox::critical(NULL,
                                  QObject::tr("Data File Removed!"),
                                  QObject::tr("<html><p>Offline Saving Failed - File Removed!</p><p>"
                                              "Data file is removed please run update on software otherwise your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return false;
        }
    } else {
        if(!readTempConsData()) {
            QMessageBox::critical(NULL,
                                  QObject::tr("Offline Data Saving Failed!"),
                                  QObject::tr("<html><p>File opening error!</p><p>"
                                              "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return false;
        }
        if(tempDoc.doctype().name() != "consumermilklog") {
            QMessageBox::critical(NULL,
                                  QObject::tr("Data File Removed!"),
                                  QObject::tr("<html><p>Offline Saving Failed - File Removed!</p><p>"
                                              "Data file is removed please run update on software otherwise your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return false;
        }
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
    QDomNodeList tempList = root.elementsByTagName(custID);
    QDomElement customer,dateNode;
    if(tempList.length()==0){
        customer = tempDoc.createElement(custID);
        root.appendChild(customer);
    } else {
        customer = tempList.at(0).toElement();
    }
    tempList = customer.elementsByTagName("d"+date);
    if(tempList.length() == 0){
        dateNode = tempDoc.createElement("d"+date);
        customer.appendChild(dateNode);
    } else {
        dateNode = tempList.at(0).toElement();
    }

    QDomElement shiftNode = tempDoc.createElement("s"+shift);
    QDomAttr curDateTime = tempDoc.createAttribute("curdatetime");
    curDateTime.setValue(dateTime);
    QDomAttr iskgAttr = tempDoc.createAttribute("iskg");
    iskgAttr.setValue(isKg);
    QDomAttr milkTypeAttr = tempDoc.createAttribute("milktypeid");
    milkTypeAttr.setValue(milkTypeID);
    shiftNode.setAttributeNode(curDateTime);
    shiftNode.setAttributeNode(iskgAttr);
    shiftNode.setAttributeNode(milkTypeAttr);
    dateNode.appendChild(shiftNode);

    QDomElement quantityNode = tempDoc.createElement("quantity");
    QDomText quantityText = tempDoc.createTextNode(quantity);
    quantityNode.appendChild(quantityText);
    QDomElement fatNode = tempDoc.createElement("fat");
    QDomText fatText = tempDoc.createTextNode(fat);
    fatNode.appendChild(fatText);
    QDomElement snfNode = tempDoc.createElement("snf");
    QDomText snfText = tempDoc.createTextNode(snf);
    snfNode.appendChild(snfText);
    QDomElement priceNode = tempDoc.createElement("price");
    QDomText priceText = tempDoc.createTextNode(price);
    priceNode.appendChild(priceText);
    QDomElement waterNode = tempDoc.createElement("water");
    QDomText waterText = tempDoc.createTextNode(water);
    waterNode.appendChild(waterText);

    shiftNode.appendChild(quantityNode);
    shiftNode.appendChild(fatNode);
    shiftNode.appendChild(snfNode);
    shiftNode.appendChild(priceNode);
    shiftNode.appendChild(waterNode);

    if(custID.left(2) == "MP"){
        if(!saveTempProdData()) {
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
    } else {
        if(!saveTempConsData()) {
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
}

QList<QStringList> OfflineCustomerLog::getTempLog(QString custType)
{
    if(custType=="Producer"){
        if(!readTempProdData()) {
            QMessageBox::critical(NULL,
                                  QObject::tr("Offline Data Saving Failed!"),
                                  QObject::tr("<html><p>File opening error!</p><p>"
                                              "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return QList<QStringList>();
        }
        if(tempDoc.doctype().name() != "producermilklog") {
            return QList<QStringList>();
        }
    } else {
        if(!readTempConsData()) {
            QMessageBox::critical(NULL,
                                  QObject::tr("Offline Data Saving Failed!"),
                                  QObject::tr("<html><p>File opening error!</p><p>"
                                              "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return QList<QStringList>();
        }
        if(tempDoc.doctype().name() != "consumermilklog") {
            return QList<QStringList>();
        }
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
        oneEntry.append(node.toElement().tagName());
        QDomNode date = node.firstChild();
        while(!date.isNull()) {
            oneEntry.append(date.toElement().tagName().right(10));
            QDomNode shift = date.firstChild();
            while(!shift.isNull()){
                oneEntry.append(shift.toElement().tagName().right(1));
                oneEntry.append(shift.toElement().attribute("curdatetime"));
                oneEntry.append(shift.toElement().attribute("iskg"));
                oneEntry.append(shift.toElement().attribute("milktypeid"));
                QDomNode tempNode = shift.firstChild();
                for (int cust=0;cust<5;cust++) {
                    oneEntry.append(tempNode.toElement().text());
                    tempNode = tempNode.nextSibling();
                }
                mainList.append(oneEntry);
                for(int cust=0;cust<5;cust++){
                    oneEntry.removeLast();
                }
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

bool OfflineCustomerLog::delTempLog(QString custID, QString date, QString dateTime, QString shift)
{
    if(custID.left(2)=="MP"){
        if(!readTempProdData()) {
            QMessageBox::critical(NULL,
                                  QObject::tr("Offline Data Saving Failed!"),
                                  QObject::tr("<html><p>File opening error!</p><p>"
                                              "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return false;
        }
        if(tempDoc.doctype().name() != "producermilklog") {
            return true;
        }
    } else {
        if(!readTempConsData()) {
            QMessageBox::critical(NULL,
                                  QObject::tr("Offline Data Saving Failed!"),
                                  QObject::tr("<html><p>File opening error!</p><p>"
                                              "Your data is not saved offline due to some internal file error. Your application my misbehave when "
                                              "you will be offline. Please contact us on 7568577487 or visit us on www.mdsonline.co.in for further help.</p><p>For further detail and help, please contact us on +7568577487 or visit us on "
                                              "<a>www.mdssystemonline.co.in</a>.</p><p>Thank You</p></html>"),
                                  QMessageBox::Ok | QMessageBox::Default);
            return false;
        }
        if(tempDoc.doctype().name() != "consumermilklog") {
            return true;
        }
    }

    MyDetail mDetail;
    if(tempDoc.documentElement().tagName() != mDetail.getDID()) {
        return true;
    }


    QDomElement root = tempDoc.documentElement();
    QDomElement dateElement = root.elementsByTagName(custID).at(0).toElement().elementsByTagName("d"+date).at(0).toElement();
    QDomNodeList shiftList = dateElement.elementsByTagName("s"+shift);
    for(int i =0; i<shiftList.length(); i++){
        QDomElement element = shiftList.at(i).toElement();
        if(element.attribute("curdatetime") == dateTime){
            element.parentNode().removeChild(element);
            break;
        }
    }

    if(custID.left(2) == "MP"){
        if(!saveTempProdData()) {
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
    } else {
        if(!saveTempConsData()) {
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
}
