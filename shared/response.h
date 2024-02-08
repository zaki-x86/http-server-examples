
#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QObject>

#include "globals.h"
#include "serverinterface.h"

namespace http
{
    class Response : public QObject {
        Q_OBJECT
    public:
        void send(Buffer& text, int status = 200);
        Buffer raw() const;

    signals:
        void responseReady(const char*);

    private:
        friend class ConnectionHandler;
        IServer* m_App;
        Request* m_Request;
        Buffer m_Body;
        BufferMap m_Headers;
        int m_Status;
        Buffer m_StatusDesc;
        bool m_HeadersSent;

    private:
        Response(IServer* app, Request* req, QObject* parent = 0);
    };

    
} // namespace http


#endif // HTTPRESPONSE_H
