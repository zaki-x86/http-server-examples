#include <QMap.h>
#include <QByteArray.h>

#include <functional>
#include <exception>

using Buffer = QByteArray;
using BufferMap = QMap<Buffer, Buffer>;

namespace http {
    class Request;
    class Response;
    class Server;
    class ConnectionHandler;
    class Router;

    class IServer;

    using Next = std::function<void(std::exception_ptr)>;
    using Handler = std::function<void(Request&, Response&, Next)>;
}