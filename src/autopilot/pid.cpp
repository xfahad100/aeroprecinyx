#ifndef _PID_SOURCE_
#define _PID_SOURCE_

#include "pid.h"



using namespace std;

class PIDImpl
{
    public:
        PIDImpl( double dt, double max, double min, double Kp, double Kd, double Ki );
        ~PIDImpl();
        double calculate( double dt, double setpoint, double pv );

    private:
        double _dt;
        double _max;
        double _min;
        double _Kp;
        double _Kd;
        double _Ki;
        double _pre_error;
        double _integral;
        double Iout;
        double outputprev;
};


PID::PID( double dt, double max, double min, double Kp, double Kd, double Ki )
{
    pimpl = new PIDImpl(dt,max,min,Kp,Kd,Ki);
}
double PID::calculate( double dt, double setpoint, double pv )
{
    return pimpl->calculate(dt, setpoint, pv);
}
PID::~PID() 
{
    delete pimpl;
}


/**
 * Implementation
 */
PIDImpl::PIDImpl( double dt, double max, double min, double Kp, double Kd, double Ki ) :
    _dt(dt),
    _max(max),
    _min(min),
    _Kp(Kp),
    _Kd(Kd),
    _Ki(Ki),
    _pre_error(0),
    _integral(0)
{
}

double PIDImpl::calculate( double dt, double setpoint, double pv )
{
    
    // Calculate error
    double error = setpoint - pv;
   // std::cout << "set:: " <<setpoint<< endl;
   // std::cout << "pv:: " <<pv<< endl;
//std::cout << "error:: " <<error<< endl;

    // Proportional term
    double Pout = _Kp * error;

    // Integral term
   _integral = error * dt;

 //_integral += (1.5*error - 0.5*_pre_error) * dt;  // 2nd order Adams Bashforth integrator
    Iout = _Ki * _integral;
   Iout += Iout;
   // Derivative term
    double derivative = (error - _pre_error) / dt;
    double Dout = _Kd * derivative;

    // Calculate total output
    double output = Pout + Iout + Dout;

    //double output = _Kp * (error + Iout + Dout);
//    std::cout << "output:: " <<output<< endl;
//std::cout << "Pout:: " <<double(Pout)<< endl;
//std::cout << "Iout:: " <<double(Iout)<< endl;
//std::cout << "Dout:: " <<Dout<< endl;
    // Restrict to max/min
    if( output > _max )
        output = _max;
    else if( output < _min )
        output = _min;

    // Save error to previous error
    _pre_error = error;

//    output = output + outputprev*0.01;

//    outputprev = output;
    return output;
}

PIDImpl::~PIDImpl()
{
}

#endif
