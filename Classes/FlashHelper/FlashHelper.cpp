#include "FlashHelper.h"

using namespace FlashHelper;

std::string UI::Audio::offButtonString = "";
std::string UI::Audio::offButtonPressedString = "";
std::string UI::Audio::onButtonString = "";
std::string UI::Audio::onButtonPressedString = "";
std::string UI::SoundEffects::offButtonString = "";
std::string UI::SoundEffects::offButtonPressedString = "";
std::string UI::SoundEffects::onButtonString = "";
std::string UI::SoundEffects::onButtonPressedString = "";
std::string UI::Music::offButtonString = "";
std::string UI::Music::offButtonPressedString = "";
std::string UI::Music::onButtonString = "";
std::string UI::Music::onButtonPressedString = "";


UI::UI( )
{ }

void UI::AddAudioToggle( const std::string &onButton, const std::string &onButtonPressed, const std::string &offButton, const std::string &offButtonPressed, cocos2d::Layer *layer, int position )
{
    audioToggleButton = ui::Button::create( onButton, onButtonPressed );

    Size visibleSize = Director::getInstance( )->getVisibleSize( );
    Vec2 origin = Director::getInstance( )->getVisibleOrigin( );

    switch ( position )
    {
    case FlashHelper::UIButtonPosition::eBottomLeft:
        audioToggleButton->cocos2d::Node::setPosition( audioToggleButton->getContentSize( ).width / 2 + origin.x, audioToggleButton->getContentSize( ).height / 2 + origin.y );

        break;

    case FlashHelper::UIButtonPosition::eBottomRight:
        audioToggleButton->cocos2d::Node::setPosition( visibleSize.width - audioToggleButton->getContentSize( ).width / 2 + origin.x, audioToggleButton->getContentSize( ).height / 2 + origin.y );

        break;

    case FlashHelper::UIButtonPosition::eTopLeft:
        audioToggleButton->cocos2d::Node::setPosition( audioToggleButton->getContentSize( ).width / 2 + origin.x, visibleSize.height - audioToggleButton->getContentSize( ).height / 2 + origin.y );

        break;

    case FlashHelper::UIButtonPosition::eTopRight:
        audioToggleButton->cocos2d::Node::setPosition( visibleSize.width - audioToggleButton->getContentSize( ).width / 2 + origin.x, visibleSize.height - audioToggleButton->getContentSize( ).height / 2 + origin.y );

        break;
    }

    audioToggleButton->addTouchEventListener( CC_CALLBACK_2( UI::AudioTouchEvent, this ) );

    layer->addChild( audioToggleButton, 10000 );

    UI::Audio::offButtonString = offButton;
    UI::Audio::offButtonPressedString = offButtonPressed;
    UI::Audio::onButtonString = onButton;
    UI::Audio::onButtonPressedString = onButtonPressed;
}

void UI::SetAudioButtonPosition( float xPos, float yPos )
{
    audioToggleButton->cocos2d::Node::setPosition( xPos, yPos );
}

void UI::AudioTouchEvent( Ref *sender, Widget::TouchEventType type )
{
    ui::Button *node = ( ui::Button * )sender;

    std::string tempString;

    switch ( type )
    {
    case Widget::TouchEventType::BEGAN:
        // code to handle when the button is first clicked

        break;

    case Widget::TouchEventType::MOVED:
        // code to handle when the user is moving their finger/cursor whilst clicking the button
        break;

    case Widget::TouchEventType::ENDED:
        tempString = UI::Audio::offButtonString;

        UI::Audio::offButtonString = UI::Audio::onButtonString;
        UI::Audio::onButtonString = tempString;

        tempString = UI::Audio::offButtonPressedString;

        UI::Audio::offButtonPressedString = UI::Audio::onButtonPressedString;
        UI::Audio::onButtonPressedString = tempString;

        node->loadTextures( UI::Audio::onButtonString, UI::Audio::onButtonPressedString );

        float volume;

        if ( CocosDenshion::SimpleAudioEngine::getInstance( )->getEffectsVolume( ) > 0.0f )
        {
            volume = 0.0f;
        }
        else
        {
            volume = 1.0f;
        }

        CocosDenshion::SimpleAudioEngine::getInstance( )->setEffectsVolume( volume );

        if ( CocosDenshion::SimpleAudioEngine::getInstance( )->getBackgroundMusicVolume( ) > 0.0f )
        {
            volume = 0.0f;
        }
        else
        {
            volume = 1.0f;
        }

        CocosDenshion::SimpleAudioEngine::getInstance( )->setBackgroundMusicVolume( volume );

        break;

    case Widget::TouchEventType::CANCELED:
        // code to handle when the button click has been cancelled,  this is usually handled the same way as ENDED in most applications (e.g. another application takes control of the device)


        break;

    default:
        break;
    }
}

void UI::AddSoundEffectsToggle( const std::string &onButton, const std::string &onButtonPressed, const std::string &offButton, const std::string &offButtonPressed, cocos2d::Layer *layer, int position )
{
    soundEffectsToggleButton = ui::Button::create( onButton, onButtonPressed );

    Size visibleSize = Director::getInstance( )->getVisibleSize( );
    Vec2 origin = Director::getInstance( )->getVisibleOrigin( );

    switch ( position )
    {
    case FlashHelper::UIButtonPosition::eBottomLeft:
        soundEffectsToggleButton->cocos2d::Node::setPosition( soundEffectsToggleButton->getContentSize( ).width / 2 + origin.x, soundEffectsToggleButton->getContentSize( ).height / 2 + origin.y );

        break;

    case FlashHelper::UIButtonPosition::eBottomRight:
        soundEffectsToggleButton->cocos2d::Node::setPosition( visibleSize.width - soundEffectsToggleButton->getContentSize( ).width / 2 + origin.x, soundEffectsToggleButton->getContentSize( ).height / 2 + origin.y );

        break;

    case FlashHelper::UIButtonPosition::eTopLeft:
        soundEffectsToggleButton->cocos2d::Node::setPosition( soundEffectsToggleButton->getContentSize( ).width / 2 + origin.x, visibleSize.height - soundEffectsToggleButton->getContentSize( ).height / 2 + origin.y );

        break;

    case FlashHelper::UIButtonPosition::eTopRight:
        soundEffectsToggleButton->cocos2d::Node::setPosition( visibleSize.width - soundEffectsToggleButton->getContentSize( ).width / 2 + origin.x, visibleSize.height - soundEffectsToggleButton->getContentSize( ).height / 2 + origin.y );

        break;
    }

    soundEffectsToggleButton->addTouchEventListener( CC_CALLBACK_2( UI::SoundEffectsTouchEvent, this ) );

    layer->addChild( soundEffectsToggleButton, 10000 );

    UI::SoundEffects::offButtonString = offButton;
    UI::SoundEffects::offButtonPressedString = offButtonPressed;
    UI::SoundEffects::onButtonString = onButton;
    UI::SoundEffects::onButtonPressedString = onButtonPressed;
}

void UI::SetSoundEffectsButtonPosition( float xPos, float yPos )
{
    soundEffectsToggleButton->cocos2d::Node::setPosition( xPos, yPos );
}

void UI::SoundEffectsTouchEvent( Ref *sender, Widget::TouchEventType type )
{
    ui::Button *node = ( ui::Button * )sender;

    std::string tempString;

    switch ( type )
    {
    case Widget::TouchEventType::BEGAN:
        // code to handle when the button is first clicked

        break;

    case Widget::TouchEventType::MOVED:
        // code to handle when the user is moving their finger/cursor whilst clicking the button
        break;

    case Widget::TouchEventType::ENDED:
        tempString = UI::SoundEffects::offButtonString;

        UI::SoundEffects::offButtonString = UI::SoundEffects::onButtonString;
        UI::SoundEffects::onButtonString = tempString;

        tempString = UI::SoundEffects::offButtonPressedString;

        UI::SoundEffects::offButtonPressedString = UI::SoundEffects::onButtonPressedString;
        UI::SoundEffects::onButtonPressedString = tempString;

        node->loadTextures( UI::SoundEffects::onButtonString, UI::SoundEffects::onButtonPressedString );

        float volume;

        if ( CocosDenshion::SimpleAudioEngine::getInstance( )->getEffectsVolume( ) > 0.0f )
        {
            volume = 0.0f;
        }
        else
        {
            volume = 1.0f;
        }

        CocosDenshion::SimpleAudioEngine::getInstance( )->setEffectsVolume( volume );

        break;

    case Widget::TouchEventType::CANCELED:
        // code to handle when the button click has been cancelled,  this is usually handled the same way as ENDED in most applications (e.g. another application takes control of the device)


        break;

    default:
        break;
    }
}

void UI::AddMusicToggle( const std::string &onButton, const std::string &onButtonPressed, const std::string &offButton, const std::string &offButtonPressed, cocos2d::Layer *layer, int position )
{
    musicToggleButton = ui::Button::create( onButton, onButtonPressed );

    Size visibleSize = Director::getInstance( )->getVisibleSize( );
    Vec2 origin = Director::getInstance( )->getVisibleOrigin( );

    switch ( position )
    {
    case FlashHelper::UIButtonPosition::eBottomLeft:
        musicToggleButton->cocos2d::Node::setPosition( musicToggleButton->getContentSize( ).width / 2 + origin.x, musicToggleButton->getContentSize( ).height / 2 + origin.y );

        break;

    case FlashHelper::UIButtonPosition::eBottomRight:
        musicToggleButton->cocos2d::Node::setPosition( visibleSize.width - musicToggleButton->getContentSize( ).width / 2 + origin.x, musicToggleButton->getContentSize( ).height / 2 + origin.y );

        break;

    case FlashHelper::UIButtonPosition::eTopLeft:
        musicToggleButton->cocos2d::Node::setPosition( musicToggleButton->getContentSize( ).width / 2 + origin.x, visibleSize.height - musicToggleButton->getContentSize( ).height / 2 + origin.y );

        break;

    case FlashHelper::UIButtonPosition::eTopRight:
        musicToggleButton->cocos2d::Node::setPosition( visibleSize.width - musicToggleButton->getContentSize( ).width / 2 + origin.x, visibleSize.height - musicToggleButton->getContentSize( ).height / 2 + origin.y );

        break;
    }

    musicToggleButton->addTouchEventListener( CC_CALLBACK_2( UI::MusicTouchEvent, this ) );

    layer->addChild( musicToggleButton, 10000 );

    UI::Music::offButtonString = offButton;
    UI::Music::offButtonPressedString = offButtonPressed;
    UI::Music::onButtonString = onButton;
    UI::Music::onButtonPressedString = onButtonPressed;
}

void UI::SetMusicButtonPosition( float xPos, float yPos )
{
    musicToggleButton->cocos2d::Node::setPosition( xPos, yPos );
}

void UI::MusicTouchEvent( Ref *sender, Widget::TouchEventType type )
{
    ui::Button *node = ( ui::Button * )sender;

    std::string tempString;

    switch ( type )
    {
    case Widget::TouchEventType::BEGAN:
        break;

    case Widget::TouchEventType::MOVED:
        break;

    case Widget::TouchEventType::ENDED:
        tempString = UI::Music::offButtonString;

        UI::Music::offButtonString = UI::Music::onButtonString;
        UI::Music::onButtonString = tempString;

        tempString = UI::Music::offButtonPressedString;

        UI::Music::offButtonPressedString = UI::Music::onButtonPressedString;
        UI::Music::onButtonPressedString = tempString;

        node->loadTextures( UI::Music::onButtonString, UI::Music::onButtonPressedString );

        float volume;

        if ( CocosDenshion::SimpleAudioEngine::getInstance( )->getBackgroundMusicVolume( ) > 0.0f )
        {
            volume = 0.0f;
        }
        else
        {
            volume = 1.0f;
        }

        CocosDenshion::SimpleAudioEngine::getInstance( )->setBackgroundMusicVolume( volume );

        break;

    case Widget::TouchEventType::CANCELED:
        // code to handle when the button click has been cancelled,  this is usually handled the same way as ENDED in most applications (e.g. another application takes control of the device)


        break;

    default:
        break;
    }
}

void UI::AddCentredBackground( const std::string &background, cocos2d::Layer *layer )
{
    Sprite *sprite = Sprite::create( background );
    sprite->setPosition( Vec2( Director::getInstance( )->getVisibleSize( ).width / 2 + Director::getInstance( )->getVisibleOrigin( ).x, Director::getInstance( )->getVisibleSize( ).height / 2 + Director::getInstance( )->getVisibleOrigin( ).y ) );
    layer->addChild( sprite );
}

Vec2 UI::GetScreenCenter( )
{
    return Vec2( Director::getInstance( )->getVisibleSize( ).width / 2 + Director::getInstance( )->getVisibleOrigin( ).x, Director::getInstance( )->getVisibleSize( ).height / 2 + Director::getInstance( )->getVisibleOrigin( ).y );
}

Vec2 UI::GetScreenCorner( int position, Node *itemToPosition )
{
    Size visibleSize = Director::getInstance( )->getVisibleSize( );
    Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
    
    switch ( position )
    {
        case FlashHelper::UIButtonPosition::eBottomLeft:
            return Vec2( itemToPosition->getContentSize( ).width / 2 + origin.x, itemToPosition->getContentSize( ).height / 2 + origin.y );
            
            break;
            
        case FlashHelper::UIButtonPosition::eBottomRight:
            return Vec2( visibleSize.width - itemToPosition->getContentSize( ).width / 2 + origin.x, itemToPosition->getContentSize( ).height / 2 + origin.y );
            
            break;
            
        case FlashHelper::UIButtonPosition::eTopLeft:
            return Vec2( itemToPosition->getContentSize( ).width / 2 + origin.x, visibleSize.height - itemToPosition->getContentSize( ).height / 2 + origin.y );
            
            break;
            
        case FlashHelper::UIButtonPosition::eTopRight:
        default:
            return Vec2( visibleSize.width - itemToPosition->getContentSize( ).width / 2 + origin.x, visibleSize.height - itemToPosition->getContentSize( ).height / 2 + origin.y );
            
            break;
    }
}
