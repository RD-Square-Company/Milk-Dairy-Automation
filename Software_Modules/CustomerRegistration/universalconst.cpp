#include "universalconst.h"

UniversalConst::UniversalConst()
{
    dairyID = "LD0001"; // needs to be changed with global variable
    dairyName = "Shardha Dudha Dairy Lalya ka bas, Jaipur"; //needs to be changed with global variable
    dStreet = "JK Lkashmipat University";
    dCity = "Jaipur";
    dPincode = "302026";
    dState = "Rajasthan";
    dTagline = "My milk is best....";
    dDescription = "This is first milk dairy situated at JK Lakshmipat university....";
    estDate = "2018-01-01";
    dEmail = "rahuldangi144@gmail.com";
    hostName ="localhost";
    dataBase = "mds";
    databaseUName = "root";
    databaseUPass = "";
    localDB = "mds";
    localDBUName = "root";
    localDBPass = "";
    hostEmail = "rdsquare144@gmail.com";
    hostEPass = "9993621661";
    dairyMobNo = "7568577487";
    dairyWebsite = "www.shardhadairy.co.in";

    //all dairy pictures
    for (int i = 0 ; i  < 5; i++)
    {
        dp[i] = QImage("/media/root/Important/Qt projects/Milk_Dairy_Software/insert_Images/milk_dairy_logo.jpg");
    }

    //dairy owner details
    ownerID = "OD0002";
    oFName = "Rahul";
    oMName = "";
    oLName  = "Dangi";
    ownerStreet = "Jk Lkashmipat University";
    ownerCity = "Jaipur";
    ownerPincode = "302026";
    ownerState = "Rajasthan";
    oAd1 = "1234";
    oAd2 = "1234";
    oAd3 = "1234";
    oPContact = "7568577487";
    oSContact = "7568577487";
    oEmail = "rahulmahi@gmail.com";
    oDesc = "This is Rahul Dangi from JK Lakshmipat University.";

    //dairy logo, images and owner profile pic
    dairyLogo = QImage("/media/root/Important/Qt projects/Milk_Dairy_Software/insert_Images/milk_dairy_logo.jpg");
    ownerPic =  QImage("/media/root/Important/Qt projects/Milk_Dairy_Software/insert_Images/no_user.png");

    //set load images
    loadImage1 = "/home/rdsquare/trload.gif";

    //stylesheet varaible
    /*
     * all the style sheets for the line edit
     * required in register class
    */
     noError = "QLineEdit {"
                      "border: 1px solid #2F4F4F;"
                      "background-color: white;"
                      "background-repeat: no-repeat;"
                  "}"
                  "QLineEdit:focus {"
               "border-style: outset;"
                  "border-color: #0000FF;"
              "}"
               "QLineEdit:disabled {"
               "border: 1px solid #C4C4C4;"
               "background-color: #C4C4C4;"
               "}";

     yesError =  "QLineEdit {"
                        "border: 1px solid #FF0000;"
                        "border-radius: 1px;"
                        "background-color: white;"
                        "background-repeat: no-repeat;"
                    "}"
                    "QLineEdit:focus {"
                        "border-style: outset;"
                        "background-color: yellow;"
                    "border-color: #0000FF;"
                "}"
                        "QLineEdit:disabled {"
                        "border: 1px solid #C4C4C4;"
                        "background-color: #C4C4C4;"
                        "}" ;

    /*
     * all the stylesheets are here only
     * for the easy access to stylesheets
     *
    */
}
