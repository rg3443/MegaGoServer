#include "MGServer.h"

using namespace MegaGo::Server;

MGServer::MGServer(QObject* parent) : QTcpServer(parent) {}

MGServer::~MGServer() {
    for (auto client : clients) client->deleteLater();
}

void MGServer::start(quint16 port) {
    listen(QHostAddress::Any, port);
}

void MGServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket* client = new QTcpSocket(this);
    client->setSocketDescriptor(socketDescriptor);
    clients.append(client);

    connect(client, &QTcpSocket::readyRead, this, &MGServer::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &MGServer::onDisconnected);

    emit clientConnected(client);
}

void MGServer::onReadyRead() {
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (client) emit dataReceived(client, client->readAll());
}

void MGServer::onDisconnected() {
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (client) {
        clients.removeOne(client);
        client->deleteLater();
        emit clientDisconnected(client);
    }
}

void MGServer::sendToAll(const QByteArray& data) {
    for (auto client : clients) client->write(data);
}

void MGServer::sendToClient(QTcpSocket* client, const QByteArray& data) {
    if (client) client->write(data);
}
