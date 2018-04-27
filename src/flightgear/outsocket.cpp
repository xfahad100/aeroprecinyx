#include "outsocket.h"

OutSocket::OutSocket()
{
    hostAddress = QHostAddress::LocalHost;
    packet = new Packet();
    connected = false;
    socket = new QUdpSocket();
    port = 0;
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
    if (p==port) return;      // don't bind twice
    port = p;
    connected = true;
    //connected = socket->bind(port, QUdpSocket::ShareAddress);
    if (!connected) {
        qWarning("Flightgear socket failed to bind!");
    } else {
        qWarning("Flightgear socket port is bound.");
    }
}

qint64 OutSocket::Send()
{
    FGNetFDM* datagram = packet->getPacketPtr();
    return socket->writeDatagram(QByteArray((char*)datagram, sizeof(FGNetFDM)),
                                 hostAddress, port);
}
