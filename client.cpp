#include "client.h"

using namespace MegaGo::Server;

MGClient::MGClient()
{

}

MGClient::~MGClient()
{

}

void MGClient::SetAccountData(ClientAccount data)
{
   // accountData = data;
}

MegaGo::Model::ClientAccount* MGClient::GetAccountData()
{
    if(socket == nullptr) return nullptr;

    return &accountData;
}
