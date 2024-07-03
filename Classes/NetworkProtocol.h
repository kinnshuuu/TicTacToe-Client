#ifndef NetworkProtocol_h
#define NetworkProtocol_h

#include <stdio.h>
#include "cocos2d.h"

//using namespace std;
using namespace cocos2d;

class NetworkProtocol: public Node {
    public:
        class Delegate {
            public:
                virtual ~Delegate(){};
                virtual void onOpen(NetworkProtocol* protocol){}
                virtual void onMessage(NetworkProtocol* protocol, std::string msg) {};
                virtual void onClose(NetworkProtocol* protocol, bool isOpen) {};
                virtual void onError(NetworkProtocol* protocol, std::string) {};
        };
    virtual ~NetworkProtocol();
    virtual bool initialize(const Delegate& delegate, std::string url) = 0;
    virtual void close() = 0;
    virtual void send(const std::string& msg) = 0;
    
    Delegate *delegate;
    void onOpen();
    void onMessage(std::string msg);
    void onClose(bool);
    void onError(std::string);
    
};

#endif /* NetworkProtocol_h */
