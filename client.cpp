#include "client.h"

using namespace MegaGo::Server;

MGClient::MGClient()
{
    socket = nullptr;
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

void MGClient::SetSocket(QTcpSocket *connection)
{
    if(connection->isValid()) {
        socket = connection;
    }
}

QTcpSocket* MGClient::GetSocket()
{
    return socket;
}
