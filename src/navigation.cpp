#include "navigation.h"

navigation::navigation()
{

}

void navigation::SetMagVar(double var) {magvar=var;}
void navigation::SetILSRunwayEndPoints(double nearLat, double nearLon,
                                       double farLat, double farLon)
   {rwyNearLat=nearLat; rwyNearLon=nearLon; rwyFarLat=farLat; rwyFarLon=farLon;}
void navigation::SetILSFrequency(float freq) {ILSfreq=freq;}
void navigation::SetILSCourseMag(double course) {ILSCourse=course;}
void navigation::SetILSGS(double gs) {ILSGS=gs;}
void navigation::SetILSTDZE(double elev) {ILSTDZE=elev;}
void navigation::SetPosition(double lat, double lon, double alt)
   {posLat=lat; posLon=lon; posAlt=alt;}
void navigation::SetTrueHeading(double hdg) {trueHdg=hdg;}

double navigation::GetMagHdg() {return trueHdg-magvar;}
