#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QVector>
#include "model/accounts/clientaccount.h"

using namespace MegaGo::Model;

namespace MegaGo {
namespace Server {
    class MGClient : public QObject {
    Q_OBJECT
    private:
        QTcpSocket * socket;
        ClientAccount accountData;
    public:
        MGClient(QTcpSocket * connection, QObject * parent);
        ~MGClient();

        void SetAccountData(ClientAccount data);
        ClientAccount * GetAccountData();

        QTcpSocket* GetSocket();
    };
}
}

#endif // CLIENT_H
