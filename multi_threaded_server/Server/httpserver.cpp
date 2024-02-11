#include "httpserver.h"

namespace http
{
    Server::Server(IServer* parent)
        : IServer(parent), m_Server()
    {
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
        
    }
    
    void Server::handle(Request& request, Response& response)
    {
        response.send("Hello world!");
    }

}