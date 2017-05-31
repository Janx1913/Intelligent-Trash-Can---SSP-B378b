#include "mainwindow.h"
#include <QApplication>
#include <list>
#include "trashcan.h"
#include "location.h"

int main(int argc, char *argv[])
{
    //Starting a Qapp, with a MainWindow object, called w
    QApplication a(argc, argv);
    MainWindow w;

    //Set name of window and the size of it
    w.setWindowTitle("serialTest");
    w.setFixedSize(400,250);
    w.show();


    trashCan trash1, trash2;
    location loc1;

    loc1.setLocation(570303, 954513);
    trash1.setLocation(570300, 954500);
    trash2.setLocation(550300, 924500);

    std::list<location> locations; // holds all locations, including trashCans
    std::list<trashCan> trashCans; // holds only trashCans

    locations.push_back(loc1);
    locations.push_back(trash1);
    locations.push_back(trash2);

    trashCans.push_back(trash1);

    for (std::list<location>::iterator it = locations.begin(); it != locations.end(); ++it){
        it->getLatitude();
        it->getLongtitude();
    }

    return a.exec();
}
