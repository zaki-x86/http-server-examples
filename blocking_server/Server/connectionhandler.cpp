#include "connectionhandler.h"

#include "request.h"
#include "response.h"
#include "httpserver.h"


http::ConnectionHandler::ConnectionHandler(Server* app, QObject *parent) 
    :m_App(app), QObject(parent) {
        qDebug() << "ConnectionHandler::ConnectionHandler initializing signals and slots";

        _createSocket();
        m_ReadTimer = new QTimer();
        m_Request = new Request(*m_App, *m_Response);
    m_Response = new Response(*m_App, *m_Request);
        m_ReadTimer->setSingleShot(true);

        connect(m_Socket, &QTcpSocket::readyRead, this, &ConnectionHandler::onReadyRead);
        connect(m_Response, &Response::responseReady, this, &ConnectionHandler::onReadyWrite);
        connect(m_Socket, &QTcpSocket::disconnected, this, &ConnectionHandler::onSocketDisconnected);
        connect(m_ReadTimer, &QTimer::timeout, this, &ConnectionHandler::onReadTimerTimeout);
        connect(m_Socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));

        qDebug() << "ConnectionHandler::ConnectionHandler initialized signals and slots";
}

http::ConnectionHandler::~ConnectionHandler() {
    qDebug() << "ConnectionHandler: Destructor\n";
    m_Socket->close();
    m_ReadTimer->stop();

    delete m_Socket;
    delete m_ReadTimer;

    qDebug() << "ConnectionHandler: Destructor done\n";
}

void http::ConnectionHandler::_createSocket() {
    m_Socket = new QTcpSocket();
}

void http::ConnectionHandler::handleConnection(const qintptr socketDescriptor) {
    qDebug() << "ConnectionHandler: New connection\n";
    
    if (m_Socket->state() == QAbstractSocket::UnconnectedState) {
        if(!m_Socket->setSocketDescriptor(socketDescriptor)) {
            qDebug() << "Connection Handler: Error setting socket descriptor\n";
        }
    }

    qDebug() << "ConnectionHandler: Connected " << "to socket: " << m_Socket->socketDescriptor();

    m_ReadTimer->start(30000); // 30 sec max for read request
}

void http::ConnectionHandler::onReadyRead() {
    qDebug() << "ConnectionHandler: Ready read\n";
    
    while (m_Socket->bytesAvailable())
    {
        auto buf = m_Socket->readAll();
        m_Request->parse(buf);

        m_App->handle(*m_Request, *m_Response, nullptr);

        qDebug() << "Writing: " << m_Response->raw();
    }

    m_ReadTimer->stop();
    m_Socket->close();
}

void http::ConnectionHandler::onReadyWrite(const char* buf) {
    // write response to socket
    m_Socket->write(buf);
    m_Socket->flush();
    m_Socket->waitForBytesWritten();
}

void http::ConnectionHandler::onSocketError(QAbstractSocket::SocketError err) {
    qDebug() << "Connection Handler: Socket error\n";
    if (err == QAbstractSocket::RemoteHostClosedError) {
        qDebug() << "Connection Handler: Remote host closed\n";
    } else if (err == QAbstractSocket::ConnectionRefusedError) {
        qDebug() << "Connection Handler: Connection refused\n";
    } 

    m_Socket->close();
}

void http::ConnectionHandler::onReadTimerTimeout() {
    qDebug() << "ConnectionHandler: Read timer timeout\n";
    m_ReadTimer->stop();
    m_Socket->close();
}

void http::ConnectionHandler::onSocketDisconnected() {
    qDebug() << "ConnectionHandler: Socket disconnected\n";
    m_Socket->close();
}
