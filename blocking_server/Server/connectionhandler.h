#ifndef __CONNECTIONHANDLER_H__
#define __CONNECTIONHANDLER_H__

#include "globals.h"

#include <QTcpSocket>
#include <QTimer>

namespace http
{
    class ConnectionHandler : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY(ConnectionHandler)
    public:
        ConnectionHandler(Handler handle, QObject* parent = nullptr);
        ~ConnectionHandler();
    
    public slots:
        void handleConnection(const qintptr socketDescriptor);

    private slots:
        void onReadyRead();
        void onSocketError(QAbstractSocket::SocketError );
        void onThreadDone();
        void onReadTimerTimeout();
        void onSocketDisconnected();
    
    private:
        void _createSocket();

    private:
        QTcpSocket m_Socket;
        QTimer m_ReadTimer;
        Handler m_Handler;
    };
} // namespace http

#endif // __CONNECTIONHANDLER_H__