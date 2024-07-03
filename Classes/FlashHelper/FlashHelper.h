#ifndef FlashHelper_h
#define FlashHelper_h

#include <stdio.h>
#include <cocos2d.h>
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

USING_NS_CC_EXT;
using namespace ui;


namespace FlashHelper
{
enum UIButtonPosition { eBottomLeft, eBottomRight, eTopLeft, eTopRight };
class UI
{
public:
    /**
     * Constructor
     */
    UI( );

    /**
     * Adds a audio toggle button (sounds effects and music)
     * @param onButton (required) audio on button filepath
     * @param onButtonPressed (required) audio on pressed button filepath
     * @param offButton (required) audio off button filepath
     * @param offButtonPressed (required) audio off pressed button filepath
     * @param layer (required) the layer to which the button will be added a child
     * @param position (required) where would you like to position the button (SonarCocosHelper::UIButtonPosition::eBottomLeft, SonarCocosHelper::UIButtonPosition::eBottomRight, SonarCocosHelper::UIButtonPosition::eTopLeft, SonarCocosHelper::UIButtonPosition::eTopRight)
     */
    void AddAudioToggle( const std::string &onButton, const std::string &onButtonPressed, const std::string &offButton, const std::string &offButtonPressed, cocos2d::Layer *layer, int position );
    /**
     * Set the audio toggle button position
     * @param xPos (required) x-axis position
     * @param yPos (required) y-axis position
     */
    void SetAudioButtonPosition( float xPos, float yPos );

    /**
     * Adds a sound effects toggle button
     * @param onButton (required) sound effects on button filepath
     * @param onButtonPressed (required) sound effects on pressed button filepath
     * @param offButton (required) sound effects off button filepath
     * @param offButtonPressed (required) sound effects off pressed button filepath
     * @param layer (required) the layer to which the button will be added a child
     * @param position (required) where would you like to position the button (SonarCocosHelper::UIButtonPosition::eBottomLeft, SonarCocosHelper::UIButtonPosition::eBottomRight, SonarCocosHelper::UIButtonPosition::eTopLeft, SonarCocosHelper::UIButtonPosition::eTopRight)
     */
    void AddSoundEffectsToggle( const std::string &onButton, const std::string &onButtonPressed, const std::string &offButton, const std::string &offButtonPressed, cocos2d::Layer *layer, int position );
    /**
     * Set the sound effects toggle button position
     * @param xPos (required) x-axis position
     * @param yPos (required) y-axis position
     */
    void SetSoundEffectsButtonPosition( float xPos, float yPos );

    /**
     * Adds a music toggle button
     * @param onButton (required) music on button filepath
     * @param onButtonPressed (required) music on pressed button filepath
     * @param offButton (required) music off button filepath
     * @param offButtonPressed (required) music off pressed button filepath
     * @param layer (required) the layer to which the button will be added a child
     * @param position (required) where would you like to position the button (SonarCocosHelper::UIButtonPosition::eBottomLeft, SonarCocosHelper::UIButtonPosition::eBottomRight, SonarCocosHelper::UIButtonPosition::eTopLeft, SonarCocosHelper::UIButtonPosition::eTopRight)
     */
    void AddMusicToggle( const std::string &onButton, const std::string &onButtonPressed, const std::string &offButton, const std::string &offButtonPressed, cocos2d::Layer *layer, int position );
    /**
     * Set the music toggle button position
     * @param xPos (required) x-axis position
     * @param yPos (required) y-axis position
     */
    void SetMusicButtonPosition( float xPos, float yPos );
    
    /**
     * Create and add a centered background
     * @param backgroundImage (required) background image filepath
     */
    static void AddCentredBackground( const std::string &background, cocos2d::Layer *layer );
    /**
     * Get the screen centre
     * @return screem center Vector (Vec2)
     */
    static Vec2 GetScreenCenter( );
    /**
     * Get the corner screen vector for positioning a node (game object/item)
     * @param position (required) where would you like to position the button (SonarCocosHelper::UIButtonPosition::eBottomLeft, SonarCocosHelper::UIButtonPosition::eBottomRight, SonarCocosHelper::UIButtonPosition::eTopLeft, SonarCocosHelper::UIButtonPosition::eTopRight)
     * @return screem corner Vector (Vec2)
     */
    static Vec2 GetScreenCorner( int position, Node *itemToPosition );

private:
    ui::Button *audioToggleButton;
    ui::Button *soundEffectsToggleButton;
    ui::Button *musicToggleButton;

    class Audio
    {
    public:
        static std::string offButtonString;
        static std::string offButtonPressedString;
        static std::string onButtonString;
        static std::string onButtonPressedString;
    };

    class SoundEffects
    {
    public:
        static std::string offButtonString;
        static std::string offButtonPressedString;
        static std::string onButtonString;
        static std::string onButtonPressedString;
    };

    class Music
    {
    public:
        static std::string offButtonString;
        static std::string offButtonPressedString;
        static std::string onButtonString;
        static std::string onButtonPressedString;
    };

    void AudioTouchEvent( Ref *sender, Widget::TouchEventType type );
    void SoundEffectsTouchEvent( Ref *sender, Widget::TouchEventType type );
    void MusicTouchEvent( Ref *sender, Widget::TouchEventType type );
};
}

#endif /* FlashHelper_h */
