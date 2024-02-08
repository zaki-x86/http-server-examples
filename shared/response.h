
#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "globals.h"


namespace http
{
    class Response {
    public:
        Response(Server& app, Request& req)
            : m_App(app), m_Request(req)
        {
            m_Status = 404;
            m_StatusDesc = "Internal Server Error";
            m_Body = "";
            m_Headers["Content-Type"] = "text/plain";
            m_Headers["Content-Length"] = Buffer::number(m_Body.size());
            m_Headers["Connection"] = "close";
            m_Headers["Server"] = "QHttpServer";
        }
        
        Response send(QString text, int status = 200) {
            m_Status = status;
            m_StatusDesc = "OK";
            m_Body = text.toUtf8();
            return *this;
        }

        Buffer toByteArray() {
            Buffer buffer;
            buffer.append("HTTP/1.1 ");
            buffer.append(Buffer::number(m_Status));
            buffer.append(' ');
            buffer.append(m_StatusDesc);
            buffer.append("\r\n");
            foreach(Buffer name, m_Headers.keys())
            {
                buffer.append(name);
                buffer.append(": ");
                buffer.append(m_Headers.value(name));
                buffer.append("\r\n");
            }
            // foreach(Cookie cookie,cookies.values())
            // {
            //     buffer.append("Set-Cookie: ");  
            //     buffer.append(cookie.toByteArray());
            //     buffer.append("\r\n");
            // }
            buffer.append("\r\n");
            buffer.append(m_Body);
            return buffer;
        }


    private:
        Server& m_App;
        Request& m_Request;
        Buffer m_Body;
        BufferMap m_Headers;
        int m_Status;
        Buffer m_StatusDesc;

    private:
        Response(QString text, int status, Server& app, Request& req)
            : m_App(app), m_Request(req)
        {
            //m_Headers["Date"] = "Mon, 27 Jul 2009 12:28:53 GMT";
            //m_Headers["Last-Modified"] = "Mon, 27 Jul 2009 12:28:53 GMT";
            //m_Headers["Accept-Ranges"] = "bytes";
            //m_Headers["Content-Encoding"] = "gzip";
            //m_Headers["Vary"] = "Accept-Encoding";
            //m_Headers["Pragma"] = "no-cache";
            //m_Headers["Cache-Control"] = "no-cache";
        }
    };

    
} // namespace http


#endif // HTTPRESPONSE_H
