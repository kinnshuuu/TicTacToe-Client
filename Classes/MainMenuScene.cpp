#include "MainMenuScene.h"
#include "constants.h"
#include "FlashHelper.h"
#include "GameScene.h"
#include "OnlineGameScene.h"
#include "GameSceneMultiplayer.h"


Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto layer = this;
    
    auto background = Sprite::create( MAIN_MENU_BACKGROUND_PATH );
    background->setPosition( Vec2( screenSize.width / 2 + origin.x, screenSize.height / 2 + origin.y ) );
    layer->addChild( background );
    
    auto title = Sprite::create( "res/tictactoe logo.png" );
    title->setScale(0.5,0.5);
    title->setPosition( Vec2( screenSize.width / 2 + origin.x, screenSize.height * 0.75 + origin.y ) );
    layer->addChild( title );
    
    auto playButton = Button::create(MAIN_MENU_PLAY_BUTTON, MAIN_MENU_PLAY_BUTTON_PRESSED);
    Vec2 playPostion = Vec2( screenSize.width / 2 + origin.x, screenSize.height * 0.45 + origin.y );
    playButton->setPosition(playPostion);
    // playButton->setScale(0.6,0.6);
    layer->addChild(playButton);
    
    playButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::touchEvent, this));
    playButton->setTag(TAG_MAIN_MENU_SINGLEPLAYER_BUTTON);
    
    //Multiplayer PlayButton
    auto multiplayerPlayButton = Button::create(MAIN_MENU_MULTI_PLAY_BUTTON, MAIN_MENU_MULTI_PLAY_BUTTON_PRESSED);
    Vec2 multiplayerPlayPostion = Vec2( screenSize.width / 2 + origin.x, screenSize.height * 0.3 + origin.y );
    multiplayerPlayButton->setPosition(multiplayerPlayPostion);
    layer->addChild(multiplayerPlayButton);
    
    multiplayerPlayButton->setTag(TAG_MAIN_MENU_MULTIPLAYER_BUTTON);
    multiplayerPlayButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::touchEvent, this));
    // multiplayerPlayButton->setScale(0.6,0.6);
    //PlayOnline PlayButton
    auto playOnlineButton = Button::create("res/Play Online.png");
    Vec2 playOnlinePostion = Vec2( screenSize.width / 2 + origin.x, screenSize.height * 0.15 + origin.y );
    playOnlineButton->setPosition(playOnlinePostion);
    // playOnlineButton->setScale(0.6,0.6);
    layer->addChild(playOnlineButton);
    
    playOnlineButton->setTag(2);
    playOnlineButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::touchEvent, this));
//
//    Settings Button
//    auto settingsButton = Button::create(MAIN_MENU_SETTINGS_BUTTON, MAIN_MENU_SETTINGS_BUTTON_PRESSED);
//    Vec2 settingsPlayPostion = Vec2( screenSize.width / 2 + origin.x, screenSize.height * 0.49 + origin.y );
//    settingsButton->setPosition(settingsPlayPostion);
//    layer->addChild(settingsButton);
//    
//    multiplayerPlayButton->setTag(TAG_MAIN_MENU_MULTIPLAYER_BUTTON);
//    multiplayerPlayButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::touchEvent, this));
    
//    FlashHelper::UI ui;
//    ui.AddAudioToggle(MAIN_MENU_SOUND_ON_BUTTON, MAIN_MENU_SOUND_ON_BUTTON_PRESSED, MAIN_MENU_SOUND_OFF_BUTTON, MAIN_MENU_SOUND_OFF_BUTTON_PRESSED, this, FlashHelper::UIButtonPosition::eBottomLeft);
    
    
    return true;
}


void MainMenuScene::touchEvent(Ref *sender, Widget::TouchEventType type)
{
    Node* node = (Node *)sender;
    switch(type){
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::ENDED:
            if(TAG_MAIN_MENU_SINGLEPLAYER_BUTTON == node->getTag()){
                Scene *scene = GameScene::createScene();
                TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
                Director::getInstance()->replaceScene(transition);
            }else if (TAG_MAIN_MENU_MULTIPLAYER_BUTTON == node->getTag()){
                Scene *scene = GameSceneMultiplayer::createScene();
                TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
                Director::getInstance()->replaceScene(transition);
            }
            else if (TAG_MAIN_MENU_ONLINE_BUTTON == node->getTag()){
                Scene *scene = OnlineGameScene::createScene();
                TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
                Director::getInstance()->replaceScene(transition);
            }
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        default:
            break;
    }
}
