#include "mgserver.h"

using namespace MegaGo::Server;

MGServer::MGServer(QObject* parent) : QTcpServer(parent) {}

MGServer::~MGServer() {
    for (auto client : clients) client->deleteLater();
}

void MGServer::Start(quint16 port) {
    listen(QHostAddress::Any, port);
}

void MGServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket* client = new QTcpSocket(this);
    client->setSocketDescriptor(socketDescriptor);
    MGClient * newClient = new MGClient(client, this);
    clients.append(newClient);

    connect(client, &QTcpSocket::readyRead, this, &MGServer::OnReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &MGServer::OnDisconnected);

    emit ClientConnected(client);
}

void MGServer::OnReadyRead() {
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (client) emit DataReceived(client, client->readAll());
}

void MGServer::OnDisconnected() {
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (client) {
        for(int cid=0;cid<clients.size();cid++) {
            if(clients[cid] != nullptr)
            if(clients[cid]->GetSocket() == client) {
                clients.erase(clients.begin()+cid);
                client->deleteLater();
            }
        }
        emit ClientDisconnected(client);
    }
}

void MGServer::SendToAll(const QByteArray& data) {
    for (auto client : clients) if(client != nullptr) client->GetSocket()->write(data);
}

void MGServer::SendToClient(QTcpSocket* client, const QByteArray& data) {
    if (client) client->write(data);
}

MGClient* MGServer::GetClient(QTcpSocket *socket)
{
    try {
        for(int cid=0;cid<clients.size();cid++) {
            if(clients[cid]->GetSocket() == socket)
                return clients[cid];
            else throw "MGServer::GetClient: cant find client data";
        }
    } catch(const char* err) { qDebug() << err; return nullptr; }
}

void MGServer::Login(QTcpSocket* client, QString username, QString password)
{
    // select username + password from bd
    // if empty throw error
    // if found ->
    QString nickname;
    int imgId;
    int64_t playedGames,wonGames,lostGames,eatenTokens;
    int16_t firstSurrender;
    //nickname = bd->query("get_nickname(username);");
    //todo:
    MegaGo::Model::ClientAccount clientData;
    MegaGo::Model::ClientStatistic stats;
    stats.playedGames = playedGames;
    stats.wonGames = wonGames;
    stats.lostGames = lostGames;
    stats.eatenTokens = eatenTokens;
    stats.firstSurrender = firstSurrender;
    clientData.Set(username,password,nickname,imgId);
    clientData.SetStats(stats);
    this->GetClient(client)->SetAccountData(clientData);
}

void MGServer::CreateRoom(QTcpSocket* client, QString name, MegaGo::Model::RoomSettings settings)
{

}

void MGServer::JoinRoom(QTcpSocket* client, uint64_t roomGID)
{

}

void MGServer::ChangeRoomSettings(QTcpSocket* client, MegaGo::Model::RoomSettings roomSettings, MegaGo::Model::GameModeSettings gamemodeSettings)
{

}

void MGServer::ExitRoom(QTcpSocket* client, uint64_t roomGID)
{

}

void MGServer::KickPlayer(QTcpSocket* client, uint64_t roomGID, uint64_t clientGID)
{

}

void MGServer::ChangeColor(QTcpSocket* client, uint64_t colorGID)
{

}

void MGServer::DeleteRoom(QTcpSocket* client, uint64_t roomGID)
{

}
