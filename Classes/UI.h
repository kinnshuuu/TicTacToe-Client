#ifndef UI_h
#define UI_h

#include <stdio.h>
#include <string>

class UI {
public:
    UI( cocos2d::Layer *layer, int &gameState, cocos2d::String gameType);
    ~UI();
    
    void ShowGameOver(cocos2d::Layer *Layer, int gameType, std::string gameMode, int result);
    void GoToMainMenu(cocos2d::Ref *pSender);
    void GoToGameScene(cocos2d::Ref *pSender);
    void GoToMultiplayerGameScene(cocos2d::Ref *pSender);
    void PauseGame(cocos2d::Ref *pSender);
    int *gameState;
    cocos2d::Menu *pauseMenu;
    cocos2d::Sprite *pausebackground;
};

#endif /* UI_h */
