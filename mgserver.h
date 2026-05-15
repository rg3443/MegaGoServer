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
        void start(quint16 port);

        void sendToAll(const QByteArray& data);
        void sendToClient(QTcpSocket* client, const QByteArray& data);

    signals:
        void clientConnected(QTcpSocket* client);
        void clientDisconnected(QTcpSocket* client);
        void dataReceived(QTcpSocket* client, const QByteArray& data);

    protected:
        void incomingConnection(qintptr socketDescriptor) override;

    private slots:
        void onReadyRead();
        void onDisconnected();

    private:
        QVector<QTcpSocket*> clients;
    };

}
}

#endif // MGSERVER_H
