#include "connectionhandler.h"


http::ConnectionHandler::ConnectionHandler(Handler handle, QObject *parent) 
    :m_Handler(handle), QObject(parent) {
}

http::ConnectionHandler::~ConnectionHandler() {
}

void http::ConnectionHandler::handleConnection(const qintptr socketDescriptor) {

}

void http::ConnectionHandler::onReadyRead() {

}

void http::ConnectionHandler::onSocketError(QAbstractSocket::SocketError ) {

}

void http::ConnectionHandler::onThreadDone() {

}

void http::ConnectionHandler::onReadTimerTimeout() {

}

void http::ConnectionHandler::onSocketDisconnected() {

}
