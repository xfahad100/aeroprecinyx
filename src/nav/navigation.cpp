#include "navigation.h"

navigation::navigation()
{
  d2r = 0.017453293;
  r2d = 57.29577951;
  ft2nm = 0.000164579;
  ILS = false;
  rwyLen = 10000.0;
  secinterval= false;
  distance2 = 0.0;
}

void navigation::SetMagVar(double var) {magvar=var;}
void navigation::SetILSRunwayEndPoints(double nearLat, double nearLon,
                                       double farLat, double farLon)
   {rwyNearLat=nearLat; rwyNearLon=nearLon; rwyFarLat=farLat; rwyFarLon=farLon;}
void navigation::SetRwyLength(double len) {rwyLen=len;}
void navigation::SetILSFrequency(float freq) {ILSfreq=freq;}
void navigation::SetILSCourseMag(double course) {ILSCourse=course;}
void navigation::SetILSGS(double gs) {ILSGS=gs;}
void navigation::SetILSTDZE(double elev) {ILSTDZE=elev;}
void navigation::SetPosition(double lat, double lon, double alt)
   {pos.lat=lat; pos.lon=lon; pos.alt=alt;}
//{if(_GSbool!=true){
//        pos.lat=lat; pos.lon=lon; pos.alt=alt;}
//    else {
//       pos.lat=rwyNearLat; pos.lon=rwyNearLon; pos.alt=alt;
//    }
//    }
void navigation::SetTrueHeading(double hdg) {trueHdg=hdg;}
void navigation::SetILSEngaged(bool set) {ILS=set;}
void navigation::SetGSEngaged(bool set) {_GSbool=set;}
void navigation::SetHDGEngaged(bool set) {HDG=set;}
void navigation::SetSelectedHdg(int val) {selectedHDG=val;}

double navigation::GetMagHdg() {return trueHdg-magvar;}
double navigation::GetCourseErrorDeg() {return courseError;}
double navigation::GetGSErrorDeg() {return GSError;}
double navigation::GetInterceptAngle() {return interceptAngle;}
double navigation::GetDistance() {
    if(secinterval!=true){return distance;}
    else {
       return distance2;
    }}
int navigation::GetSelectedHdg() {return selectedHDG;}
double navigation::GetILSCourse() {return ILSCourse;}
QString navigation::GetIdentifier() {return QString("DTK");}


///////////////////////////////////////////////////////////////////////////////
/// Get true bearing (deg) and distance (nm) from start to finish
///
BrgDst navigation::GetBearingDistance(GeoLoc start, GeoLoc finish) {
    BrgDst bd;
    double deltaL = (finish.lon - start.lon)*d2r;
    double y = sin(deltaL) * cos(finish.lat*d2r);
    double x = cos(start.lat*d2r) * sin(finish.lat*d2r) -
            sin(start.lat*d2r) * cos(finish.lat*d2r) * cos(deltaL);
    bd.bearing = atan2(y, x)*r2d;  // true bearing in degrees
    bd.bearing = fmod((bd.bearing + 360.0), 360);

    double R = 3440.06479482;  // Radius of Earth in nautical miles
    double p1 = start.lat*d2r;
    double p2 = finish.lat*d2r;
    double dp = (finish.lat - start.lat)*d2r;
    double dq = (finish.lon - start.lon)*d2r;
    double a = sin(dp*0.5) * sin(dp*0.5) +
               cos(p1) * cos(p2) * sin(dq*0.5) * sin(dq*0.5);
    double c = 2.0 * (atan2(sqrt(a), sqrt(1.0-a)));
    bd.distance = R*c;

    return bd;
}

void navigation::Update() {
    if (ILS) {
//        if(secinterval!=true && distance2 == 0.0){
        dest.lat = rwyFarLat;
        dest.lon = rwyFarLon;
        BrgDst bd = GetBearingDistance(pos, dest);
        //courseError = ILSCourse - bd.bearing;  // course error (mag, deg)
        courseError = bd.bearing;  //heading for GS
        //std::cout << "data1:: " <<bd.distance<< std::endl;
       // distance = bd.distance - (rwyLen * ft2nm); // distance to approach end of runway (nm)
         distance = bd.distance*6076;
//       }  if(distance<500){
//                secinterval = true;
//                dest.lat = rwyNearLat;
//                dest.lon = rwyNearLon;
//                BrgDst bd = GetBearingDistance(pos, dest);
//                courseError = bd.bearing;
//                distance2 = bd.distance*6076;
//         }
      //  double a = bd.distance - ((rwyLen - 1080.0) * ft2nm);
        double a = distance;
         // std::cout << "data2:: " <<distance<< std::endl;
       // double b = (pos.alt - ILSTDZE) * ft2nm;
        double b = ILSTDZE; //GS altitude
        GSError = atan2(b, a)*r2d;
      //  std::cout << "gserror:: " <<b<< std::endl;
    }
}
