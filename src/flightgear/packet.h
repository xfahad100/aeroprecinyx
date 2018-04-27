#ifndef PACKET_H
#define PACKET_H

#include <netinet/in.h>
#include "net_fdm.hxx"
#include <chrono>

class Packet
{
public:
    Packet();
    ~Packet();
    void Init();
    bool EndianTest();               // returns true if little-endian
    void htond(double &x);
    void htonf(float &x);

    void setLongitude(double lon);   // degrees
    void setLatitude(double lat);    // degrees
    void setAltitude(double alt);    // feet MSL
    void setRoll(float r);           // degrees
    void setPitch(float p);          // degrees
    void setTrueHdg(float y);        // degrees
    void setVelocity(float v);       // knots calibrated airspeed
    void setClimbRate(float c);      // feet per minute
    void setAltAGL(float a);         // feet AGL

    FGNetFDM* getPacketPtr();

private:
    FGNetFDM* packet;
    bool isLittleEndian;
    float DEFAULT_VISIBILITY;
    double DEG2RAD;
    double FT2M;
    uint32_t DEFAULT_TIME;
};

#endif // PACKET_H
