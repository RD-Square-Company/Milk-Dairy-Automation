#include "dairypicture.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QPixmap>
#include <QByteArray>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QBuffer>
#include <QTimer>

DairyPicture::DairyPicture(QWidget *parent)
    : QDialog(parent)
{
    //set ui to DairyPiture widget
    setupUi(this);

    //loading
    loadingLabel = new QLabel(this);
    loading = gDetail.getLoadAnimation();
    loadingLabel->setMovie(loading);
    loadingLabel->hide();

    //set connections to buttons
    connect(pb1, SIGNAL(clicked(bool)),
            this, SLOT(p1Pressed()));
    connect(pb2, SIGNAL(clicked(bool)),
            this, SLOT(p2Pressed()));
    connect(pb3, SIGNAL(clicked(bool)),
            this, SLOT(p3Pressed()));
    connect(pb4, SIGNAL(clicked(bool)),
            this, SLOT(p4Pressed()));
    connect(pb5, SIGNAL(clicked(bool)),
            this, SLOT(p5Pressed()));
    connect(cancelButton, SIGNAL(clicked(bool)),
            this, SLOT(cancelPressed()));
    connect(updateButton, SIGNAL(clicked(bool)),
            this, SLOT(updatePressed()));
    //all connections are set for DairyPicture widget

    //setting widgets of DairyPicture widget
    setWidgets();
}

void DairyPicture::setWidgets()
{
    if (connectDatabase()){
        QSqlQuery query(myDatabase);
        QString queryString = "select Picture from DairyPicture "
                              "where LocalDID  = '" + mDetail.getDID() + "';";
        if (query.exec(queryString)){
            if (query.size() > 0) {
                int index = 0;
                while (query.next()) {
                    QByteArray ba = query.value("Picture").toByteArray();
                    pc[index].loadFromData(ba, "JPG");
                    index++;
                }
            }
        } else {
            for (int index = 0; index < 5; index++) {
                pc[index] = mDetail.getPictures().at(index);
            }
        }
    } else {
        for (int index = 0; index < 5; index++) {
            pc[index] = mDetail.getPictures().at(index);
        }
    }

    //setting dairy pictures to labels
    pic1->setPixmap(QPixmap::fromImage(pc[0].scaled(100,100,Qt::IgnoreAspectRatio)));
    pic2->setPixmap(QPixmap::fromImage(pc[1].scaled(100,100,Qt::IgnoreAspectRatio)));
    pic3->setPixmap(QPixmap::fromImage(pc[2].scaled(100,100,Qt::IgnoreAspectRatio)));
    pic4->setPixmap(QPixmap::fromImage(pc[3].scaled(100,100,Qt::IgnoreAspectRatio)));
    pic5->setPixmap(QPixmap::fromImage(pc[4].scaled(100,100,Qt::IgnoreAspectRatio)));
}

bool DairyPicture::connectDatabase()
{
    if(!myDatabase.contains("dairyPicture")){
        myDatabase = QSqlDatabase::addDatabase("QMYSQL", "dairyPicture");
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

void DairyPicture::disconnectDatabase()
{
    myDatabase = QSqlDatabase();
    myDatabase.removeDatabase("dairyPicture");
}

void DairyPicture::p1Pressed()
{
    //open a file dialog for selecting pic1 from computer and then set it to pic1 label by setting it's width and height to appropriate size
    QString imgFile = QFileDialog::getOpenFileName(
                this,
                tr("Pick a User Image"),
                QDir::homePath(),
                tr("Images (*.png  *.jpg )"));
    QImage UImg(imgFile);
    pc[0] = QImage(imgFile);
    pic1->setPixmap(QPixmap::fromImage(UImg.scaled(100, 100, Qt::IgnoreAspectRatio)));
}

void DairyPicture::p2Pressed()
{
    //open a file dialog for selecting pic2 from computer and then set it to pic2 label by setting it's width and height to appropriate size
    QString imgFile = QFileDialog::getOpenFileName(
                this,
                tr("Pick a User Image"),
                QDir::homePath(),
                tr("Images (*.png  *.jpg )"));
    QImage UImg(imgFile);
    pc[1] = QImage(imgFile);
    pic2->setPixmap(QPixmap::fromImage(UImg.scaled(100, 100, Qt::IgnoreAspectRatio)));
}

void DairyPicture::p3Pressed()
{
    //open a file dialog for selecting pic3 from computer and then set it to pic3 label by setting it's width and height to appropriate size
    QString imgFile = QFileDialog::getOpenFileName(
                this,
                tr("Pick a User Image"),
                QDir::homePath(),
                tr("Images (*.png  *.jpg )"));
    QImage UImg(imgFile);
    pc[2] = QImage(imgFile);
    pic3->setPixmap(QPixmap::fromImage(UImg.scaled(100, 100, Qt::IgnoreAspectRatio)));
}

void DairyPicture::p4Pressed()
{
    //open a file dialog for selecting pic4 from computer and then set it to pic4 label by setting it's width and height to appropriate size
    QString imgFile = QFileDialog::getOpenFileName(
                this,
                tr("Pick a User Image"),
                QDir::homePath(),
                tr("Images (*.png  *.jpg )"));
    QImage UImg(imgFile);
    pc[3] = QImage(imgFile);
    pic4->setPixmap(QPixmap::fromImage(UImg.scaled(100, 100, Qt::IgnoreAspectRatio)));
}

void DairyPicture::p5Pressed()
{
    //open a file dialog for selecting pic5 from computer and then set it to pic5 label by setting it's width and height to appropriate size
    QString imgFile = QFileDialog::getOpenFileName(
                this,
                tr("Pick a User Image"),
                QDir::homePath(),
                tr("Images (*.png  *.jpg )"));
    QImage UImg(imgFile);
    pc[4] = QImage(imgFile);
    pic5->setPixmap(QPixmap::fromImage(UImg.scaled(100, 100, Qt::IgnoreAspectRatio)));
}

void DairyPicture::updatePressed()
{
    //switching off all the buttons till updation process takes place
    rLoad(1);

    if (connectDatabase()) {
        QSqlQuery query(myDatabase);
        QSqlQuery query1(myDatabase);
        QString queryString = "select ImgNo from DairyPicture "
                              "where LocalDID = '" + mDetail.getDID() + "';";
        if (query.exec(queryString)) {
            //getting image id of every image
            if (query.size() > 0) {
                int i = 0;
                while (query.next()) {
                    pcId[i] = query.value("ImgNo").toInt();
                    i++;
                }
            }
            //now prepare updation query
            for (int index = 0; index <5; index++) {
                query1.prepare("update DairyPicture "
                              "set Picture = ? "
                              "where ImgNo = " + QString::number(pcId[index]) + " and LocalDID = '" +
                              mDetail.getDID() + "';");
                QByteArray ba ;
                QBuffer bf(&ba);
                bf.open(QIODevice::WriteOnly);
                pc[index].save(&bf, "JPG");
                query1.addBindValue(ba, QSql::In);

                if (!query1.exec()){
                    QMessageBox::information(this,
                                             tr("Connection Error! : %1").arg(qApp->applicationName()),
                                             tr("connect to database and then try again...."),
                                             QMessageBox::Ok);
                    rLoad(0);
                    return;
                }
            }
        } else {
            QMessageBox::information(this,
                                     tr("Connection Error! : %1").arg(qApp->applicationName()),
                                     tr("connect to database and then try again...."),
                                     QMessageBox::Ok);
            rLoad(0);
            return;
        }

        QTimer::singleShot(2000, this, SLOT(showMessage()));
        updateOffline();
    }
    //turning on all the buttons

}

void DairyPicture::showMessage()
{
    rLoad(0);
    QMessageBox::information(this,
                             tr("Update Successful! : %1").arg(qApp->applicationName()),
                             tr("Dear Secratery,\nYour dairy showcase picture(s) are updated successfully on server."),
                             QMessageBox::Ok);
    disconnectDatabase();
}

void DairyPicture::cancelPressed()
{
    disconnectDatabase();
    this->close();
}

void DairyPicture::updateOffline()
{
    QList<QImage> imageList;
    imageList.append(pic1->pixmap()->toImage());
    imageList.append(pic2->pixmap()->toImage());
    imageList.append(pic3->pixmap()->toImage());
    imageList.append(pic4->pixmap()->toImage());
    imageList.append(pic5->pixmap()->toImage());
    QStringList idList;
    idList.append(QString::number(pcId[0]));
    idList.append(QString::number(pcId[1]));
    idList.append(QString::number(pcId[2]));
    idList.append(QString::number(pcId[3]));
    idList.append(QString::number(pcId[4]));

    mDetail.setPictures(imageList);
    mDetail.setiNums(idList);
}

void DairyPicture::rLoad(int i)
{
    if(i == 1){
        pb1->setEnabled(false);
        pb2->setEnabled(false);
        pb3->setEnabled(false);
        pb4->setEnabled(false);
        pb5->setEnabled(false);
        updateButton->setEnabled(false);
        cancelButton->setEnabled(false);
        int x = this->rect().width()/2 - 64;
        int y = this->rect().height()/2 -64;
        loadingLabel->setGeometry(x,y, 128, 128);
        loadingLabel->show();
        loading->start();
    } else {
        pb1->setEnabled(true);
        pb2->setEnabled(true);
        pb3->setEnabled(true);
        pb4->setEnabled(true);
        pb5->setEnabled(true);
        updateButton->setEnabled(true);
        cancelButton->setEnabled(true);
        loading->stop();
        loadingLabel->hide();
    }
}

void DairyPicture::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    loadingLabel->setGeometry(this->width()/2-50,this->height()/2-50, 150,150);
}
