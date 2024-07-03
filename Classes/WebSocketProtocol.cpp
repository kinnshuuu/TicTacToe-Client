#include "WebSocketProtocol.h"
#include <json/rapidjson.h>
#include <json/document.h>
#include <json/error/error.h>
#include <iostream>

WebSocketProtocol::WebSocketProtocol(){
    socket = new WebSocket();
    closed = false;
}

WebSocketProtocol::~WebSocketProtocol(){
    this->close();
}

bool WebSocketProtocol::initialize(const NetworkProtocol::Delegate &del, std::string url){
    delegate = const_cast<NetworkProtocol::Delegate*>(&del);
    return socket->init(*this, url);
}

void WebSocketProtocol::close(){
    if(socket && !closed){
        closed = true;
        socket->close();
    }
}

void WebSocketProtocol::send(const std::string &message){
    socket->send(message);
}

void WebSocketProtocol::onClose(WebSocket* ws){
    
}
void WebSocketProtocol::onError(WebSocket* ws, const WebSocket::ErrorCode&){
    
}
void WebSocketProtocol::onOpen(WebSocket* ws){
    
}
void WebSocketProtocol::onMessage(WebSocket* ws, const WebSocket::Data& data){
    if(!closed){
        std::string jsonStr(data.bytes, data.bytes + data.len);
        this->NetworkProtocol::onMessage(jsonStr);
    }
}
