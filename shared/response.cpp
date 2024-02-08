#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include "response.h"

using namespace http;

Response::Response(Server& app, Request& req, QObject* parent)
    : m_App(app), m_Request(req), QObject(parent)
{
    m_Status = 404;
    m_StatusDesc = "Internal Server Error";
    m_Body = "";
    m_Headers["Content-Type"] = "text/plain";
    m_Headers["Content-Length"] = Buffer::number(m_Body.size());
    m_Headers["Connection"] = "keep-alive";
    m_Headers["Server"] = "QHttpServer";
}

void Response::send(Buffer& text, int status) {
    m_Status = status;
    m_StatusDesc = "OK";
    m_Body = text;
    m_Headers["Content-Length"] = Buffer::number(m_Body.size());
    
    emit responseReady(raw().constData());
    m_HeadersSent = true;
}

Buffer Response::raw() const {
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
    //     buffer.append(cookie.raw());
    //     buffer.append("\r\n");
    // }
    buffer.append("\r\n");
    buffer.append(m_Body);
    buffer.append("\r\n");
    return buffer;
}

#endif // __RESPONSE_H__