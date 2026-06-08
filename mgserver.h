#ifndef MGSERVER_H
#define MGSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

#include "client.h"
#include "model/server/room.h"

namespace MegaGo {
namespace Server {

    class MGServer : public QTcpServer {
    Q_OBJECT
    public:
        explicit MGServer(QObject* parent = nullptr);
        ~MGServer();
        void Start(quint16 port);

        void SendToAll(const QByteArray& data);
        void SendToClient(QTcpSocket* client, const QByteArray& data);

        MGClient* GetClient(QTcpSocket* socket);

    signals:
        void ClientConnected(QTcpSocket* client);
        void ClientDisconnected(QTcpSocket* client);
        void DataReceived(QTcpSocket* client, const QByteArray& data);

    protected:
        void incomingConnection(qintptr socketDescriptor) override;

    private slots:
        void OnReadyRead();
        void OnDisconnected();

        // login menu
        void Login(QTcpSocket* client, QString username, QString password);

        // main menu
        void CreateRoom(QTcpSocket* client, QString name, MegaGo::Model::RoomSettings settings);
        //void ChangeSettings(QTcpSocket* client, MegaGo::Model::Sett);
        void JoinRoom(QTcpSocket* client, uint64_t roomGID);

        // Room menu
        void ChangeRoomSettings(QTcpSocket* client, MegaGo::Model::RoomSettings roomSettings, MegaGo::Model::GameModeSettings gamemodeSettings);
        void ExitRoom(QTcpSocket* client, uint64_t roomGID);
        void KickPlayer(QTcpSocket* client, uint64_t roomGID, uint64_t clientGID);
        void ChangeColor(QTcpSocket* client, uint64_t colorGID);
        void DeleteRoom(QTcpSocket* client, uint64_t roomGID);

    private:
        QVector<MGClient*> clients;
        QVector<MegaGo::Model::Room*> rooms; // todo:
    };

}
}

#endif // MGSERVER_H
