#ifndef UNIVERSALCONST_H
#define UNIVERSALCONST_H
#include <QString>

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
};

#endif // UNIVERSALCONST_H
