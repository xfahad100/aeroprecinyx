#include "outsocket.h"

OutSocket::OutSocket()
{
    hostAddress = QHostAddress::LocalHost;
    packet = new Packet();
    connected = false;
    socket = new QUdpSocket();
    port = 0;
    size = sizeof(FGNetFDM);
}

OutSocket::~OutSocket()
{
    delete packet;
    delete socket;
}

Packet* OutSocket::getPacket()
{
    return packet;
}

void OutSocket::setPort(int p)
{
    port = p;
    connected = true;
}

qint64 OutSocket::Send()
{
    FGNetFDM* datagram = packet->getPacketPtr();
    return socket->writeDatagram(QByteArray((char*)datagram, size),
                                 hostAddress, port);
}
