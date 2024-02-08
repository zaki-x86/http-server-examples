#include "qtcpserverwrapper.h"

using namespace http;

TcpServerWrapper::TcpServerWrapper(QObject *parent) 
    : QTcpServer(parent)
{
}

void TcpServerWrapper::incomingConnection(qintptr socketDescriptor)
{
    emit newConnection(socketDescriptor);
}