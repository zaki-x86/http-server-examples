#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include <QObject>

#include "globals.h"
#include "request.h"
#include "response.h"
#include "qtcpserverwrapper.h"
#include "serverinterface.h"
#include "connectionhandler.h"

#include <QThread>
namespace http
{
    class Server : public IServer {
        Q_OBJECT
        Q_DISABLE_COPY(Server)

    public:
        Server(IServer* parent = 0);
        ~Server();

        void listen(quint16 port, std::function<void()> callback = 0) override;

        void close() override;

        int serverPort() override;

        //void use(Router& router);
    
    protected:
        void incomingConnection(qintptr socketDescriptor) override;

    private:
        void handle(Request& request, Response& response) override;

    private:
        TcpServerWrapper m_Server;
        
    };
} // namespace networxx


#endif // __HTTPSERVER_H__