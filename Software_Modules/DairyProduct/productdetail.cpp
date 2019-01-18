#include "productdetail.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QKeyEvent>
#include "../CustomerRegistration/smtp.h"
#include <QDebug>
#include <QTimer>
#include <QSqlError>

ProductDetail::ProductDetail(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    //loading initializing
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //initializing model
    model = new QSqlQueryModel;
    stringModel = new QStringListModel;

    //initializing mapper
    mapper = new QDataWidgetMapper(this);

    //initializing completer
    completer = new QCompleter(this);

    //setting connections
    connect(updateButton, SIGNAL(clicked(bool)),
            this, SLOT(updatePressed()));
    connect(newButton, SIGNAL(clicked(bool)),
            this, SLOT(newPressed()));
    connect(listView, SIGNAL(currentRowChanged(int)),
            this, SLOT(productChanged(int)));
    connect(paButton, SIGNAL(clicked(bool)),
            this, SLOT(paPressed()));
    connect(srdButton, SIGNAL(clicked(bool)),
            this, SLOT(srdPressed()));
    connect(searchButton, SIGNAL(clicked(bool)),
            this, SLOT(searchProduct()));
    //connections are set

    //setting event filter to searchEdit
    searchEdit->installEventFilter(this);

    setWidgets();
}

void ProductDetail::setWidgets()
{
    //setting stylesheet for all line edit
    searchEdit->setStyleSheet(gDetail.getNormalStylesheet());
    priceEdit->setStyleSheet(gDetail.getNormalStylesheet());
    quantityEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //setting of stylesheet is completed

    //setting validator for line edit
    QRegExp priceExp("[0-9]{1,5}[.][0-9]{2}");
    QRegExpValidator *priceValidator = new QRegExpValidator(priceExp, this);
    priceEdit->setValidator(priceValidator);
    quantityEdit->setValidator(priceValidator);
    //setting of all validator is completed

    //setting mapper for widgets
    mapper->setModel(model);
    mapper->addMapping(pidLabel, 0, "text");
    mapper->addMapping(pNameLabel, 1, "text");
    mapper->addMapping(bNameLabel,2, "text");
    mapper->addMapping(priceEdit, 3);
    mapper->addMapping(quantityEdit, 4);
    mapper->addMapping(descLabel, 8, "text");

    //querying by model
    modelQuery();

    //settting completer

    completer->setModel(stringModel);
    completer->setMaxVisibleItems(10);
    completer->setWrapAround(true);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    searchEdit->setCompleter(completer);

    QStringList stringList;
    for(int row=0; row < model->rowCount(); row++){
        stringList << model->data(model->index(row, 0)).toString();
        stringList << model->data(model->index(row, 1)).toString();
        stringList << model->data(model->index(row, 2)).toString();
    }

    stringModel->setStringList(stringList);

    if(model->rowCount() == 0) {
        editSetting(0);
    } else {
        editSetting(1);
    }

    mapper->toFirst();
    listView->setCurrentRow(0);
}

void ProductDetail::editSetting(int i)
{
    if(i == 1) {
        priceEdit->setEnabled(true);
        quantityEdit->setEnabled(true);
    } else {
        priceEdit->setEnabled(false);
        quantityEdit->setEnabled(false);
    }
}

void ProductDetail::modelQuery()
{
    for(int row=0; row< model->rowCount(); row++){
        model->removeRow(row);
    }

    //setting list view
    for(int row = 0; row<listView->count(); row++){
        listView->model()->removeRows(0, model->rowCount());
    }

    QString queryString = "select P.ProductID as pid, P.ProductName as pn, P.BrandName as bn, P.Price as pr, P.Quantity as qn,"
                          "P.PackTypeID as ptid, P.ProductCatID as pcid, P.WTID as wtid, P.Decription as des, PG.gst "
                          "from Product P, ProductGst PG "
                          "where P.ProductID = PG.ProductID "
                          "and P.LocalDID = PG.LocalDID "
                          "and binary P.LocalDID = '" + mDetail.getDID() + "';";


    //connect database if not connected
    if(!myDatabase.isOpen()){
        if(!connectDatabase())
            return;
    }

    model->setQuery(queryString, myDatabase);

    for(int row=0; row < model->rowCount(); row++){
        listView->addItem(model->data(model->index(row, 0)).toString() + "    "+ model->data(model->index(row, 1)).toString() + " (" +
                          model->data(model->index(row, 4)).toString()+" - "  +model->data(model->index(row, 3)).toString() +")");
    }
}

void ProductDetail::updatePressed()
{
    QString error;
    if(priceEdit->text().isEmpty()){
        error = tr("Please enter price of product");
        priceEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(quantityEdit->text().isEmpty()){
        error = tr("Please enter quantity on per of product.");
        quantityEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }

    if(error.isEmpty()){
        updateValue();
    } else {

        QMessageBox::information(this, tr("Enter Correct Value - %1").arg(qApp->applicationName()),
                                 tr("%1").arg(error),
                                 QMessageBox::Ok|QMessageBox::Default);
    }
}

void ProductDetail::updateValue()
{
    rLoad(1);
    if(!myDatabase.isOpen()){
        if(!connectDatabase()){
            rLoad(0);
            return;
        }
    }

    QSqlQuery query(myDatabase);
    QString updateQuery = "update Product set Price = " + priceEdit->text() + ", Quantity = " +
            quantityEdit->text() + " where ProductID = '" + pidLabel->text() + "' and "
            " LocalDID = '"+ mDetail.getDID() + "';";

    if(!query.exec(updateQuery)){
        QMessageBox::critical(this,
                              tr("Connection Error! : %1").arg(qApp->applicationName()),
                              tr("\tDatabase Connection Problem!\n"
                                 "Please make sure, you are connected to the internet service."
                                 "Retry after connecting to the internet."
                                 "SQL Error Code - %1").arg(query.lastError().text()),
                              QMessageBox::Ok | QMessageBox::Default);
        rLoad(0);
        return;
    } else {
        QTimer::singleShot(2000, this, SLOT(showMessage()));
    }
}

void ProductDetail::showMessage()
{
    rLoad(0);
    QMessageBox::information(this, tr("Information Updated! - %1").arg(qApp->applicationName()),
                             tr("Product detail is updated successfully."),
                             QMessageBox::Ok | QMessageBox::Default);
    modelQuery();
}

void ProductDetail::srdPressed()
{
    //empty for now
}

void ProductDetail::newPressed()
{
    productRegistration = new ProductRegistration(this);
    productRegistration->exec();
    delete productRegistration;
}

void ProductDetail::paPressed()
{
    //empty for now
}

void ProductDetail::searchProduct()
{
    QString temp = searchEdit->text();
    int row = 0;
    while (row < model->rowCount()){
        if(temp == model->data(model->index(row, 0)).toString()){
            listView->setCurrentRow(row);
            listView->currentRowChanged(row);
            return;
        }
        row++;
    }

    row = 0;
    while (row <model->rowCount()){
        if(temp == model->data(model->index(row, 1)).toString()){
            listView->setCurrentRow(row);
            listView->currentRowChanged(row);
            return;
        }
        row++;
    }

    row = 0;
    while (row <model->rowCount()){
        if(temp == model->data(model->index(row, 2)).toString()){
            listView->setCurrentRow(row);
            listView->currentRowChanged(row);
            return;
        }
        row++;
    }

    QMessageBox::information(this, tr("Not Found! - %1").arg(qApp->applicationName()),
                             tr("%1 is not found in database...").arg(temp),
                             QMessageBox::Ok|QMessageBox::Default);
}

bool ProductDetail::connectDatabase()
{
    if(!myDatabase.contains("prodDetail")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "prodDetail");
        myDatabase.setHostName(oDetail.getHostName());
        myDatabase.setUserName(oDetail.getUserName());
        myDatabase.setPassword(oDetail.getUserPass());
        myDatabase.setDatabaseName(oDetail.getDatabase());
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

void ProductDetail::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("prodDetail");
}

void ProductDetail::productChanged(int row)
{
    if(!priceEdit->isEnabled()){
        searchEdit->setEnabled(true);
        listView->setEnabled(true);
        priceEdit->setEnabled(true);
        quantityEdit->setEnabled(true);
        newButton->setEnabled(true);
        paButton->setEnabled(true);
        srdButton->setEnabled(true);
        updateButton->setEnabled(true);
        searchButton->setEnabled(true);
    }

    //setting stylesheet for all line edit
    searchEdit->setStyleSheet(gDetail.getNormalStylesheet());
    priceEdit->setStyleSheet(gDetail.getNormalStylesheet());
    quantityEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //setting of stylesheet is completed

    mapper->toFirst();

    for(int jump = 0; jump < row; jump++){
        mapper->toNext();
    }
    updateDetails();
}

void ProductDetail::rLoad(int i)
{
    if(i == 1){
        newButton->setEnabled(false);
        paButton->setEnabled(false);
        srdButton->setEnabled(false);
        priceEdit->setEnabled(false);
        quantityEdit->setEnabled(false);
        updateButton->setEnabled(false);
        listView->setEnabled(false);
        searchButton->setEnabled(false);
        searchEdit->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 - 64;
        loadingLabel->setGeometry(x, y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        loading->stop();
        loadingLabel->hide();
        searchEdit->setEnabled(true);
        listView->setEnabled(true);
        priceEdit->setEnabled(true);
        quantityEdit->setEnabled(true);
        newButton->setEnabled(true);
        paButton->setEnabled(true);
        srdButton->setEnabled(true);
        updateButton->setEnabled(true);
        searchButton->setEnabled(true);
    }
}

void ProductDetail::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}

void ProductDetail::updateDetails()
{

    int ptid = model->data(model->index(listView->currentRow(), 6)).toString().toInt();
    QSqlQuery query(myDatabase);
    if (ptid == 1) {
        pTypeLabel->setText(tr("Human Food"));
        QString qString = "select Color, Ingredients "
                          "from HumanFood "
                          "where ProductID = '" + pidLabel->text() + "' and "
                          " LocalDID = '" + mDetail.getDID() + "';";
        acNameLabel->setText(tr("Color:"));
        iLabel->setText(tr("Ingredients"));
        iLabel->show();
        ingLabel->show();
        stLabel->hide();
        shopLabel->hide();
        if(query.exec(qString)){
            if(query.size() > 0) {
                if(query.next()) {
                    colorLabel->setText(query.value("Color").toString());
                    ingLabel->setText(query.value("Ingredients").toString());
                }
            }
        }
    } else if (ptid == 2) {
        pTypeLabel->setText(tr("Animal Food"));
        QString qString = "select Appearance, Ingredients "
                          "from AnimalFood "
                          "where ProductID = '" + pidLabel->text() + "' and "
                          " LocalDID = '" + mDetail.getDID() + "';";
        acNameLabel->setText(tr("Appearance:"));
        iLabel->setText(tr("Ingredients"));
        iLabel->show();
        ingLabel->show();
        stLabel->hide();
        shopLabel->hide();
        if(query.exec(qString)){
            if(query.size() > 0) {
                if(query.next()) {
                    colorLabel->setText(query.value("Appearance").toString());
                    ingLabel->setText(query.value("Ingredients").toString());
                }
            }
        }
    } else if (ptid == 3) {
        pTypeLabel->setText(tr("Animal Medicine"));
        QString qString = "select Apperance, FromWhere, AnimalType "
                          "from AnimalMedicine "
                          "where ProductID = '" + pidLabel->text() + "' and "
                          " LocalDID = '" + mDetail.getDID() + "';";
        acNameLabel->setText(tr("Appearance:"));
        iLabel->setText(tr("For Animals:"));
        iLabel->show();
        ingLabel->show();
        stLabel->show();
        shopLabel->show();
        if(query.exec(qString)){
            if(query.size() > 0) {
                if(query.next()) {
                    colorLabel->setText(query.value("Apperance").toString());
                    shopLabel->setText(query.value("FromWhere").toString());
                    ingLabel->setText(query.value("AnimalType").toString());
                }
            }
        }
    } else if (ptid == 4) {
        pTypeLabel->setText(tr("Plant Seed"));
        QString qString = "select Color, PlantName "
                          "from PlantSeed "
                          "where ProductID = '" + pidLabel->text() + "' and "
                          " LocalDID = '" + mDetail.getDID() + "';";
        acNameLabel->setText(tr("Appearance:"));
        iLabel->setText(tr("Plant Name:"));
        iLabel->show();
        ingLabel->show();
        stLabel->hide();
        shopLabel->hide();
        if(query.exec(qString)){
            if(query.size() > 0) {
                if(query.next()) {
                    colorLabel->setText(query.value("Appearance").toString());
                    ingLabel->setText(query.value("PlantName").toString());
                }
            }
        }
    }
}
