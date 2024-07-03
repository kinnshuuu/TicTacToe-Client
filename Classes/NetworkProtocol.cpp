#include "NetworkProtocol.h"


NetworkProtocol::~NetworkProtocol(){}

void NetworkProtocol::onOpen(){
    delegate->onOpen(this);
}

void NetworkProtocol::onClose(bool isOpen) {
    delegate->onClose(this, isOpen);
}

void NetworkProtocol::onMessage(std::string msg){
    delegate->onMessage(this, msg);
}

void NetworkProtocol::onError(std::string error){
    delegate->onError(this, error);
}

