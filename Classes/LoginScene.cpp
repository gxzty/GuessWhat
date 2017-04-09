#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "./base/macro/mButton.h"
#include "./base/macro/mMisc.h"
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

    // ��¼�ɹ�
    CUSTOM_EVENT_LISTENER("LOGIN_login_0", CC_CALLBACK_1(LoginScene::loginSusses, this));
    // ��¼ʧ��
    CUSTOM_EVENT_LISTENER("LOGIN_login_1", CC_CALLBACK_1(LoginScene::loginFailed, this));


    // ע��ɹ�
    CUSTOM_EVENT_LISTENER("LOGIN_regit_0", CC_CALLBACK_1(LoginScene::regitSusses, this));
    // ע��ʧ��
    CUSTOM_EVENT_LISTENER("LOGIN_regit_1", CC_CALLBACK_1(LoginScene::regitFailed, this));



    INITBTN(regitBtn, loginNode, "regitBtn", [&](Ref*) {
        std::string _url = "account";
        const char* __url = __String::createWithFormat(
            "%s%s",
            SERVER_URL, _url.c_str()
            )->getCString();
        const  char* _data = __String::createWithFormat(
            "account=%s&password=%s&nickName=%s",
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
    CCLOG("LoginSusses");
    socket.Init();
    socket.Create(AF_INET, SOCK_STREAM, 0);

    const char* ip = "45.58.54.172";
    int port = 1992;
    bool result = socket.Connect(ip, port);

    // �������� Send
    socket.Send("login", 5);

    if (result) {
        CCLOG("connect to server success!");
        // �������̣߳������߳��У���������
        std::thread recvThread = std::thread(&LoginScene::receiveData, this);
        recvThread.detach(); // �����̷߳���
    } else {
        CCLOG("can not connect to server");
        return;
    }

    nickNameText->setString(PlayerVO::szNickName);
}
void LoginScene::loginFailed(Ref*) {
    CCLOG("LoginFailed");
}

void LoginScene::regitSusses(Ref*) {
    CCLOG("regitSusses");
    nickNameText->setString(PlayerVO::szNickName);
}
void LoginScene::regitFailed(Ref*) {
    CCLOG("regitFailed");
}
void LoginScene::receiveData() {
    // ��Ϊ��ǿ����
    // ���Կ���һֱ��������Ƿ������ݴ���
    while (true) {
        // �������� Recv
        char data[512] = "";
        int result = socket.Recv(data, 512, 0);
        printf("%d", result);
        // ������������ӶϿ���
        if (result <= 0) break;

        CCLOG("%s", data);
    }
    // �ر�����
    socket.Close();
}