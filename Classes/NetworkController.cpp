#include "NetworkController.h"
#include <iostream>

NetworkController::NetworkController(){
    this->protocol = nullptr;
    this->url = "localhost:8080/ws";
    this->ip = "";
    this->packet = "";
}

void NetworkController::initialize(const NetworkController::Delegate& del) {
    delegate = const_cast<NetworkController::Delegate*>(&del);
}

NetworkController::~NetworkController(){
    if(this->protocol){
        this->protocol->close();
        this->protocol = nullptr;
    }
}

bool NetworkController::connect(){
    if(this->protocol){
        this->protocol->close();
    }
    this->protocol = new WebSocketProtocol();
    this->protocol->initialize(*this, url);
    return true;
}

void NetworkController::onClose(NetworkProtocol* protocol, bool isOpen){
    std::cout<<"Connection Closed\n";
    CCLOG("Connection Closed");
}

void NetworkController::onError(NetworkProtocol* protocol, std::string msg){
}

void NetworkController::onOpen(NetworkProtocol* protocol){
    std::cout<<"Connection Established\n";
    CCLOG("Connection Established");
}

void NetworkController::onMessage(NetworkProtocol* protocol, std::string msg){
    delegate->onMessage(msg);
}

void NetworkController::send(std::string data) {
    if(this->protocol && data != ""){
        this->protocol->send(data);
    }
}
