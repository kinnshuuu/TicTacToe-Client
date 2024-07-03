#ifndef NetworkController_h
#define NetworkController_h

#include "cocos2d.h"
#include "network/Websocket.h"
#include "NetworkProtocol.h"
#include "WebSocketProtocol.h"
#include <stdio.h>

using namespace cocos2d;
using namespace cocos2d::network;

#include <stdio.h>

class NetworkController: public NetworkProtocol::Delegate {
private:
    NetworkProtocol* protocol;
    std::string url;
    std::string ip;
    std::string packet;
public:
    NetworkController();
    ~NetworkController();
    class Delegate {
        public:
            virtual ~Delegate(){};
            virtual void onMessage(std::string msg) {};
    };
    
    Delegate *delegate;
    bool connect();
    void initialize(const NetworkController::Delegate&);
    
    void onClose(NetworkProtocol*, bool isOpen);
    void onError(NetworkProtocol*, std::string);
    void onOpen(NetworkProtocol*);
    void onMessage(NetworkProtocol*, std::string msg);
    void send(std::string data);
};

#endif /* NetworkController_h */
