# http-server-examples

Examples of how to create an HTTP server based on Qt framework

I created 2 kinds of servers; blocking and non-blocking. Besides, other classes that are necessary to create a server, such as: Request, Response, and `QTcpServer` wrapper.

For simplicity - and also because we are only looking for results in these examples; The servers should echo back information about the request that they received - there are no fancy request handlers. Once you get the idea, you will be able to add your own request handler the way that suits your needs.

## Single-threaded Server

The single-threaded server examples handle only one request at a time. Therefore, it doesn't spawn any thread handlers to handle new incoming requests. It blocks requests until the one currently being handled is done.

## Multithreaded Server

Unlike the single-threaded server, it handles multiple requests concurrently by using a threadpool, (aka connection pool).

## Shared modules

Both implementations of the server class share commom objects, which are: `Request`, `Response`, `TcpServerWrapper`, and `ConnectionHandler`.
