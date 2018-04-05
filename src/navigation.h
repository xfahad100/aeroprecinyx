#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "math.h"

class navigation
{
public:
    navigation();
    void SetMagVar(double var);
    void SetILSRunwayEndPoints(double nearLat, double nearLon, double farLat, double farLon);
    void SetILSFrequency(float freq);
    void SetILSCourseMag(double course);
    void SetILSGS(double gs);
    void SetILSTDZE(double elev);
    void SetPosition(double lat, double lon, double alt);
    void SetTrueHeading(double hdg);

    double GetMagHdg();


private:
    double magvar;
    double rwyNearLat, rwyNearLon, rwyFarLat, rwyFarLon;
    float ILSfreq;
    double ILSCourse;
    double ILSGS;
    double ILSTDZE;
    double posLat, posLon, posAlt;
    double trueHdg;
};

#endif // NAVIGATION_H
