#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include <QObject>

#include "globals.h"
#include "request.h"
#include "response.h"
#include "qtcpserverwrapper.h"
#include "connectionhandler.h"

namespace http
{
    class Server : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY(Server)

    public:
        Server(QObject* parent = 0);
        ~Server();

        void listen(quint16 port, std::function<void()> callback = 0);

        void close();

        int serverPort();

        //void use(Router& router);
    
    protected:
        virtual void incomingConnection(qintptr socketDescriptor);

    private:
        void onConnection(qintptr socketDescriptor);

    private:
        TcpServerWrapper m_Server;
    };
} // namespace networxx


#endif // __HTTPSERVER_H__