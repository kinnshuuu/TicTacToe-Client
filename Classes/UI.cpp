#include "UI.h"
#include "MainMenuScene.h"
#include "constants.h"
#include "GameScene.h"
#include "FlashHelper.h"
//#include "MultiplayerGameScene.h"
#include <string>
#include "GameSceneMultiplayer.h"


UI::UI(cocos2d::Layer *layer, int &gameState, cocos2d::String gameType) {
    this->gameState = &gameState;
    
    Size screenSize = Director::getInstance( )->getVisibleSize( );
    Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
    
    MenuItemSprite *pauseItem = MenuItemSprite::create( Sprite::create( PAUSE_BUTTON ), Sprite::create( PAUSE_BUTTON_PRESSED ),  CC_CALLBACK_1( UI::PauseGame, this ) );
    pauseItem->setPosition( Vec2( screenSize.width - ( pauseItem->getContentSize( ).width / 2 ) + origin.x, pauseItem->getContentSize( ).height / 2  + origin.y ) );
    
    Menu *menuButtons = Menu::create( pauseItem, NULL );
    menuButtons->setPosition( Vec2::ZERO );
    layer->addChild( menuButtons );
    
    pausebackground = Sprite::create( GAME_BACKGROUND_FILEPATH );
    pausebackground->setPosition( FlashHelper::UI::GetScreenCenter( ) );
    pausebackground->setOpacity( 0 );
    layer->addChild( pausebackground );
    
    
    MenuItemImage *overlayPauseWindowItem = MenuItemImage::create( PAUSE_WINDOW, PAUSE_WINDOW, PAUSE_WINDOW, NULL );
    MenuItemSprite *resumeItem = MenuItemSprite::create( Sprite::create( RESUME_BUTTON ), Sprite::create( RESUME_BUTTON_PRESSED ), Sprite::create( RESUME_BUTTON ), CC_CALLBACK_1( UI::PauseGame, this ) );
    resumeItem->setPosition( Vec2( -1.2* overlayPauseWindowItem->getContentSize( ).width / 4, resumeItem->getPositionY( ) ) );
    MenuItemSprite *mainMenuItem = MenuItemSprite::create( Sprite::create( HOME_BUTTON ), Sprite::create( HOME_BUTTON_PRESSED ), Sprite::create( HOME_BUTTON_PRESSED ), CC_CALLBACK_1( UI::GoToMainMenu, this ) );
    mainMenuItem->setPosition( Vec2( 1.2 *overlayPauseWindowItem->getContentSize( ).width / 4, mainMenuItem->getPositionY( ) ) );
    
//    Size size = mainMenuItem->getContentSize();
    
    MenuItemSprite *restartButton;
    if (gameType.compare("SinglePlayer") == 0) {
        restartButton = MenuItemSprite::create(Sprite::create(RETRY_BUTTON), Sprite::create(RETRY_BUTTON_PRESSED), Sprite::create(RETRY_BUTTON_PRESSED), CC_CALLBACK_1(UI::GoToGameScene, this));
    } else if (gameType.compare("Multiplayer") == 0) {
        restartButton = MenuItemSprite::create(Sprite::create(RETRY_BUTTON), Sprite::create(RETRY_BUTTON_PRESSED), Sprite::create(RETRY_BUTTON_PRESSED), CC_CALLBACK_1(UI::GoToMultiplayerGameScene, this));
    }
    restartButton->setPosition( Vec2( 0, restartButton->getPositionY( ) ) );
    
//    restartButton -> setScale(0.3, 0.3);
    pauseMenu = Menu::create( overlayPauseWindowItem, resumeItem, mainMenuItem,restartButton,  NULL );
    pauseMenu->setPosition( Vec2( FlashHelper::UI::GetScreenCenter( ).x, FlashHelper::UI::GetScreenCenter( ).y + screenSize.height ) );
    layer->addChild( pauseMenu );
}

UI::~UI(){
}

void UI::PauseGame( cocos2d::Ref *pSender )
{
    Size screenSize = Director::getInstance( )->getVisibleSize( );
    
    if ( STATE_PLAYING == *gameState )
    {
        *gameState = STATE_PAUSED;
        pausebackground->runAction( FadeIn::create( PAUSE_BACKGROUND_FADE_IN_TIME ) );
        
        EaseBounceOut *menuActionEasing = EaseBounceOut::create( MoveTo::create( MENU_MOVE_BOUNCE_DURATION, FlashHelper::UI::GetScreenCenter( ) ) );
        pauseMenu->runAction( menuActionEasing );
    }
    else if ( STATE_PAUSED == *gameState )
    {
        *gameState = STATE_PLAYING;
        pausebackground->runAction( FadeOut::create( PAUSE_BACKGROUND_FADE_IN_TIME ) );
        
        EaseBounceOut *menuActionEasing = EaseBounceOut::create( MoveTo::create( MENU_MOVE_BOUNCE_DURATION, Vec2( FlashHelper::UI::GetScreenCenter( ).x, FlashHelper::UI::GetScreenCenter( ).y + screenSize.height ) ) );
        pauseMenu->runAction( menuActionEasing );
    }
}

void UI::ShowGameOver(cocos2d::Layer *layer, int gameType, std::string gameMode, int result){
    Size screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = Sprite::create( MAIN_MENU_BACKGROUND_PATH );
    background->setPosition( Vec2( screenSize.width / 2 + origin.x, screenSize.height / 2 + origin.y ) );
    background->setOpacity(0);
    background->runAction( Sequence::create( DelayTime::create( 1.0f * .5 ), FadeIn::create( GAME_OVER_BACKGROUND_FADE_IN_TIME ), NULL ) );
    // background->setScale(.5,.5);
    layer->addChild(background);
    MenuItemImage *overlayWindowItem;
    
    if(gameMode == "SinglePlayer"){
        if(*gameState == STATE_WON){
            overlayWindowItem = MenuItemImage::create(VICTORY_WINDOW_FILEPATH, VICTORY_WINDOW_FILEPATH);
        }else if (*gameState == STATE_LOSE){
            overlayWindowItem = MenuItemImage::create(LOSE_WINDOW_FILEPATH, LOSE_WINDOW_FILEPATH);
        }else {
            overlayWindowItem = MenuItemImage::create(OVERLAY_WINDOW_FILEPATH, OVERLAY_WINDOW_FILEPATH);
            auto label = Label::createWithTTF("It's a Draw", "fonts/Marker Felt.ttf", 40);
            label->setTextColor(Color4B(128, 0, 128, 255));
            label->setPosition(FlashHelper::UI::GetScreenCenter().x * 0.6, FlashHelper::UI::GetScreenCenter().y );
            // label->setScale(.5,.5);
            overlayWindowItem->addChild(label);
        }
    }
    else{
        overlayWindowItem = MenuItemImage::create(OVERLAY_WINDOW_FILEPATH, OVERLAY_WINDOW_FILEPATH);
        if(result == STATE_X_WIN) {
            auto label = Label::createWithTTF("X is the Winner", "fonts/Marker Felt.ttf", 40);
            label->setTextColor(Color4B(128, 0, 128, 255));
            label->setPosition(FlashHelper::UI::GetScreenCenter().x * 0.6, FlashHelper::UI::GetScreenCenter().y );
            // label->setScale(.5,.5);
            overlayWindowItem->addChild(label);
        }
        else if(result == STATE_O_WIN)
        {
            auto label = Label::createWithTTF("O is the Winner", "fonts/Marker Felt.ttf", 40);
            label->setTextColor(Color4B(128, 0, 128, 255));
            label->setPosition(FlashHelper::UI::GetScreenCenter().x * 0.6, FlashHelper::UI::GetScreenCenter().y );
            // label->setScale(.5,.5);
            overlayWindowItem->addChild(label);
        }
        else{
            auto label = Label::createWithTTF("It's a Draw", "fonts/Marker Felt.ttf", 40);
            label->setTextColor(Color4B(128, 0, 128, 255));
            label->setPosition(FlashHelper::UI::GetScreenCenter().x * 0.6, FlashHelper::UI::GetScreenCenter().y );
            // label->setScale(.5,.5);
            overlayWindowItem->addChild(label);
        }
    }
        
    MenuItemSprite *retryButton;
    if(gameType == GAME_TYPE_OFFLINE){
        retryButton = MenuItemSprite::create(Sprite::create(RETRY_BUTTON), Sprite::create(RETRY_BUTTON_PRESSED), Sprite::create(RETRY_BUTTON_PRESSED),CC_CALLBACK_1(UI::GoToGameScene,this));
        retryButton->setPosition( Vec2( -.75*overlayWindowItem->getContentSize( ).width / 4, retryButton->getPositionY( ) ) );
    }
    else if(gameType == GAME_TYPE_ONLINE){
        retryButton = MenuItemSprite::create(Sprite::create(RETRY_BUTTON), Sprite::create(RETRY_BUTTON_PRESSED), Sprite::create(RETRY_BUTTON_PRESSED),CC_CALLBACK_1(UI::GoToMultiplayerGameScene,this));
        retryButton->setPosition( Vec2( -.75*overlayWindowItem->getContentSize( ).width / 4, retryButton->getPositionY( ) ) );
    }
    
    auto homeButton = MenuItemSprite::create(Sprite::create(HOME_BUTTON), Sprite::create(HOME_BUTTON_PRESSED), Sprite::create(HOME_BUTTON_PRESSED),CC_CALLBACK_1(UI::GoToMainMenu,this));
    homeButton->setPosition( Vec2( .75*overlayWindowItem->getContentSize( ).width / 4, homeButton->getPositionY( ) ) );
    
    auto menu = Menu::create(overlayWindowItem, retryButton, homeButton, NULL);
    menu->setPosition( Vec2(FlashHelper::UI::GetScreenCenter( ).x, FlashHelper::UI::GetScreenCenter( ).y + screenSize.height) );
    // menu->setScale(.5,.5);
    layer->addChild(menu);
    
    EaseBounceOut *menuActionEasing = EaseBounceOut::create( MoveTo::create( MENU_MOVE_BOUNCE_DURATION, FlashHelper::UI::GetScreenCenter( ) ) );
    Sequence *menuShowSeq = Sequence::create( DelayTime::create( 1.0f * 0.5 ),menuActionEasing, NULL );
    menu->runAction( menuShowSeq );
}

void UI::GoToGameScene(cocos2d::Ref *pSender){
    Scene *scene = GameScene::createScene();
    TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(transition);
}

void UI::GoToMultiplayerGameScene(cocos2d::Ref *pSender){
    Scene *scene = GameSceneMultiplayer::createScene();
    TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(transition);
}

void UI::GoToMainMenu(cocos2d::Ref *pSender){
    Scene *scene = MainMenuScene::createScene();
    TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(transition);
}

