#include <QCoreApplication>
#include "Server/httpserver.h"

int main(int argc, char** argv)
{
    QCoreApplication qt(argc, argv);

    using namespace http;
    Server app;
    
    app.listen(8080, [&app](){
        qDebug() << "Server started listening on port: " << app.serverPort();
    });

    return qt.exec();
}
