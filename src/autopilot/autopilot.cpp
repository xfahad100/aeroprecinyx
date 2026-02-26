 #include "autopilot.h"

autopilot::autopilot()
{
    ap_elevator = desiredPitch = desiredAlt = 0.0;
    ap_aileron = desiredBank = desiredCrs = 0.0;
    desiredHdg = desiredVS = headingRotation = CorrectedHeading = 0.0;
   // VMode = VertSpeed;
   // LMode = Heading;
    engaged = false;
                                /// "P", "D", "I" ///
    vsPID = new PID(0.01, 0.45, -0.45, 0.1, 0.00005, 0.008);
    ydPID = new PID(0.01, 0.25, -0.25, 0.1, 0.05, 0.5);
    baPID = new PID(0.01, 0.25, -0.25, 0.35, 0.2, 0.005);  // fine tuned vals kp = 0.35, kd= 0.2 , ki = 0.005
    vPID = new PID(0.01, 15, -15, 1, 0.0004, 0.001);
    wlPID = new PID(0.01, 0.25, -0.25, 1, 0.001, 0.04);
    lPID = new PID(0.01, 10, -10, 0.75, 0.001, 0.002);
    vviPID = new PID(0.01, 0.3, -0.3, 0.075, 0.00003, 0.008);
}

void autopilot::setEngaged( bool engage ) { engaged = engage; }
void autopilot::setVMode( vMode mode ) { VMode = mode; }
void autopilot::setLMode( lMode mode ) { LMode = mode; }
void autopilot::setDesiredAlt(double alt) { desiredAlt = alt; }
void autopilot::setDesiredCrs(double crs) { desiredCrs = crs; }
void autopilot::setDesiredHdg( double hdg ) { desiredHdg = hdg; }
void autopilot::setDesiredVS( double vs ) { desiredVS = vs; }

double autopilot::getFDPitchCmd() { return desiredPitch; }
double autopilot::getFDRollCmd() { return desiredBank; }

autopilot::vMode autopilot::getVMode() { return VMode; }
autopilot::lMode autopilot::getLMode() { return LMode; }

bool autopilot::getEngaged() { return engaged; }

void autopilot::mainLoop(double dt)
{

}

double autopilot::updateVMode(double dt, double pitch,double altitude, double alt, double desGS)
{
   switch (VMode)
   {
     case AltHold:

       desiredPitch = vPID->calculate(dt, desiredAlt, altitude);
       ap_elevator = -vsPID->calculate(dt, desiredPitch, pitch);

       break;
     case VertSpeed:

       //// Caculation of error and error rate for determining KP KI and KD
       if(alt < 0) {
           _alt = -alt;
       }
       else if (alt > 0) {
           _alt = -alt;
       }
       else {
           _alt = alt;
       }
       if(desiredVS > 0) {
           _desiredVS = -desiredVS;
       }
       else if(desiredVS < 0) {
           _desiredVS = -desiredVS;
       }
       else {
           _desiredVS = desiredVS;
       }
      desiredPitch = vPID->calculate(dt, _desiredVS, _alt);
       ap_elevator = vviPID->calculate(dt, desiredPitch, pitch);

       break;
     case Speed:
       break;
     case VNAV:
       break;
     case ILS:
          ap_elevator = vviPID->calculate(dt, desGS, alt);
       break;
     default:
       ap_elevator = 0.0;
   }

   return ap_elevator;
}

double autopilot::updateydMode(double dt, double desiredrate, double yawrate)
{

      // ap_rudder = ydPID->calculate(dt, desiredrate, yawrate);
      // ap_rudder = 0.01* ap_rudder;

   return ap_rudder;
}

double autopilot::updateLMode(double dt, double roll, double yaw, double navc, double rollrate, double altG)
{
    switch (LMode)
    {
      case Winglevel:
        ap_aileron = wlPID->calculate(dt, 0.0, roll);
        break;

      case Heading:


//        ldb = desiredHdg - yaw;
//        if (ldb > 180)
//        { headingRotation = -360;}
//        else if (ldb < -180)
//        { headingRotation = 360;}
//        CorrectedHeading = ldb + headingRotation;
        if(altG > 10){
            ap_rudder = 0;
            if (desiredHdg > 180){ desiredHdg = desiredHdg - 360;
             }
       if (desiredHdg > 180){ desiredHdg = desiredHdg - 360;
        }
       if(yaw < 360 && yaw > 180){
        ldb = yaw - 360;  //convert 360 to 180 -> 0 to -180
        desiredBank = lPID->calculate(dt, desiredHdg, ldb);
       }
       else {
           desiredBank = lPID->calculate(dt, desiredHdg, yaw);
             }
    ap_aileron = baPID->calculate(dt, desiredBank, roll);
        }
        else {
            ap_aileron = 0;
//            if(yaw < 360 && yaw > 180){
//             ldb = yaw - 360;  //convert 360 to 180 -> 0 to -180
//             ap_rudder = ydPID->calculate(dt, desiredHdg, ldb);
//            }
//            else {
//               ap_rudder = ydPID->calculate(dt, desiredHdg, yaw);
//            }
             ap_rudder = -ydPID->calculate(dt, desiredHdg, yaw);

        }
    //std::cout << "yaw " <<yaw<< std::endl;
//       if (navc > 180){ navc = navc - 360;
//        }
//       if(yaw < 360 && yaw > 180){
//        ldb = yaw - 360;  //convert 360 to 180 -> 0 to -180
//        desiredBank = lPID->calculate(dt, navc, ldb);
//       }
//       else {
//           desiredBank = lPID->calculate(dt, navc, yaw);
//       }

//ap_rudder = baPID->calculate(dt, desiredBank, roll);
        break;
      case LNAV:
        break;
      case LOC:
        break;
      case LNone:
        ap_aileron = 0.0;
        break;
      default:
        ap_aileron = 0.0;
    }

   return ap_aileron;
}

autopilot::~autopilot()
{
    delete vsPID;
    delete baPID;
    delete vPID;
    delete lPID;
    delete ydPID;
    delete wlPID;
    delete vviPID;
}
