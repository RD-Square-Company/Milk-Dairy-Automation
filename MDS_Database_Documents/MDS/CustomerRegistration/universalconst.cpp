#include "universalconst.h"

UniversalConst::UniversalConst()
{
    dairyID = "LD0001"; // needs to be changed with global variable
    dairyName = "Shardha Dudha Dairy Lalya ka bas, Jaipur"; //needs to be changed with global variable
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

    //set load images
    loadImage1 = "C:/Users/user/Desktop/trload.gif";

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
