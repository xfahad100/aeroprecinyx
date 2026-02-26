#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include "pid.h"
 #include <unistd.h>
#include <math.h>
#include <iostream>

class autopilot
{
public:
    autopilot();
    ~autopilot();
    enum vMode { VNone, AltHold, VertSpeed, Speed, VNAV, ILS };
    enum lMode { LNone, Winglevel, Heading, LNAV, LOC };
    void mainLoop( double dt );
double apdefrad;
    // get the new elevator command based on current pitch and altitude
    double updateVMode( double dt, double pitch,double altitude, double alt, double GSerror);
     double updateydMode(double dt, double desiredrate, double yawrate);
    // get the new aileron command based on current bank and course
    double updateLMode( double dt, double bank, double crs , double navc, double rollrate, double altG);

    void setEngaged( bool engage );
    void setVMode( vMode mode );
    void setLMode( lMode mode );
    void setDesiredAlt( double alt );
    void setDesiredCrs( double crs );
    void setDesiredHdg( double hdg );
    void setDesiredVS( double vs );

    static double mapOneRangeToAnother(double sourceNumber, double fromA, double fromB, double toA, double toB, int decimalPrecision)
   {double deltaA = fromB - fromA;
        double deltaB = toB - toA;
        double scale = deltaB/deltaA;
        double negA = -1 * fromA;
        double offset = (negA * scale) + toA;
        double finalNumber = (sourceNumber * scale) + offset;
        int calcScale = (int) pow(10, decimalPrecision);
        return (double) round(finalNumber * calcScale)/calcScale;
    }
    double getFDPitchCmd();
    double getFDRollCmd();
    vMode getVMode();
    lMode getLMode();
    bool getEngaged();
    double apKp, apKi, apKd;
     double ap_aileron, ap_elevator, ap_rudder;
     double headingRotation, CorrectedHeading;
     PID* ydPID;

private:
    bool engaged;
    vMode VMode;
    lMode LMode;
    PID* vsPID;        // uses elevator to set pitch angle
    PID* baPID;        // uses aileron to set bank angle

    PID* vPID;         // uses pitch angle to set altitude
    PID* lPID;         // uses bank angle to set course
    PID* wlPID;        //wing level to ease in take off
    PID* vviPID;       //vertical speed mode

    double desiredPitch, pitch, desiredAlt, altitude;
    double desiredBank, bank, desiredCrs, course;
    double desiredHdg, desiredVS, _desiredVS;
    double ldb=0 , _alt;
    double diff1, diff2, desHdg_scaled;
    double desint, desprev;
    double apnow, apprev;
};

#endif // AUTOPILOT_H
