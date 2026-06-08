#include "client.h"

using namespace MegaGo::Server;

MGClient::MGClient(QTcpSocket * connection, QObject * parent)
    : QObject(parent)
{
    socket = nullptr;
    if(connection->isValid()) {
        socket = connection;
    }
}

MGClient::~MGClient()
{
    if(socket != nullptr) socket->deleteLater();
}

void MGClient::SetAccountData(ClientAccount data)
{
   // accountData = data;
}

MegaGo::Model::ClientAccount* MGClient::GetAccountData()
{
    if(!socket->isValid()) return nullptr;

    return &accountData;
}

QTcpSocket* MGClient::GetSocket()
{
    return socket;
}
