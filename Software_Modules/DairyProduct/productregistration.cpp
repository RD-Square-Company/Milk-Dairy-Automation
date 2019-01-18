#include "productregistration.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTimer>

ProductRegistration::ProductRegistration(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    //loading initializing
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //setting connetions of buttons in widget
    connect(pTypeBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(productTypeChanged(int)));
    connect(weighBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(WeightTypeChanged(int)));
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    connect(registerButton, SIGNAL(clicked(bool)),
            this, SLOT(registerPressed()));
    connect(packBox,SIGNAL(currentIndexChanged(int)),
            this, SLOT(packingChange(int)));
    connect(pNameEdit, SIGNAL(textChanged(QString)),
            this, SLOT(generateID()));
    connect(pIDEdit,SIGNAL(textEdited(QString)),
            this, SLOT(setProductID()));
    connect(others, SIGNAL(clicked(bool)),
            this, SLOT(showSpecify(bool)));
    connect(gstBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(gstChanged(int)));

    idLabel->installEventFilter(this);

    //calling set widget
    setWidgets();
}

void ProductRegistration::setWidgets()
{
    setDefault();
    emit pTypeBox->currentIndexChanged(0);
    emit weighBox->currentIndexChanged(0);

    //setting stylesheet to all line edit
    pNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    bNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pIDEdit->setStyleSheet(gDetail.getNormalStylesheet());
    priceEdit->setStyleSheet(gDetail.getNormalStylesheet());
    quantityEdit->setStyleSheet(gDetail.getNormalStylesheet());
    colorEdit->setStyleSheet(gDetail.getNormalStylesheet());
    shopEdit->setStyleSheet(gDetail.getNormalStylesheet());
    specifyEdit->setStyleSheet(gDetail.getNormalStylesheet());

    //setting validator to line edit
    QRegExp nameEdit("[a-zA-Z]{1,15}[ ][a-zA-Z]{1,15}[ ][a-zA-Z]{1,15}");
    QRegExpValidator *nameValidator =  new QRegExpValidator(nameEdit, this);
    pNameEdit->setValidator(nameValidator);
    bNameEdit->setValidator(nameValidator);

    QRegExp idExp("[a-zA-Z0-9]{5}");
    QRegExpValidator *idValidator = new QRegExpValidator(idExp, this);
    pIDEdit->setValidator(idValidator);

    QRegExp priceExp("[0-9]{1,5}[.][0-9]{2}");
    QRegExpValidator *priceValidator = new QRegExpValidator(priceExp, this);
    priceEdit->setValidator(priceValidator);
    quantityEdit->setValidator(priceValidator);

    QRegExp colorExp("[a-zA-Z ]{15}");
    QRegExpValidator *colorValidator = new QRegExpValidator(colorExp, this);
    colorEdit->setValidator(colorValidator);
}

void ProductRegistration::setProductID()
{
    pIDEdit->setText(pIDEdit->text().toUpper());
}

void ProductRegistration::generateID()
{
    QString tempID ;
    if(!pNameEdit->text().isEmpty()){
        tempID = pNameEdit->text().at(0).toUpper();
    }
    if(!pNameEdit->text().isEmpty()){
        int wc = (int)pNameEdit->text().length()/2;
        if(pNameEdit->text().length() > 2) {
            if(pNameEdit->text().at(wc) == ' '){
                wc--;
            }
            tempID += pNameEdit->text().at(wc).toUpper();
        }

    }
    if(!pNameEdit->text().isEmpty()){
        if(pNameEdit->text().at(pNameEdit->text().length()-1) != ' '){
            tempID += pNameEdit->text().at(pNameEdit->text().length()-1).toUpper();
        } else if(pNameEdit->text().length() > 1){
            tempID += pNameEdit->text().at(pNameEdit->text().length()-2).toUpper();
        }
    }

    idLabel->setText(tempID);
}

void ProductRegistration::productTypeChanged(int ind)
{
    setDefault();
    if(ind == 0) {
        pNameLabel->hide();
        pNameEdit->hide();
        bnLabel->hide();
        bNameEdit->hide();
        pidLabel->hide();
        pIDEdit->hide();
        sidLabel->hide();
        idLabel->hide();
        ptypeLabel->hide();
        packBox->hide();
        wtypeLabel->hide();
        weighBox->hide();
        priceLabel->hide();
        priceEdit->hide();
        rsEdit->hide();
        quantityLabel->hide();
        quantityEdit->hide();
        kgLabel->hide();
        appLabel->hide();
        appBox->hide();
        colorLabel->hide();
        colorEdit->hide();
        shopLabel->hide();
        shopEdit->hide();
        ingLabel->hide();
        ingEdit->hide();
        medicineLabel->hide();
        buffalo->hide();
        cow->hide();
        others->hide();
        specifyEdit->hide();
        descLabel->hide();
        descEdit->hide();
        registerButton->hide();
        gstLabel->hide();
        gstBox->hide();
        cLabel->hide();
        iLabel->hide();
        cgst->hide();
        igst->hide();
    } else if(ind == 1) {
        pNameLabel->show();
        pNameEdit->show();
        bnLabel->show();
        bNameEdit->show();
        pidLabel->show();
        pIDEdit->show();
        sidLabel->show();
        idLabel->show();
        ptypeLabel->show();
        packBox->show();
        wtypeLabel->show();
        weighBox->show();
        appLabel->hide();
        appBox->hide();
        colorLabel->show();
        colorEdit->show();
        shopLabel->hide();
        shopEdit->hide();
        ingLabel->show();
        ingEdit->show();
        medicineLabel->hide();
        buffalo->hide();
        cow->hide();
        others->hide();
        specifyEdit->hide();
        descLabel->show();
        descEdit->show();
        registerButton->show();
        ingLabel->setText(tr("Ingredients:"));
        gstLabel->show();
        gstBox->show();
    } else if (ind == 2) {
        pNameLabel->show();
        pNameEdit->show();
        bnLabel->show();
        bNameEdit->show();
        pidLabel->show();
        pIDEdit->show();
        sidLabel->show();
        idLabel->show();
        ptypeLabel->show();
        packBox->show();
        wtypeLabel->show();
        weighBox->show();
        appLabel->show();
        appBox->show();
        colorLabel->hide();
        colorEdit->hide();
        shopLabel->hide();
        shopEdit->hide();
        ingLabel->show();
        ingEdit->show();
        medicineLabel->hide();
        buffalo->hide();
        cow->hide();
        others->hide();
        specifyEdit->hide();
        descLabel->show();
        descEdit->show();
        registerButton->show();
        ingLabel->setText(tr("Ingredients:"));
        gstLabel->show();
        gstBox->show();
    } else if (ind == 3) {
        pNameLabel->show();
        pNameEdit->show();
        bnLabel->show();
        bNameEdit->show();
        pidLabel->show();
        pIDEdit->show();
        sidLabel->show();
        idLabel->show();
        ptypeLabel->show();
        packBox->show();
        wtypeLabel->show();
        weighBox->show();
        appLabel->show();
        appBox->show();
        colorLabel->hide();
        colorEdit->hide();
        shopLabel->show();
        shopEdit->show();
        ingLabel->hide();
        ingEdit->hide();
        medicineLabel->show();
        buffalo->show();
        cow->show();
        others->show();
        specifyEdit->hide();
        descLabel->show();
        descEdit->show();
        registerButton->show();
        gstLabel->show();
        gstBox->show();
    } else {
        pNameLabel->show();
        pNameEdit->show();
        bnLabel->show();
        bNameEdit->show();
        pidLabel->show();
        pIDEdit->show();
        sidLabel->show();
        idLabel->show();
        ptypeLabel->show();
        packBox->show();
        wtypeLabel->show();
        weighBox->show();
        appLabel->hide();
        appBox->hide();
        colorLabel->show();
        colorEdit->show();
        shopLabel->hide();
        shopEdit->hide();
        ingLabel->show();
        ingEdit->show();
        medicineLabel->hide();
        buffalo->hide();
        cow->hide();
        others->hide();
        specifyEdit->hide();
        descLabel->show();
        descEdit->show();
        registerButton->show();
        ingLabel->setText(tr("Plant Name: "));
        gstLabel->show();
        gstBox->show();
    }
}

void ProductRegistration::WeightTypeChanged(int ind)
{
    if (ind==0){
        kgLabel->setText("");
    } else if(ind==1){
        kgLabel->setText(tr("Kg"));
    } else {
        kgLabel->setText(tr("Litre"));
    }
}

void ProductRegistration::packingChange(int ind)
{
    if (ind == 0) {
        priceLabel->hide();
        priceEdit->hide();
        rsEdit->hide();
        quantityLabel->hide();
        quantityEdit->hide();
        kgLabel->hide();
        weighBox->setEnabled(true);
        weighBox->setCurrentIndex(0);
    } else if(ind==1) {
        priceLabel->show();
        priceEdit->show();
        rsEdit->hide();
        quantityLabel->hide();
        quantityEdit->hide();
        kgLabel->hide();
        weighBox->setCurrentIndex(1);
        weighBox->setEnabled(false);
        priceLabel->setText(tr("<html>Price on per kg:<font  color=\"red\">*</font></html>"));
        rsEdit->show();
    } else{
        priceLabel->show();
        priceEdit->show();
        rsEdit->show();
        quantityLabel->show();
        quantityEdit->show();
        kgLabel->show();
        weighBox->setEnabled(true);
        weighBox->setCurrentIndex(0);
        priceLabel->setText(tr("<html>Price on per %1:<font  color=\"red\">*</font></html>").arg(packBox->currentText()));
        quantityLabel->setText(tr("<html>Quantity on per %1:<font  color=\"red\">*</font></html>").arg(packBox->currentText()));
    }
}

void ProductRegistration::setDefault()
{
    //setting value to default of all child widgets
    pNameEdit->setText("");
    bNameEdit->setText("");
    idLabel->setText("");
    pIDEdit->setText("");
    packBox->setCurrentIndex(0);
    weighBox->setCurrentIndex(0);
    priceEdit->setText("");
    quantityEdit->setText("");
    appBox->setCurrentIndex(0);
    colorEdit->setText("");
    shopEdit->setText("");
    ingEdit->setText("");
    buffalo->setChecked(false);
    cow->setChecked(false);
    others->setChecked(false);
    specifyEdit->setText("");
    descEdit->setText("");
    gstBox->setCurrentIndex(0);
}

void ProductRegistration::registerPressed()
{
    rLoad(1);
    QString error;
    if(others->isChecked() && (pTypeBox->currentIndex()==3) ){
        if(specifyEdit->text().isEmpty()){
            error = tr("Please specify other animal names");
            specifyEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    }
    if(!(((buffalo->isChecked()) || cow->isChecked()) || others->isChecked())) {
        if(pTypeBox->currentIndex() == 3){
            error= tr("Please select animal for medicine");
        }
    }
    if(shopEdit->text().isEmpty() && (pTypeBox->currentIndex()==3)){
        error = tr("Please select shop from where product is brought.");
        shopEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(gstBox->currentIndex() == 0){
        error = tr("Please select gst on product.");
    }
    if(appBox->currentIndex() == 0 && (pTypeBox->currentIndex()==3  || pTypeBox->currentIndex()==2)){
        error= tr("Please select apperance of product.");
    }
    if(weighBox->currentIndex()==0){
        error = tr("Please select weight");
    }
    if(packBox->currentIndex() == 0) {
        error = tr("Please select packing type of product");
    } else  if (packBox->currentIndex() > 1){
        if(quantityEdit->text().isEmpty()){
            error = tr("Please enter quantity on per %1 of product.").arg(packBox->currentText());
            quantityEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
        if(priceEdit->text().isEmpty()){
            error = tr("Please enter price of %1 of product").arg(packBox->currentText());
            priceEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    } else {
        if(priceEdit->text().isEmpty()){
            error = tr("Please enter price of %1 of product").arg(packBox->currentText());
            priceEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    }
    if(pIDEdit->text().isEmpty() && pIDEdit->text().length() < 3){
        error = tr("Please enter valid product id. Product id must consist of 3 or more letters.");
        pIDEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(pNameEdit->text().isEmpty()){
        error = tr("Please enter Product name.");
        pNameEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }

    if(!error.isEmpty()) {
        rLoad(0);
        QMessageBox::information(this,
                                 tr("Error encountered! - %1").arg(qApp->applicationName()),
                                 tr("<html><p>Error Encountered!</p>"
                                    "<p>%1</p></html>").arg(error),
                                 QMessageBox::Ok |  QMessageBox::Default);
        return;
    }

    if(!saveData()) {
        return;
    }
    QTimer::singleShot(2000, this,SLOT(showMessage()));
}

void ProductRegistration::showMessage()
{
    rLoad(0);
    setDefault();
    QMessageBox::information(this,
                             tr("Product Registration Complete! - %1").arg(qApp->applicationName()),
                             tr("<html><p>Product Registration Completed!<p>"
                                "<p>%1 is registered on dairy with id %1 and GST %2.").arg(pNameEdit->text()).arg(gstBox->currentText()),
                             QMessageBox::Ok|QMessageBox::Default);
    disconnectDatabase();
}

void ProductRegistration::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("dairyProduct");
}

bool ProductRegistration::connectDatabase()
{
    if(!myDatabase.contains("dairyProduct")) {
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "dairyProduct");
        myDatabase.setHostName(oDetail.getHostName());
        myDatabase.setDatabaseName(oDetail.getDatabase());
        myDatabase.setUserName(oDetail.getUserName());
        myDatabase.setPassword(oDetail.getUserPass());
        myDatabase.setPort(3306);
    }
  retry:
    if(!myDatabase.open()){
        int result = QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service. "
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(myDatabase.lastError().nativeErrorCode()),
                              tr("&Exit"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry;
        else{
            return false;
    }
 }
    return true;
}

void ProductRegistration::cancelPressed()
{
    disconnectDatabase();
    this->close();
}

ProductRegistration::~ProductRegistration()
{
    disconnectDatabase();
}

bool ProductRegistration::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == idLabel && event->type() == QEvent::MouseButtonPress){
        QMouseEvent* me = static_cast<QMouseEvent*>(event);
        if(me->button() == Qt::LeftButton){
            pIDEdit->setText(idLabel->text());
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void ProductRegistration::showSpecify(bool checked)
{
    if(checked){
        specifyEdit->show();
    } else {
        specifyEdit->hide();
    }
}

void ProductRegistration::gstChanged(int ind)
{
    if(ind==0){
        cLabel->hide();
        iLabel->hide();
        cgst->hide();
        igst->hide();
    } else {
        cLabel->show();
        iLabel->show();
        cgst->show();
        igst->show();

        QString ts = gstBox->currentText();
        if (ts.contains("%")){
            ts.remove("%");
        }
        int temp = ts.toInt();
        cgst->setText(tr("%1%").arg(QString::number(((double)temp)/2)));
        igst->setText(tr("%1%").arg(QString::number(((double)temp)/2)));
    }
}

void ProductRegistration::rLoad(int i)
{
    if(i ==1){
        pTypeBox->setEnabled(false);
        pNameEdit->setEnabled(false);
        bNameEdit->setEnabled(false);
        pIDEdit->setEnabled(false);
        packBox->setEnabled(false);
        weighBox->setEnabled(false);
        priceEdit->setEnabled(false);
        quantityEdit->setEnabled(false);
        appBox->setEnabled(false);
        colorEdit->setEnabled(false);
        shopEdit->setEnabled(false);
        ingEdit->setEnabled(false);
        buffalo->setEnabled(false);
        cow->setEnabled(false);
        others->setEnabled(false);
        descEdit->setEnabled(false);
        cancelButton->setEnabled(false);
        registerButton->setEnabled(false);
        gstLabel->setEnabled(false);
        gstBox->setEnabled(false);
        cgst->setEnabled(false);
        igst->setEnabled(false);
        cLabel->setEnabled(false);
        iLabel->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 - 64;
        loadingLabel->setGeometry(x, y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        pTypeBox->setEnabled(true);
        pNameEdit->setEnabled(true);
        bNameEdit->setEnabled(true);
        pIDEdit->setEnabled(true);
        packBox->setEnabled(true);
        weighBox->setEnabled(true);
        priceEdit->setEnabled(true);
        quantityEdit->setEnabled(true);
        appBox->setEnabled(true);
        colorEdit->setEnabled(true);
        shopEdit->setEnabled(true);
        ingEdit->setEnabled(true);
        buffalo->setEnabled(true);
        cow->setEnabled(true);
        others->setEnabled(true);
        descEdit->setEnabled(true);
        cancelButton->setEnabled(true);
        registerButton->setEnabled(true);
        gstLabel->setEnabled(true);
        gstBox->setEnabled(true);
        cgst->setEnabled(true);
        igst->setEnabled(true);
        cLabel->setEnabled(true);
        iLabel->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}

bool ProductRegistration::saveData()
{
    QString product = "INSERT INTO Product(ProductID, ProductName, BrandName, Price, Quantity,"
                      " PackTypeID, ProductCatID, WTID, Decription, LocalDID) VALUES ('" +
            pIDEdit->text()+"','"+pNameEdit->text()+"','"+bNameEdit->text()+"',"+priceEdit->text()+","+
            quantityEdit->text()+","+QString::number(packBox->currentIndex())+","+QString::number(pTypeBox->currentIndex())+","+QString::number(weighBox->currentIndex())+",'"+
            descEdit->toPlainText() +"','" + mDetail.getDID()+"');";

    if(!myDatabase.isOpen()) {
        rLoad(0);
        if(!connectDatabase()) {
            return false;
        }
        rLoad(1);
    }

    QSqlQuery query(myDatabase);
    if(!query.exec(product)){
        rLoad(0);
        if(query.lastError().nativeErrorCode() == "1062"){
            QMessageBox::information(this,
                                     tr("Product id Exist! - %1").arg(qApp->applicationName()),
                                     tr("<html><p>Product ID Exist!</p>"
                                        "<p>Product with Product ID %1 already exist please change id of product.</p></html>").arg(pIDEdit->text()),
                                     QMessageBox::Ok|QMessageBox::Default);
            return false;
        } else {
            QMessageBox::information(this,
                                     tr("Product Registratin Error! - %1").arg(qApp->applicationName()),
                                     tr("<html><p>Connection Problem!</p>"
                                        "<p>Please try after some time.</p></html>"),
                                     QMessageBox::Ok|QMessageBox::Default);
            return false;
        }
    }

    QString productType;
    int in = pTypeBox->currentIndex();
    if (in ==1){
        productType = "INSERT INTO HumanFood(ProductID, Color, Ingredients, LocalDID) VALUES ('"+
                pIDEdit->text()+"','"+ colorEdit->text()+"','"+ingEdit->toPlainText()+"','"+
                mDetail.getDID()+"');";
    } else if(in==2) {
        productType= "INSERT INTO AnimalFood(ProductID, Appearance, Ingredients, LocalDID) VALUES ('"+
                pIDEdit->text()+"','"+appBox->currentText()+"','"+ingEdit->toPlainText()+"','"+mDetail.getDID()+"');";
    } else if (in==3) {
        QString animals;
        if(buffalo->isChecked()){
            animals = "Buffalo, ";
        }
        if(cow->isChecked()){
            animals += "Cow, ";
        }
        if(others->isChecked()){
            animals += specifyEdit->text();
        } else {
            animals.remove(animals.length()-1);
            animals.remove(animals.length()-1);
        }
        productType = "INSERT INTO AnimalMedicine(ProductID, Apperance,FromWhere,AnimalType,LocalDID) VALUES ('"+
                pIDEdit->text()+"','"+appBox->currentText()+"','"+shopEdit->text()+"','"+animals+"','"+mDetail.getDID()+"');";
    } else{
        productType = "INSERT INTO PlantSeed(ProductID, Color, PlantName, LocalDID) VALUES ('"+
                pIDEdit->text()+"','"+appBox->currentText()+"','"+ingEdit->toPlainText()+"','"+mDetail.getDID()+"');";
    }
    QString gstValue = gstBox->currentText();
    gstValue.remove("%");
    QString gstQuery = "INSERT INTO ProductGst(ProductID, LocalDID, gst) VALUES ('"+
            pIDEdit->text()+"','"+mDetail.getDID()+"',"+gstValue+");";
    //myDatabase.transaction();
    query.exec("START TRANSACTION; "+productType+gstQuery+" COMMIT;");
    if(!myDatabase.commit()){
        myDatabase.close();
        if(!myDatabase.isOpen()){
            if(!connectDatabase()){
                return false;
            }
        }
        QSqlQuery tmpQ(myDatabase);
        if(tmpQ.exec("DELETE FROM Product WHERE ProductID ='"+pIDEdit->text()+"' and LocalDID = '"+mDetail.getDID()+"';")){
            rLoad(0);
            QMessageBox::information(this,
                                     tr("Product Registratin Error! - %1").arg(qApp->applicationName()),
                                     tr("<html><p>Connection Problem!</p>"
                                        "<p>Please try after some time.</p></html>"),
                                     QMessageBox::Ok|QMessageBox::Default);
            return false;
        } /*else {
            if(tmpQ.lastError().nativeErrorCode() != "2002"){
                rLoad(0);
                QMessageBox::information(this,
                                         tr("Product Registratin Error! - %1").arg(qApp->applicationName()),
                                         tr("<html><p>Connection Problem!</p>"
                                            "<p>Please try after some time.</p></html>"),
                                         QMessageBox::Ok|QMessageBox::Default);
                return false;
            }
            return true;
        }*/
    }
    return true;
}
