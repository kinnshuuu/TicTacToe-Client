#include "UIOnlineGame.h"
#include "MainMenuScene.h"
#include "constants.h"
#include "FlashHelper.h"
#include "OnlineGameScene.h"
#include <json/document.h>
#include <json/writer.h>
#include <json/stringbuffer.h>


UIOnlineGame::UIOnlineGame(cocos2d::Layer *layer, int &gameState, NetworkController *ws1){
    this->gameState = &gameState;
    
    Size screenSize = Director::getInstance( )->getVisibleSize( );
    Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
    
    MenuItemSprite *pauseItem = MenuItemSprite::create( Sprite::create( PAUSE_BUTTON ), Sprite::create( PAUSE_BUTTON_PRESSED ), Sprite::create( PAUSE_BUTTON_PRESSED ), CC_CALLBACK_1( UIOnlineGame::PauseGame, this ) );
    pauseItem->setPosition( Vec2( screenSize.width - ( pauseItem->getContentSize( ).width / 2 ) + origin.x, pauseItem->getContentSize( ).height / 2  + origin.y ) );
    
    Menu *menuButtons = Menu::create( pauseItem, NULL );
    menuButtons->setPosition( Vec2::ZERO );
    // menuButtons->setScale(.5,.5);
    layer->addChild( menuButtons );
    
    pausebackground = Sprite::create( GAME_BACKGROUND_FILEPATH );
    pausebackground->setPosition( FlashHelper::UI::GetScreenCenter( ) );
    pausebackground->setOpacity( 0 );
    // pausebackground->setScale(.5,.5);
    layer->addChild( pausebackground );
    
    
    MenuItemImage *overlayPauseWindowItem = MenuItemImage::create( PAUSE_WINDOW, PAUSE_WINDOW, PAUSE_WINDOW, NULL );
    // overlayPauseWindowItem->setScale(.5,.5);
    MenuItemSprite *resumeItem = MenuItemSprite::create( Sprite::create( RESUME_BUTTON ), Sprite::create( RESUME_BUTTON_PRESSED ), Sprite::create( RESUME_BUTTON ), CC_CALLBACK_1( UIOnlineGame::PauseGame, this ) );
        // resumeItem->setScale(.5,.5);
    resumeItem->setPosition( Vec2( -overlayPauseWindowItem->getContentSize( ).width / 4, resumeItem->getPositionY( ) ) );
    MenuItemSprite *mainMenuItem = MenuItemSprite::create( Sprite::create( HOME_BUTTON ), Sprite::create( HOME_BUTTON_PRESSED ), Sprite::create( HOME_BUTTON_PRESSED ), CC_CALLBACK_1( UIOnlineGame::GoToMainMenu, this ) );
    // mainMenuItem->setScale(.5,.5);
    mainMenuItem->setPosition( Vec2( overlayPauseWindowItem->getContentSize( ).width / 4, mainMenuItem->getPositionY( ) ) );
    
    pauseMenu = Menu::create( overlayPauseWindowItem, resumeItem, mainMenuItem, NULL );
    pauseMenu->setPosition( Vec2( FlashHelper::UI::GetScreenCenter( ).x, FlashHelper::UI::GetScreenCenter( ).y + screenSize.height ) );
    // pauseMenu->setScale(.5,.5);
    layer->addChild( pauseMenu );
    ws = ws1;
}

UIOnlineGame::~UIOnlineGame(){
    
}

void UIOnlineGame::PauseGame( cocos2d::Ref *pSender)
{
    // Create your JSON struct
    rapidjson::Document jsonStruct;
    jsonStruct.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonStruct.GetAllocator();
    rapidjson::Value key("command_type", allocator);
    rapidjson::Value value(COMMAND_TYPE_PAUSE);
    jsonStruct.AddMember(key, value, allocator);
    // Add more fields as needed
    
    Size screenSize = Director::getInstance( )->getVisibleSize( );
    
    if ( STATE_PLAYING == *gameState || STATE_ON_GOING == *gameState )
    {
        *gameState = STATE_PAUSED;
        pausebackground->runAction( FadeIn::create( PAUSE_BACKGROUND_FADE_IN_TIME ) );
        
        EaseBounceOut *menuActionEasing = EaseBounceOut::create( MoveTo::create( MENU_MOVE_BOUNCE_DURATION, FlashHelper::UI::GetScreenCenter( ) ) );
        pauseMenu->runAction( menuActionEasing );
        
        rapidjson::Value key("data", allocator);
        rapidjson::Value value("1", allocator);
        jsonStruct.AddMember(key, value, allocator);
        
        // Serialize the JSON struct into a string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        jsonStruct.Accept(writer);
        std::string jsonString = buffer.GetString();
        ws->send(jsonString);
    }
    else if ( STATE_PAUSED == *gameState )
    {
        *gameState = STATE_ON_GOING;
        pausebackground->runAction( FadeOut::create( PAUSE_BACKGROUND_FADE_IN_TIME ) );
        
        EaseBounceOut *menuActionEasing = EaseBounceOut::create( MoveTo::create( MENU_MOVE_BOUNCE_DURATION, Vec2( FlashHelper::UI::GetScreenCenter( ).x, FlashHelper::UI::GetScreenCenter( ).y + screenSize.height ) ) );
        pauseMenu->runAction( menuActionEasing );
        
        rapidjson::Value key("data", allocator);
        rapidjson::Value value("0", allocator);
        jsonStruct.AddMember(key, value, allocator);
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        jsonStruct.Accept(writer);
        std::string jsonString = buffer.GetString();
        ws->send(jsonString);
    }
}

void UIOnlineGame::PauseGameByOtherPlayer(cocos2d::Ref *pSender, int pause){
    Size screenSize = Director::getInstance( )->getVisibleSize( );
    if(pause == 1){
        *gameState = STATE_PAUSED;
        pausebackground->runAction( FadeIn::create( PAUSE_BACKGROUND_FADE_IN_TIME ) );
        
        EaseBounceOut *menuActionEasing = EaseBounceOut::create( MoveTo::create( MENU_MOVE_BOUNCE_DURATION, FlashHelper::UI::GetScreenCenter( ) ) );
        pauseMenu->runAction( menuActionEasing );
    }else{
        *gameState = STATE_ON_GOING;
        pausebackground->runAction( FadeOut::create( PAUSE_BACKGROUND_FADE_IN_TIME ) );
        
        EaseBounceOut *menuActionEasing = EaseBounceOut::create( MoveTo::create( MENU_MOVE_BOUNCE_DURATION, Vec2( FlashHelper::UI::GetScreenCenter( ).x, FlashHelper::UI::GetScreenCenter( ).y + screenSize.height ) ) );
        pauseMenu->runAction( menuActionEasing );
    }
}

void UIOnlineGame::ShowGameOver(cocos2d::Layer *layer, int gameType){
    Size screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = Sprite::create( MAIN_MENU_BACKGROUND_PATH );
    background->setPosition( Vec2( screenSize.width / 2 + origin.x, screenSize.height / 2 + origin.y ) );
    background->setOpacity(0);
    background->runAction( Sequence::create( DelayTime::create( PIECE_FADE_IN_TIME * 2.5 ), FadeIn::create( GAME_OVER_BACKGROUND_FADE_IN_TIME ), NULL ) );
    layer->addChild(background);
    MenuItemImage *overlayWindowItem;
    
        if(*gameState == STATE_WON){
        overlayWindowItem = MenuItemImage::create(VICTORY_WINDOW_FILEPATH, VICTORY_WINDOW_FILEPATH);
    }else if (*gameState == STATE_LOSE){
        overlayWindowItem = MenuItemImage::create(LOSE_WINDOW_FILEPATH, LOSE_WINDOW_FILEPATH);
    }else {
            overlayWindowItem = MenuItemImage::create(OVERLAY_WINDOW_FILEPATH, OVERLAY_WINDOW_FILEPATH);
        }
        
    MenuItemSprite *retryButton;    
    if(gameType == GAME_TYPE_OFFLINE){
        retryButton = MenuItemSprite::create(Sprite::create(RETRY_BUTTON), Sprite::create(RETRY_BUTTON_PRESSED), Sprite::create(RETRY_BUTTON_PRESSED),CC_CALLBACK_1(UIOnlineGame::GoToGameScene,this));
        retryButton->setPosition( Vec2( -.75*overlayWindowItem->getContentSize( ).width / 4, retryButton->getPositionY( ) ) );
    }
    else if(gameType == GAME_TYPE_ONLINE){
        retryButton = MenuItemSprite::create(Sprite::create(RETRY_BUTTON), Sprite::create(RETRY_BUTTON_PRESSED), Sprite::create(RETRY_BUTTON_PRESSED),CC_CALLBACK_1(UIOnlineGame::GoToMultiplayerGameScene,this));
        retryButton->setPosition( Vec2( -.75*overlayWindowItem->getContentSize( ).width / 4, retryButton->getPositionY( ) ) );
    }    

    auto homeButton = MenuItemSprite::create(Sprite::create(HOME_BUTTON), Sprite::create(HOME_BUTTON_PRESSED), Sprite::create(HOME_BUTTON_PRESSED),CC_CALLBACK_1(UIOnlineGame::GoToMainMenu,this));
    homeButton->setPosition( Vec2( .75*overlayWindowItem->getContentSize( ).width / 4, homeButton->getPositionY( ) ) );
    
    auto menu = Menu::create(overlayWindowItem, retryButton, homeButton, NULL);
    menu->setPosition( Vec2(FlashHelper::UI::GetScreenCenter( ).x, FlashHelper::UI::GetScreenCenter( ).y + screenSize.height) );
    // menu->setScale(.5,.5);
    layer->addChild(menu);
    
    EaseBounceOut *menuActionEasing = EaseBounceOut::create( MoveTo::create( MENU_MOVE_BOUNCE_DURATION, FlashHelper::UI::GetScreenCenter( ) ) );
    Sequence *menuShowSeq = Sequence::create( DelayTime::create( PIECE_FADE_IN_TIME * 2.5 ),menuActionEasing, NULL );
    menu->runAction( menuShowSeq );
}

void UIOnlineGame::GoToGameScene(cocos2d::Ref *pSender){
    Scene *scene = GameScene::createScene();
    TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(transition);
}

void UIOnlineGame::GoToMultiplayerGameScene(cocos2d::Ref *pSender){
    Scene *scene = OnlineGameScene::createScene();
    TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(transition);
}

void UIOnlineGame::GoToMainMenu(cocos2d::Ref *pSender){
    Scene *scene = MainMenuScene::createScene();
    TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(transition);
}
