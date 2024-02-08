#ifndef TCPSERVERWRAPPER_H
#define TCPSERVERWRAPPER_H

#include <QtNetwork/QTcpServer>

namespace http {

    class TcpServerWrapper : public QTcpServer
    {
        Q_OBJECT
    public:
        explicit TcpServerWrapper(QObject *parent = 0);

    signals:
        void newConnection(qintptr socketDescriptor);

    protected:
        void incomingConnection(qintptr socketDescriptor) override;
    };
    
} // namespace http



#endif // TCPSERVERWRAPPER_H