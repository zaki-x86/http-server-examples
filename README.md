# http-server-examples

Examples of how to create an HTTP server based on Qt framework

## Blocking Server

The blocking server examples handles only one request at a time. Therefore, it doesn't spawn any thread handlers to handle new incoming requests concurrently.

## Non-blocking Server

Unlike the non-blocking server, it handlers multiple requests concurrently - but not efficiently though. Another better way to handle multiple requests is by using a threadpool, or connection pool which will be added to extend this example later.
