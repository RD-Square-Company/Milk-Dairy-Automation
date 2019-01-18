#include "ownerupdate.h"
#include <QPixmap>
#include <QFileDialog>
#include <QRegExp>
#include <QRegExpValidator>
#include <QDir>
#include <QMessageBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QByteArray>
#include <QBuffer>
#include <QSqlError>
#include <QtDebug>
#include <iostream>
#include <QTimer>

OwnerUpdate::OwnerUpdate(QWidget *parent)
    : QDialog(parent)
{
    //setting up ui to the widget
    setupUi(this);

    //loading
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //hiding the gender selection machanism
    genderLabel->hide();
    maleButton->hide();
    femalebutton->hide();
    emailEdit->hide();
    emailLabel->hide();

    //setting connections of the OwnerUpdate widget
    connect(picButton, SIGNAL(clicked(bool)),
            this, SLOT(updatePic()));
    connect(updateButton, SIGNAL(clicked(bool)),
            this, SLOT(updatePressed()));
    connect(cancelButton, SIGNAL(clicked(bool)),
             this, SLOT(cancelPressed()));
    //all connections to the signal and slot are done...now set child widgets of the OwnerUpdate widget
    setWidgets();
}

void OwnerUpdate::setWidgets()
{
    //setting stylesheets of all line edit of OwnerUpdate widget
    fNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    mNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    lNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //emailEdit->setStyleSheet(gDetail.getNormalStylesheet());
    streetEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cityEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pincodeEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //all stylesheet settings are done....
    //setting up title label
    titleLabel->setText(tr("Dairy Details Update: %1").arg(mDetail.getDID()));
    //setting profile pic to owner profile pic logo
    profilePic = mDetail.getpPic();
    picLabel->setPixmap(QPixmap::fromImage(mDetail.getpPic().scaled(100,100,Qt::IgnoreAspectRatio)));

    //setting validator to the input panels of OwnerUpdate widget

    QRegExp nameRegExp("[A-Za-z]{20}");
    QRegExpValidator *nameValidator = new QRegExpValidator(nameRegExp, this);
    fNameEdit->setValidator(nameValidator);
    mNameEdit->setValidator(nameValidator);
    lNameEdit->setValidator(nameValidator);

    QRegExp adharRegExp("[0-9]{4}");
    QRegExpValidator *adharValidator = new QRegExpValidator(adharRegExp, this);
    ad1Edit->setValidator(adharValidator);
    ad2Edit->setValidator(adharValidator);
    ad3Edit->setValidator(adharValidator);

    QRegExp contactRegExp("[0-9]{10}");
    QRegExpValidator *contactValidator = new QRegExpValidator(contactRegExp, this);
    pEdit->setValidator(contactValidator);
    cEdit->setValidator(contactValidator);

    //QRegExp emailRegExp("[A-Za-z0-9@.]{10,50}");
    //QRegExpValidator *emailValidator = new QRegExpValidator(emailRegExp, this);
    //emailEdit->setValidator(emailValidator);

    QRegExp pincodeExp("[0-9]{6}");
    QRegExpValidator *pincodeValidator = new QRegExpValidator(pincodeExp, this);
    pincodeEdit->setValidator(pincodeValidator);

    QRegExp streetExp("[A-Za-z-.*'\\s0-9]{40}");
    QRegExpValidator *streetValidator = new QRegExpValidator(streetExp, this);
    streetEdit->setValidator(streetValidator);

    QRegExp cityExp("[A-Za-z\\s]{20}");
    QRegExpValidator *cityValidator = new QRegExpValidator(cityExp, this);
    cityEdit->setValidator(cityValidator);
    //all validators to the input panels are set now

    //setting default  values to all input
    fNameEdit->setText(tr("%1").arg(mDetail.getofName()));
    mNameEdit->setText(tr("%1").arg(mDetail.getomName()));
    lNameEdit->setText(tr("%1").arg(mDetail.getolName()));
    ad1Edit->setText(tr("%1").arg(mDetail.getAdhaar().left(4)));
    ad2Edit->setText(tr("%1").arg(mDetail.getAdhaar().mid(5,4)));
    ad3Edit->setText(tr("%1").arg(mDetail.getAdhaar().right(4)));
    pEdit->setText(tr("%1").arg(mDetail.getpc()));
    cEdit->setText(tr("%1").arg(mDetail.getsc()));
    //emailEdit->setText(tr("%1").arg(uc.oEmail));
    streetEdit->setText(tr("%1").arg(mDetail.getoStreet()));
    cityEdit->setText(tr("%1").arg(mDetail.getoCity()));
    pincodeEdit->setText(tr("%1").arg(mDetail.getoPin()));
    stateBox->setCurrentText(mDetail.getoState());
    descEdit->setText(tr("%1").arg(mDetail.getoD()));
    //all values are set now...
    ad1Edit->setEnabled(false);
    ad2Edit->setEnabled(false);
    ad3Edit->setEnabled(false);
    fNameEdit->setEnabled(false);
    mNameEdit->setEnabled(false);
    lNameEdit->setEnabled(false);
}

bool OwnerUpdate::connectDatabase()
{
    if(!myDatabase.contains("ownerUpdate")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "ownerUpdate");
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

void OwnerUpdate::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("ownerUpdate");
}

void OwnerUpdate::updatePic()
{
    //open a file dialog for selecting profile pic from computer and then set it to pic label by setting it's width and height to appropriate size
    QString imgFile = QFileDialog::getOpenFileName(
                this,
                tr("Pick a User Image"),
                QDir::homePath(),
                tr("Images (*.png *.jpg)"));
    QImage UImg(imgFile);
    profilePic = UImg;
    picLabel->setPixmap(QPixmap::fromImage(profilePic.scaled(100, 100, Qt::IgnoreAspectRatio)));
}

void OwnerUpdate::updatePressed()
{
    rLoad(1);

    //check for all inpt values entered by user
    QString error = "";
    if(descEdit->toPlainText().isEmpty()){
        error = tr("Please, write something about yourself.");
    }
    if (stateBox->currentIndex() == 0) {
        error = tr("Please select your state.");
    }
    if (pincodeEdit->text().isEmpty()) {
        error = tr("Pincode field can not be empty.");
        pincodeEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if (cityEdit->text().isEmpty()) {
        error = tr("Please enter your residential city.");
        cityEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if (streetEdit->text().isEmpty()) {
        error = tr("Please enter your address");
        streetEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    /*if (emailEdit->text().isEmpty()) {
        error = tr("Please enter official email id of milk diary.");
        emailEdit->setStyleSheet(gDetail.getErrorStylesheet());
    } else {
        if ((!emailEdit->text().contains('@')) || (emailEdit->text().count('@') > 1)) {
            error = tr("Please enter valid email id.");
            emailEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    }*/
    if (!pEdit->text().isEmpty()) {
        if (pEdit->text().count() != 10) {
            error = tr("Please enter valid mobile no.");
            pEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    } else {
        error = tr("Please ener your mobile number.");
        pEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if (!cEdit->text().isEmpty()) {
        if (cEdit->text().count() != 10) {
            error = tr("Please enter valid mobile no.");
            cEdit->setStyleSheet(gDetail.getErrorStylesheet());
        }
    }
    if (fNameEdit->text().isEmpty()) {
        error  = tr("Please enter your first name.");
        fNameEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    if(lNameEdit->text().isEmpty()) {
        error = tr("Please enter your last name.");
        lNameEdit->setStyleSheet(gDetail.getErrorStylesheet());
    }
    //now .... checking for all input are done here

    if (!error.isEmpty()) {
        QMessageBox::information(this,
                                  tr("Input Error! : %1").arg(qApp->applicationName()),
                                   tr("Error Encountered: %1").arg(error),
                                  QMessageBox::Ok);
        rLoad(0);
        return ;
    }
    //callint updateData() to update the information of owner to server
    if(updateData()) {
        QTimer::singleShot(2000, this, SLOT(showMessage()));
        updateOffline();
    } else {
        rLoad(0);
    }

    //settting stylesheet to all the line edits of DairyUpdate widget
    fNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    mNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    lNameEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cEdit->setStyleSheet(gDetail.getNormalStylesheet());
    //emailEdit->setStyleSheet(gDetail.getNormalStylesheet());
    streetEdit->setStyleSheet(gDetail.getNormalStylesheet());
    cityEdit->setStyleSheet(gDetail.getNormalStylesheet());
    pincodeEdit->setStyleSheet(gDetail.getNormalStylesheet());
    ///all line edit stylesheets are set to default (noError)
}

void OwnerUpdate::updateOffline()
{
    mDetail.setOwnerInfo(mDetail.getOID(), fNameEdit->text(), mNameEdit->text(), lNameEdit->text(),
                         pEdit->text(), cEdit->text(),streetEdit->text(),cityEdit->text(), pincodeEdit->text(),
                         stateBox->currentText(), descEdit->toPlainText(), ad1Edit->text()+ad2Edit->text()+ad3Edit->text(),
                         picLabel->pixmap()->toImage());
}

bool OwnerUpdate::updateData()
{
   QString queryString = "update DairyOwner "
                         "set DOFName = '" + fNameEdit->text() + "', "
           "DOMName = '" + mNameEdit->text() + "', "
           "DOLName  = '" + lNameEdit->text() + "', "
           "PContact = '" + pEdit->text() + "', "
           "SContact = '" + cEdit->text() + "', "
           "Description = '" + descEdit->toPlainText() + "', "
           "Street = '" + streetEdit->text() + "', "
           "City = '" + cityEdit->text() + "', "
           "Pincode = '" + pincodeEdit->text() + "', "
           "State = '" + stateBox->currentText() + "', "
           "ProfilePic = ? "
           "where OwnerID = '" + mDetail.getOID() +"';";
   //QString emailString = "update DairyWPED "
    //                     "set Email_id = '" + emailEdit->text() + "' "
     //                     "where  LocalDID = '" + mDetail.getDID() + "';";
   //converting image to bytearray to upload on server
   QByteArray ba;
   QBuffer bf(&ba);
   bf.open(QIODevice::WriteOnly);
   QImage tempImage;
   //showing error if pixmap is null or logo is not selected
   if (picLabel->pixmap()){
       tempImage = picLabel->pixmap()->toImage();
   } else {
       QMessageBox::critical(this,
                               tr("Profile Pic  Error! : %1").arg(qApp->applicationName()),
                                tr("Error Encountered!\nPlease select a logo to upload on server for your milk dairy."),
                                QMessageBox::Ok);
       return false;
   }
   tempImage.save(&bf, "JPG");

   //checking if database is open or not
   if(connectDatabase()) {
       QSqlQuery query(myDatabase);
       query.prepare(queryString);
       query.addBindValue(ba, QSql::In);

       if(!query.exec()) {
           QMessageBox::critical(this,
                                             tr("Server Not Responding! : %1").arg(qApp->applicationName()),
                                             tr("Server Connection Error: server is not responding while uploading data of dairy."),
                                             QMessageBox::Ok);
                       return false;
       }
       return true;

       /*
       if (!query.exec(emailString)) {
           QMessageBox::critical(this,
                                 tr("Email Updation Failed! : %1").arg(qApp->applicationName()),
                                 tr("Server Connection Error: server is not responding while uploading email of dairy."),
                                 QMessageBox::Ok);
           return;
       }*/
   }
   return false;
}

void OwnerUpdate::showMessage()
{
    rLoad(0);\
    //show successfull updation completed message
    QMessageBox::information(this,
                             tr("Update Successful! : %1").arg(qApp->applicationName()),
                             tr("Your dairy information is updated successfully on server.\n"
                                "For any query please visit 'www.mds.com'."),
                             QMessageBox::Ok);
    disconnectDatabase();
}

void OwnerUpdate::cancelPressed()
{
    //first disconnect database connection from widget before closing this widget
    disconnectDatabase();
    //close this widget now
    this->close();
}

void OwnerUpdate::rLoad(int i)
{
    if(i == 1){
        streetEdit->setEnabled(false);
        cityEdit->setEnabled(false);
        pincodeEdit->setEnabled(false);
        stateBox->setEnabled(false);
        descEdit->setEnabled(false);
        picButton->setEnabled(false);
        pEdit->setEnabled(false);
        cEdit->setEnabled(false);
        updateButton->setEnabled(false);
        cancelButton->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 -64;
        loadingLabel->setGeometry(x,y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        streetEdit->setEnabled(true);
        cityEdit->setEnabled(true);
        pincodeEdit->setEnabled(true);
        stateBox->setEnabled(true);
        descEdit->setEnabled(true);
        picButton->setEnabled(true);
        pEdit->setEnabled(true);
        cEdit->setEnabled(true);
        updateButton->setEnabled(true);
        cancelButton->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}

void OwnerUpdate::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}
