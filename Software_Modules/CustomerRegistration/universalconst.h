#ifndef UNIVERSALCONST_H
#define UNIVERSALCONST_H
#include <QString>
#include <QImage>
/*
 * local dairy id no and dairy name are fetched by a global variables that will
 * store the id no and name and at last id no and name will be saved in a file
 * and whenever program start the id no and name will loaded in that variables
 *
 */

class UniversalConst
{
  public:
    UniversalConst();
     QString dairyID ;
     QString dairyName ;
     QString hostName;
     QString dataBase ;
     QString databaseUName ;
     QString databaseUPass ;
     QString hostEmail ;
     QString hostEPass ;
     QString noError;
     QString yesError;
     QString loadImage1;
     QString dairyMobNo;
     QString localDB;
     QString localDBUName;
     QString localDBPass;
     QString dairyWebsite;
     QImage dairyLogo;
     QImage ownerPic;
     QString dStreet;
     QString dCity;
     QString dPincode;
     QString dState;
     QString dTagline;
     QString dDescription;
     QString estDate;
     QString dEmail;
     QImage dp[5];
     QString oFName;
     QString oMName;
     QString oLName;
     QString ownerStreet;
     QString ownerCity;
     QString ownerPincode;
     QString ownerState;
     QString oAd1;
     QString oAd2;
     QString oAd3;
     QString ownerID;
     QString oPContact;
     QString oSContact;
     QString oDesc;
     QString oEmail;
};

#endif // UNIVERSALCONST_H
