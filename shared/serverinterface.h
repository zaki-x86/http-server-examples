#ifndef __SERVERINTERFACE_H__
#define __SERVERINTERFACE_H__

#include <QObject>

#include "globals.h"
#include "request.h"
#include "response.h"
#include "qtcpserverwrapper.h"
#include "connectionhandler.h"

namespace http
{
    class IServer : public QObject {
    public:
        IServer(QObject* parent = 0) : QObject(parent) {}
        
        virtual ~IServer() {}

        virtual void listen(quint16 port, std::function<void()> callback = 0) = 0;

        virtual void close() = 0;

        virtual int serverPort() = 0;

        //void use(Router& router);
    
    protected:
        virtual void incomingConnection(qintptr socketDescriptor) = 0;
        virtual void onConnection(qintptr socketDescriptor) {
            incomingConnection(socketDescriptor);
        }

    private:
        friend class ConnectionHandler;
        virtual void handle(Request& request, Response& response) = 0;
    };

    //Q_DECLARE_INTERFACE(IServer, "IServer") // define this out of namespace scope

} // namespace http

#endif // __SERVERINTERFACE_H__