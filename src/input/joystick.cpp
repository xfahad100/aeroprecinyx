#include "joystick.h"

Joystick::Joystick()
{
    js = new jsJoystick();    // jsJoystick is defined in PLIB
    ax = new float[16];
    b  = new int[32];
    deadband = new float[3];

    for (int i=0; i<16; i++) {
       ax[i] = -1.0;
    }
    for (int i=0; i<32; i++) {
       b[i] = 0.0;
    }

    // -1 signifies not assigned yet
    elevator_axis = aileron_axis = rudder_axis = -1;
    elevator_trim_axis = aileron_trim_axis = throttle_axis = -1;
    deadband[0] = deadband[1] = deadband[2] = 0.0;
}

void Joystick::Init()
{
    jsInit();
    numAxes = js->getNumAxes();
    numButtons = js->getNumButtons();
}

void Joystick::Read()
{
    js->read(&buttons, ax);

    for (uint i=0; i<(uint)numButtons; i++){
        b[i] = buttons & 1;
        buttons = buttons >> 1;
    }
}

QString Joystick::getName()
{
    return js->getName();
}

bool Joystick::notWorking()
{
    return js->notWorking();
}

void Joystick::setDeadbands(float axis0, float axis1, float axis2)
{
    deadband[0] = axis0;
    deadband[1] = axis1;
    deadband[2] = axis2;

    if (!notWorking()) {
      if (numAxes>0) js->setDeadBand(0, deadband[0]);
      if (numAxes>1) js->setDeadBand(1, deadband[1]);
      if (numAxes>2) js->setDeadBand(2, deadband[2]);
    }
}

double Joystick::getAileron()
{
   if (aileron_axis >= 0) return ax[aileron_axis];
   return 0.0;
}

double Joystick::getElevator()
{
   if (elevator_axis >= 0) return -ax[elevator_axis];
   return 0.0;
}

double Joystick::getRudder()
{
   if (rudder_axis >= 0) return -ax[rudder_axis];
   return 0.0;
}

double Joystick::getThrottle()
{
   if (throttle_axis >= 0) return (ax[throttle_axis]-1.0)/-2.0;
   return 0.0;
}

double Joystick::getAileronTrim()
{
   if (aileron_trim_axis >= 0) return ax[aileron_trim_axis];
   return 0.0;
}

double Joystick::getElevatorTrim()
{
   if (elevator_trim_axis >= 0) return ax[elevator_trim_axis];
   return 0.0;
}

bool Joystick::getButtonState(int index)
{
    if ( 0 <= index && index < 33) return (bool)b[index];
    return false;
}

Joystick::~Joystick()
{
    delete js;
    delete ax;
    delete b;
    delete deadband;
}
