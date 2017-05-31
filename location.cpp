#include "location.h"
#include <qdebug.h>

location::location()
{

}

void location::setLocation(double latitudeInput, double longtitudeInput){
    latitude = latitudeInput;
    longtitude = longtitudeInput;
}

double location::getLatitude(){
    qDebug() << latitude;
    return latitude;
}

double location::getLongtitude(){
    qDebug() << longtitude;
    return longtitude;
}
