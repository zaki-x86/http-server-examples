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
        ConnectionHandler(IServer* app, QObject* parent = nullptr);
        ~ConnectionHandler();
    
    public slots:
        void handleConnection(const qintptr socketDescriptor);

    private slots:
        void onReadyRead();
        void onReadyWrite(const char*);
        void onReadTimerTimeout();
        void onSocketDisconnected();
        void onSocketError(QAbstractSocket::SocketError);
    
    private:
        void _createSocket();

    private:
        IServer* m_App;
        QTcpSocket* m_Socket;
        QTimer* m_ReadTimer;
        Request* m_Request;
        Response* m_Response;
    };
} // namespace http

#endif // __CONNECTIONHANDLER_H__