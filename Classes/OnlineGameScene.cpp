#include "OnlineGameScene.h"
#include "FlashHelper/FlashHelper.h"
#include "constants.h"
#include <iostream>
#include <vector>

#include <json/document.h>
#include <json/writer.h>
#include <json/stringbuffer.h>

USING_NS_CC;

Scene *OnlineGameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OnlineGameScene::create();
    scene->addChild(layer);
    return scene;
}

bool OnlineGameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    FlashHelper::UI::AddCentredBackground(GAME_BACKGROUND_FILEPATH, this);
    waitingSprite = Sprite::create(WAITING_FILEPATH);
    waitingSprite->setPosition(FlashHelper::UI::GetScreenCenter());
    gridSprite = Sprite::create(GRID_FILEPATH);
    gridSprite->setPosition(FlashHelper::UI::GetScreenCenter());
    gridSprite->setVisible(false);
    this->addChild(gridSprite);
    this->addChild(waitingSprite);
    yourTurnLabel = Label::createWithTTF("Your Turn", "fonts/Marker Felt.ttf", 40);
    yourTurnLabel->setTextColor(Color4B(54, 57, 67, 255));
    yourTurnLabel->setPosition(FlashHelper::UI::GetScreenCenter().x, FlashHelper::UI::GetScreenCenter().y * 1.75);
    this->addChild(yourTurnLabel);
    yourTurnLabel->setVisible(false);

    opponentTurnLabel = Label::createWithTTF("Opponent's Turn", "fonts/Marker Felt.ttf", 40);
    opponentTurnLabel->setTextColor(Color4B(54, 57, 67, 255));
    opponentTurnLabel->setPosition(FlashHelper::UI::GetScreenCenter().x, FlashHelper::UI::GetScreenCenter().y * 1.75);
    this->addChild(opponentTurnLabel);
    opponentTurnLabel->setVisible(false);

    InitGridRects();
    InitGridPieces();

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            gridArray[x][y] = EMPTY_PIECE;
        }
    }

    turn = X_PIECE;
    gameState = STATE_PLAYING;

    auto *listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    // Initiate networkController
    ws = new NetworkController();
    ws->initialize(*this);
    ws->connect();

    g = new GameInfo();
    myTurn = 0;

    listener->onTouchBegan = CC_CALLBACK_2(OnlineGameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(OnlineGameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(OnlineGameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(OnlineGameScene::onTouchCancelled, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

bool OnlineGameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}
void OnlineGameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
}
void OnlineGameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (gameState == STATE_ON_GOING && myTurn == 1)
    {
        myTurn = 0;
        CheckAndPlacePiece(touch);
    }
}
void OnlineGameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
}

void OnlineGameScene::CheckAndPlacePiece(cocos2d::Touch *touch)
{
    Rect rect1 = gridSprite->getBoundingBox();
    Point touchPoint = touch->getLocation();

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (gridSpaces[x][y].containsPoint(touchPoint))
            {
                if (gridArray[x][y] == EMPTY_PIECE)
                {
                    gameState = STATE_PLACING_PIECE;
                    gridArray[x][y] = turn;
                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            std::cout << gridArray[i][j] << " ";
                        }
                        std::cout << "\n";
                    }
                    if ("x" == mySymbol)
                    {
                        gridPieces[x][y]->setTexture(X_PIECE_FILEPATH);
                    }
                    else if ("o" == mySymbol)
                    {
                        gridPieces[x][y]->setTexture(O_PIECE_FILEPATH);
                    }
                    yourTurnLabel->setVisible(false);
                    opponentTurnLabel->setVisible(true);
                    gridPieces[x][y]->setVisible(true);
                    // Send data to ws server
                    rapidjson::Document jsonStruct;
                    jsonStruct.SetObject();
                    rapidjson::Document::AllocatorType &allocator = jsonStruct.GetAllocator();
                    rapidjson::Value key("command_type", allocator);
                    rapidjson::Value value(COMMAND_TYPE_MOVE);
                    jsonStruct.AddMember(key, value, allocator);
                    rapidjson::Value key1("data", allocator);
                    std::string s = std::to_string(gridPieces[x][y]->getTag());
                    rapidjson::Value value1(s.c_str(), allocator);
                    jsonStruct.AddMember(key1, value1, allocator);
                    rapidjson::StringBuffer buffer;
                    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                    jsonStruct.Accept(writer);
                    std::string jsonString = buffer.GetString();
                    ws->send(jsonString);
                    //                    std::cout << "myturn - " << gameState << std::endl;
                    myTurn = 0;
                    //                    gridPieces[x][y]->runAction( Sequence::create( FadeIn::create( PIECE_FADE_IN_TIME ), CallFunc::create( std::bind( &OnlineGameScene::CheckWin, this, x, y) ), NULL ) );
                    gridPieces[x][y]->runAction(FadeIn::create(PIECE_FADE_IN_TIME));
                }
            }
        }
    }
}

std::vector<int> OnlineGameScene::getWinningCoordinates()
{
    std::vector<std::vector<int>> pos{
        {0, 0, 0, 1, 0, 2},
        {1, 0, 1, 1, 1, 2},
        {2, 0, 2, 1, 2, 2},
        {0, 0, 1, 0, 2, 0},
        {0, 1, 1, 1, 2, 1},
        {0, 2, 1, 2, 2, 2},
        {0, 0, 1, 1, 2, 2},
        {2, 0, 1, 1, 0, 2}};
    for (int i = 0; i < pos.size(); i++)
    {
        if ((gridArray[pos[i][0]][pos[i][1]] == gridArray[pos[i][2]][pos[i][3]]) && (gridArray[pos[i][2]][pos[i][3]] == gridArray[pos[i][4]][pos[i][5]]) && (gridArray[pos[i][0]][pos[i][1]] == O_PIECE || gridArray[pos[i][0]][pos[i][1]] == X_PIECE))
        {
            return pos[i];
        }
    }
    return pos[0];
}

void OnlineGameScene::CheckWin(int state)
{
    if (STATE_DRAW == state || STATE_LOSE == state || STATE_WON == state)
    {
        gameState = state;
        if (gameState != STATE_DRAW)
        {
            __String winningPieceStr;

            if (gameState == STATE_LOSE)
            {
                if (mySymbol == "x")
                    winningPieceStr = O_WINNING_PIECE_FILEPATH;
                else
                    winningPieceStr = X_WINNING_PIECE_FILEPATH;
            }
            else
            {
                if (mySymbol == "o")
                    winningPieceStr = O_WINNING_PIECE_FILEPATH;
                else
                    winningPieceStr = X_WINNING_PIECE_FILEPATH;
            }

            std::vector<int> v = OnlineGameScene::getWinningCoordinates();

            Sprite *winningPieces[3];

            winningPieces[0] = Sprite::create(winningPieceStr.getCString());
            winningPieces[0]->setPosition(gridPieces[v[0]][v[1]]->getPosition());
            winningPieces[0]->setOpacity(0);
            this->addChild(winningPieces[0]);
            winningPieces[1] = Sprite::create(winningPieceStr.getCString());
            winningPieces[1]->setPosition(gridPieces[v[2]][v[3]]->getPosition());
            winningPieces[1]->setOpacity(0);
            this->addChild(winningPieces[1]);
            winningPieces[2] = Sprite::create(winningPieceStr.getCString());
            winningPieces[2]->setPosition(gridPieces[v[4]][v[5]]->getPosition());
            winningPieces[2]->setOpacity(0);
            this->addChild(winningPieces[2]);

            winningPieces[0]->runAction(FadeIn::create(PIECE_FADE_IN_TIME));
            winningPieces[1]->runAction(Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 0.5), FadeIn::create(PIECE_FADE_IN_TIME), NULL));
            winningPieces[2]->runAction(Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 1.5), FadeIn::create(PIECE_FADE_IN_TIME), NULL));
        }
        ui->ShowGameOver(this, GAME_TYPE_ONLINE);
    }
}

void OnlineGameScene::onMessage(std::string msg)
{
    OnlineGameScene::parseJson(msg);
    if (g->commandType == COMMAND_TYPE_CONNECTED)
    {
        mySymbol = (g->turn == 1) ? "x" : "o";
        turn = (g->turn == 1) ? 1 : 0;
        OnlineGameScene::CommandMove();
    }
    else if (g->commandType == COMMAND_TYPE_PAUSE)
    {
        OnlineGameScene::CommandPause();
    }
    else if (g->commandType == COMMAND_TYPE_MOVE)
    {
        OnlineGameScene::CommandMove();
    }
    else if (g->commandType == COMMAND_TYPE_DISCONNECTED)
    {
        ui->GoToMainMenu(this);
    }
    else if (g->commandType == COMMAND_TYPE_RESULT)
    {
        OnlineGameScene::CheckWin(g->data);
    }
}

void OnlineGameScene::CommandPause()
{
    ui->PauseGameByOtherPlayer(this, g->data);
}

void OnlineGameScene::CommandMove()
{
    if (g->state == STATE_WAITING)
    {
        gameState = STATE_WAITING;
    }
    else if (g->state == STATE_CONNECTED)
    {
        if (waitingSprite->isVisible())
            waitingSprite->setVisible(false);
        if (g->turn == 1)
        {
            yourTurnLabel->setVisible(true);
            gameState = STATE_ON_GOING;
            myTurn = g->turn;
        }
        else
        {
            gameState = STATE_ON_GOING;
            opponentTurnLabel->setVisible(true);
        }
        ui = new UIOnlineGame(this, gameState, ws);
        gridSprite->setVisible(true);
    }
    else if (g->state == STATE_ON_GOING)
    {
        int x = g->data / 3;
        int y = g->data % 3;
        myTurn = g->turn;
        if (myTurn == 1)
        {
            yourTurnLabel->setVisible(true);
            opponentTurnLabel->setVisible(false);
        }
        else
        {
            yourTurnLabel->setVisible(false);
            opponentTurnLabel->setVisible(true);
        }
        Rect rect1 = GameScene::GetRectSpaceFromTag(g->data);
        gameState = STATE_PLACING_PIECE;
        if (mySymbol == "x")
        {
            gridArray[x][y] = O_PIECE;
            gridPieces[x][y]->setTexture(O_PIECE_FILEPATH);
        }
        else if (mySymbol == "o")
        {
            gridArray[x][y] = X_PIECE;
            gridPieces[x][y]->setTexture(X_PIECE_FILEPATH);
        }
        gridPieces[x][y]->setVisible(true);
        //        gridPieces[x][y]->runAction( Sequence::create( FadeIn::create( PIECE_FADE_IN_TIME ), CallFunc::create( std::bind( &OnlineGameScene::CheckWin, this, x, y) ), NULL ) );
        gridPieces[x][y]->runAction(FadeIn::create(PIECE_FADE_IN_TIME));
        gameState = STATE_ON_GOING;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                std::cout << gridArray[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
}

void OnlineGameScene::parseJson(std::string msg)
{
    rapidjson::Document document;
    document.Parse(msg.c_str());
    if (!document.HasParseError())
    {
        // Access the JSON fields
        if (document.HasMember("state") && document["state"].IsInt())
        {
            int stateValue = document["state"].GetInt();
            g->state = stateValue;
        }

        if (document.HasMember("data") && document["data"].IsString())
        {
            int dataValue = std::stoi(document["data"].GetString());
            g->data = dataValue;
        }

        if (document.HasMember("turn") && document["turn"].IsInt())
        {
            int turnValue = document["turn"].GetInt();
            g->turn = turnValue;
        }
        if (document.HasMember("command_type") && document["command_type"].IsInt())
        {
            int commandtypeValue = document["command_type"].GetInt();
            g->commandType = commandtypeValue;
        }
    }
    else
    {
        std::cout << "Failed to parse JSON: " << std::endl;
    }
}
