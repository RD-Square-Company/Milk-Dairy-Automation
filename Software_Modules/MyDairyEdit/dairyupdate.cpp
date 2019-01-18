#include "dairyupdate.h"
#include <QFileDialog>
#include <QImage>
#include <QtDebug>
#include <QRegExp>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QBuffer>
#include <QByteArray>
#include <QTimer>

DairyUpdate::DairyUpdate(QWidget *parent)
    : QDialog(parent)
{
    //setting ui to DairyUpdate widget
    setupUi(this);

    //loading
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //set connections of DairyUpdate widget
    connect(logoButton, SIGNAL(clicked(bool)),
            this, SLOT(logoUpdatePressed()));
    connect(upButton, SIGNAL(clicked(bool)),
            this, SLOT(upPicturesPressed()));
    connect(updateButton, SIGNAL(clicked(bool)),
            this, SLOT(updatePressed()));
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    //all connections of DairyUpdate widget are set....

    //calll setwidgets() to set all the child widgets of the DairyUpdate widget
    setWidgets();
}

void DairyUpdate::setWidgets()
{
    //settting stylesheet to all the line edits of DairyUpdate widget
    nameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    tagEdit->setStyleSheet(gDetail.getNormalStylesheet());
    webEdit->setStyleSheet(gDetail.getNormalStylesheet());
    emailEdit->setStyleSheet(gDetail.getNormalStylesheet());
    streetEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cityEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pincodeEdit->setStyleSheet(gDetail.getNormalStylesheet());
    descEdit->setStyleSheet(gDetail.getNormalStylesheet());
    ///all line edit stylesheets are set to default (noError)
    ///
    /// setting dairy id

    titleLabel->setText(tr("Dairy Details Update: %1").arg(mDetail.getDID()));
    //settting dairy logo to logo label
    QImage image(mDetail.getLogo());
    logoLabel->setPixmap(QPixmap::fromImage(image.scaled(150, 100, Qt::IgnoreAspectRatio)));

    //setting default values to the all fields
    nameEdit->setText(tr("%1").arg(mDetail.getdName()));
    tagEdit->setText(tr("%1").arg(mDetail.gettagline()));
    webEdit->setText(tr("%1").arg(mDetail.getWebsite()));
    emailEdit->setText(tr("%1").arg(mDetail.getemailID()));
    streetEdit->setText(tr("%1").arg(mDetail.getdStreet()));
    cityEdit->setText(tr("%1").arg(mDetail.getdCity()));
    pincodeEdit->setText(tr("%1").arg(mDetail.getdPin()));
    stateBox->setCurrentText(mDetail.getdState());
    descEdit->setText(tr("%1").arg(mDetail.getdD()));
    estLabel->setText(tr("%1").arg(mDetail.getestDate()));
    //values of dairy are set to default

    //setting validator to the various input fileds

    QRegExp emailRegExp("[A-Za-z0-9@.]{10,50}");
    QRegExpValidator *emailValidator = new QRegExpValidator(emailRegExp, this);
    emailEdit->setValidator(emailValidator);

    QRegExp pincodeExp("[0-9]{6}");
    QRegExpValidator *pincodeValidator = new QRegExpValidator(pincodeExp, this);
    pincodeEdit->setValidator(pincodeValidator);

    QRegExp streetExp("[A-Za-z-.*'\\s0-9]{40}");
    QRegExpValidator *streetValidator = new QRegExpValidator(streetExp, this);
    streetEdit->setValidator(streetValidator);

    QRegExp cityExp("[A-Za-z\\s]{20}");
    QRegExpValidator *cityValidator = new QRegExpValidator(cityExp, this);
    cityEdit->setValidator(cityValidator);
}

void DairyUpdate::cancelPressed()
{
    //close the DairyUpdate widget
    disconnectDatabase(); //disconnecting database
    this->close();
}

void DairyUpdate::updatePressed()
{
    //disabling all the buttons of widgets
    rLoad(1);

    //checking for invalid entries
    QString error;
    QString tempDesc = descEdit->toPlainText();
    if (tempDesc.isEmpty()){
        error = tr("Please write something about dairy in Description Box.");
        descEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if (stateBox->currentIndex() == 0){
        error = tr("Please select your state where diary is situated.");
    }
    if (pincodeEdit->text().isEmpty()) {
        error  = tr("You must have to enter pincode of your dairy.");
        pincodeEdit->setStyleSheet(gDetail.getErrorStylesheet());
    } else if (pincodeEdit->text().count() != 6){
        error = tr("pincode must be of 6 digits.");
        pincodeEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if (cityEdit->text().isEmpty()){
        error = tr("Please enter your city.");
        cityEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if (streetEdit->text().isEmpty()) {
        error = tr("Please enter you address.");
        streetEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if (emailEdit->text().isEmpty()) {
        error = tr("Please enter official email id of milk diary.");
        emailEdit->setStyleSheet(gDetail.getErrorStylesheet());
    } else {
        if ((!emailEdit->text().contains('@')) || (emailEdit->text().count('@') > 1)) {
            error = tr("Please enter valid email id.");
            emailEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    }
    if (tagEdit->text().isEmpty()) {
        error  = tr("Please enter tag line of dairy");
        tagEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if (nameEdit->text().isEmpty()) {
        error = tr("Please enter name of your milk dairy.");
        nameEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    //all inputs are checked now

    if (!error.isEmpty()) {
        QMessageBox::information(this,
                                  tr("Input Error! : %1").arg(qApp->applicationName()),
                                   tr("Error Encountered: %1").arg(error),
                                  QMessageBox::Ok);
        rLoad(0);
        return ;
    }
    //all the inputs are checked and set now so call upload data to upload dairy information to the database
    if(uploadData()){
        QTimer::singleShot(2000, this, SLOT(showMessage()));
        saveOffline();
    } else {
        rLoad(0);
    }

    //settting stylesheet to all the line edits of DairyUpdate widget
    nameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    tagEdit->setStyleSheet(gDetail.getNormalStylesheet());
    webEdit->setStyleSheet(gDetail.getNormalStylesheet());
    emailEdit->setStyleSheet(gDetail.getNormalStylesheet());
    streetEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cityEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pincodeEdit->setStyleSheet(gDetail.getNormalStylesheet());
    descEdit->setStyleSheet(gDetail.getNormalStylesheet());
    ///all line edit stylesheets are set to default (noError)
}

bool DairyUpdate::uploadData()
{
    QString dairyQuery = "update Dairy "
                         "set Name = '" + nameEdit->text() + "' "
                       " , Website = '" + webEdit->text() + "' "
                        ", Tagline = '" + tagEdit->text() + "' "
                        ", Street = '" + streetEdit->text() + "' "
                       ", City = '" + cityEdit->text() + "' "
                       ", Pincode = '" + pincodeEdit->text() + "' "
                     ", State = '" + stateBox->currentText() + "' "
                       ", Logo = ? , Description = '" + descEdit->toPlainText() + "' "
                     "where LocalDID = '" + mDetail.getDID() + "';";
    QString emailQuery = "update DairyWPED "
                         "set Email_id = '" + emailEdit->text() + "' "
                         "where LocalDID = '" + mDetail.getDID() + "';";

    //converting image to bytearray to upload on server
    QByteArray ba;
    QBuffer bf(&ba);
    bf.open(QIODevice::WriteOnly);
    QImage tempImage;
    //showing error if pixmap is null or logo is not selected
    if (logoLabel->pixmap()){
        tempImage = logoLabel->pixmap()->toImage();
    } else {
        QMessageBox::critical(this,
                                tr("Logo Error! : %1").arg(qApp->applicationName()),
                                 tr("Error Encountered!\nPlease select a logo to upload on server for your milk dairy."),
                                 QMessageBox::Ok);
        return false;
    }
    tempImage.save(&bf, "JPG");
    //checking database connection and if it is connected then getting query ready and execute it.
    if (connectDatabase()) {
        QSqlQuery query(myDatabase);
        query.prepare(dairyQuery);
        query.addBindValue(ba, QSql::In);
        if(!query.exec()) {
            QMessageBox::critical(this,
                                  tr("Server Not Responding! : %1").arg(qApp->applicationName()),
                                  tr("Server Connection Error: server is not responding while uploading data of dairy."),
                                  QMessageBox::Ok);
            return false;
        }
        if (!query.exec(emailQuery)){
            QMessageBox::critical(this,
                                  tr("Email Updation Failed! : %1").arg(qApp->applicationName()),
                                  tr("Server Connection Error: server is not responding while uploading email of dairy."),
                                  QMessageBox::Ok);
            return true;
        }
        return true;
    }

    return false;
}

void DairyUpdate::showMessage()
{
    rLoad(0);
    QMessageBox::information(this,
                             tr("Update Successful! : %1").arg(qApp->applicationName()),
                             tr("Your dairy information is updated successfully on server.\n"
                                "For any query please visit 'www.mds.com'."),
                             QMessageBox::Ok);
    disconnectDatabase();
}

bool DairyUpdate::connectDatabase()
{
    if(!myDatabase.contains("dairyUpdate")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "dairyUpdate");
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
                              tr("&Cancel"), tr("&Retry"), QString(), 0, 1);
        if(result == 1)
            goto retry;
        else{
            return false;
    }
 }
    return true;
}

void DairyUpdate::disconnectDatabase()
{
    //removing database connection from  the QSqlDatabase
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("dairyUpdate");
}

void DairyUpdate::upPicturesPressed()
{
    //open upload pictures dialog box
    //using exec to open upload pictures dialog box so this dialog box can inactive be for some time
    dairyPic = new DairyPicture(this);
    dairyPic->exec();
    delete dairyPic;
}

void DairyUpdate::logoUpdatePressed()
{
    //open a file dialog for selecting logo from computer and then set it to logo label by setting it's width and height to appropriate size
    QString imgFile = QFileDialog::getOpenFileName(
                this,
                tr("Pick a User Image"),
                QDir::homePath(),
                tr("Images (*.png *.jpg)"));
    QImage UImg(imgFile);
    logoLabel->setPixmap(QPixmap::fromImage(UImg.scaled(150, 100, Qt::IgnoreAspectRatio)));
}

void DairyUpdate::rLoad(int i)
{
    if(i == 1){
        nameEdit->setEnabled(false);
        tagEdit->setEnabled(false);
        webEdit->setEnabled(false);
        emailEdit->setEnabled(false);
        streetEdit->setEnabled(false);
        cityEdit->setEnabled(false);
        pincodeEdit->setEnabled(false);
        stateBox->setEnabled(false);
        descEdit->setEnabled(false);
        logoButton->setEnabled(false);
        upButton->setEnabled(false);
        updateButton->setEnabled(false);
        cancelButton->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 -64;
        loadingLabel->setGeometry(x,y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        nameEdit->setEnabled(true);
        tagEdit->setEnabled(true);
        webEdit->setEnabled(true);
        emailEdit->setEnabled(true);
        streetEdit->setEnabled(true);
        cityEdit->setEnabled(true);
        pincodeEdit->setEnabled(true);
        stateBox->setEnabled(true);
        descEdit->setEnabled(true);
        logoButton->setEnabled(true);
        upButton->setEnabled(true);
        updateButton->setEnabled(true);
        cancelButton->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}

void DairyUpdate::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}

void DairyUpdate::saveOffline()
{
    //saving data to file for offline use
    mDetail.setdName(nameEdit->text());
    mDetail.settagline(tagEdit->text());
    mDetail.setWebsite(webEdit->text());
    mDetail.setemailID(emailEdit->text());
    mDetail.setdStreet(streetEdit->text());
    mDetail.setdCity(cityEdit->text());
    mDetail.setdPin(pincodeEdit->text());
    mDetail.setdState(stateBox->currentText());
    mDetail.setdD(descEdit->toPlainText());
    mDetail.setLogo(logoLabel->pixmap()->toImage());
}
