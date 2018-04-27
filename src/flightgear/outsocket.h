#ifndef OUTSOCKET_H
#define OUTSOCKET_H

#include <QUdpSocket>
#include <QtNetwork>
#include "packet.h"

class OutSocket
{

public:
    OutSocket();
    ~OutSocket();
    Packet* getPacket();
    void setPort(int p);
    qint64 Send();
    inline bool Connected() { return connected; }

private:
    QUdpSocket* socket;
    QHostAddress hostAddress;
    bool connected;
    int port;
    Packet* packet;
};

#endif // OUTSOCKET_H
