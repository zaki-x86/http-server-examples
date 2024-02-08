#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

#include "globals.h"
#include <QHttp.h>


namespace http
{
    using RequestParser = QHttp::RequestParser;

    class Request
    {
    public:
        Request(Server& app, Response& res) 
            : m_App(app), m_Res(res)
        {

        }

        ~Request() {}

        Server& app() const {
            return m_App;
        }

        Response& res() const {
            return m_Res;
        }

        const RequestParser& parser() const {
            return m_Parser;
        }

        const Buffer& method() const {
            return m_Parser.method();
        }

        const Buffer& version() const {
            return m_Parser.version();
        }

        const Buffer& body() const{
            return m_Parser.body();
        }

        const Buffer& get(Buffer& name) const {
            return m_Parser.headers()[name];  
        }

    private:
        RequestParser m_Parser;
        Server& m_App;
        Response& m_Res;
    };
    
} // namespace http


#endif // !HTTP_REQUEST_H_