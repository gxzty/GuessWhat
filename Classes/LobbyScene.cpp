#include "LobbyScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

LobbyScene* LobbyScene::_instance = nullptr;

Scene* LobbyScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LobbyScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


LobbyScene* LobbyScene::getInstance() {
    if (_instance == nullptr) {
        _instance = LobbyScene::create();
    }
    return _instance;
}

// on "init" you need to initialize your instance
bool LobbyScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("Lobby/LobbyScene.csb");

    addChild(rootNode);

    return true;
}

