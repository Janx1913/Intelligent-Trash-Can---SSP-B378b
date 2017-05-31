#ifndef LOCATION_H
#define LOCATION_H


class location
{
public:
    location();
    double getLatitude();
    double getLongtitude();
    void setLocation(double latitudeInput, double longtitudeInput);

private:
    double latitude;
    double longtitude;

};

#endif // LOCATION_H
