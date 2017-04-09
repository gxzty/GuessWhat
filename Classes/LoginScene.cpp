#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "./base/macro/mButton.h"
#include "./base/network/Http.h"

LoginScene* LoginScene::_instance = nullptr;

Scene* LoginScene::createScene() {
    Scene* scene = Scene::create();
    LoginScene* layer = LoginScene::create();
    scene->addChild(layer);
    return scene;
}


LoginScene* LoginScene::getInstance() {
    return _instance;
}

bool LoginScene::init() {
    if (!Layer::init()) {
        return false;
    }

    rootNode = CSLoader::createNode("Login/LoginScene.csb");
    this->addChild(rootNode);
    
    loginNode = rootNode->getChildByName("loginNode");

    accountText = static_cast<TextField*>(loginNode->getChildByName("accountText"));
    passwordText = static_cast<TextField*>(loginNode->getChildByName("passwordText"));
    nickNameText = static_cast<TextField*>(loginNode->getChildByName("nickNameText"));

    auto listence0 = EventListenerCustom::create("LOGIN_login", CC_CALLBACK_1(LoginScene::loginSusses, this));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listence0, this);
    auto listence1 = EventListenerCustom::create("LOGIN_regit_0", CC_CALLBACK_1(LoginScene::regitSusses, this));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listence1, this);


    INITBTN(regitBtn, loginNode, "regitBtn", [&](Ref*) {
        std::string _url = "account";
        const char* __url = __String::createWithFormat("%s%s",
            SERVER_URL, _url.c_str()
            )->getCString();
        const  char* _data = __String::createWithFormat("account=%s&password=%s&nickName=%s",
            accountText->getString().c_str(), passwordText->getString().c_str(),nickNameText->getString().c_str()
            )->getCString();
            Http::getInstance()->sendHttpRequest(__url, HttpRequest::Type::POST, "LOGIN_regit",_data);
    });

    INITBTN(loginBtn, loginNode, "loginBtn", [&](Ref*) {
        std::string _url = "account";
        const char* __url = __String::createWithFormat("%s%s?account=%s&password=%s",
            SERVER_URL, _url.c_str(), accountText->getString().c_str(), passwordText->getString().c_str()
            )->getCString();
        Http::getInstance()->sendHttpRequest(__url, HttpRequest::Type::GET,"LOGIN_login");
    });
    
    return true;
}

void LoginScene::loginSusses(Ref*) {
    CCLOG("nickName:%s", PlayerVO::szNickName.c_str());
    nickNameText->setString(PlayerVO::szNickName);
}
void LoginScene::regitSusses(Ref*) {
    CCLOG("nickName:%s", PlayerVO::szNickName.c_str());
    nickNameText->setString(PlayerVO::szNickName);
}