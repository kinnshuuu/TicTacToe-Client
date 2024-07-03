#ifndef UIOnlineGame_h
#define UIOnlineGame_h

#include <stdio.h>
#include "UI.h"
#include "NetworkController.h"

class UIOnlineGame{
public:
    UIOnlineGame( cocos2d::Layer *layer, int &gameState, NetworkController *ws );
    ~UIOnlineGame();
    
    void ShowGameOver(cocos2d::Layer *Layer, int gameType);
    void GoToMainMenu(cocos2d::Ref *pSender);
    void GoToGameScene(cocos2d::Ref *pSender);
    void GoToMultiplayerGameScene(cocos2d::Ref *pSender);
    int *gameState;
    cocos2d::Menu *pauseMenu;
    cocos2d::Menu *pauseMenuOtherPlayer;
    cocos2d::Sprite *pausebackground;
    NetworkController *ws;
    void PauseGame(cocos2d::Ref *pSender);
    void PauseGameByOtherPlayer(cocos2d::Ref *pSender, int pause);
};

#endif /* UIOnlineGame_h */
