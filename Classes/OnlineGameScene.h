#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "NetworkController.h"
#include "UIOnlineGame.h"
#include <vector>
#include <string>

struct GameInfo
{
    int state;
    int data;
    int turn;
    int commandType;
};

class OnlineGameScene : public GameScene, public NetworkController::Delegate
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    CREATE_FUNC(OnlineGameScene);

private:
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

    void CheckAndPlacePiece(cocos2d::Touch *touch);
    void CheckWin(int x, int y);
    void CheckWin2(int state);

    cocos2d::Sprite *waitingSprite;
    cocos2d::Label *yourTurnLabel;
    cocos2d::Label *opponentTurnLabel;

    NetworkController *ws;
    UIOnlineGame *ui;
    GameInfo *g;
    int myTurn;
    std::string mySymbol;

    void onMessage(std::string msg);
    void parseJson(std::string msg);
    void CommandMove();
    void CommandPause();
    std::vector<int> getWinningCoordinates();
};
