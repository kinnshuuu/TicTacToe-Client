#ifndef WebSocketProtocol_h
#define WebSocketProtocol_h

#include "NetworkProtocol.h"
#include "cocos2d.h"
#include "network/Websocket.h"

using namespace cocos2d;
using namespace cocos2d::network;

#include <stdio.h>

class WebSocketProtocol : public NetworkProtocol, public WebSocket::Delegate {
public:
    WebSocketProtocol();
    ~WebSocketProtocol();
    
    bool initialize(const NetworkProtocol::Delegate&, std::string url);
    void close();
    void send(const std::string &msg);
    
private:
    WebSocket* socket;
    bool closed;
    
    void onClose(WebSocket*);
    void onError(WebSocket*, const WebSocket::ErrorCode&);
    void onOpen(WebSocket*);
    void onMessage(WebSocket*, const WebSocket::Data&);
};

#endif /* WebSocketProtocol_h */
