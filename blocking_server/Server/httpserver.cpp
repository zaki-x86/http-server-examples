#include "httpserver.h"

namespace http
{
    Server::Server(QObject* parent)
        : IServer(parent), m_Server()
    {
        qDebug() << "Server: Initializing\n";
        qRegisterMetaType<qintptr>("qintptr");
        connect(&m_Server, &TcpServerWrapper::newConnection, this, &Server::onConnection);
    }
    
    Server::~Server()
    {
        
    }
    
    void Server::listen(quint16 port, std::function<void()> callback)
    {
        m_Server.listen(QHostAddress::Any, port);
        callback();
    }
    
    void Server::close()
    {
        m_Server.close();
    }
    
    int Server::serverPort()
    {
        return m_Server.serverPort();
    }
    
    void Server::incomingConnection(qintptr socketDescriptor)
    {
        qDebug() << "Server: Detected new incoming connection\n";
        
        m_Handler = new ConnectionHandler(this);
        m_Handler->handleConnection(socketDescriptor);
        //QMetaObject::invokeMethod(m_Handler, "handleConnection", Qt::DirectConnection, Q_ARG(qintptr, socketDescriptor));
    }
    
    void Server::handle(Request& request, Response& response)
    {
        // echo request
        Buffer res = "Recieved HTTP: " + request.method() + "\n"
                        + "Requested URL: " + request.url() + "\n"
                        + "Hello world!";
        response.send(res);
    }
}