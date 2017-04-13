#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "./base/macro/Define.h"
#include "./base/network/ODSocket/ODSocket.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

class LoginScene : public cocos2d::Layer {
public:
    static Scene* createScene();
    static LoginScene* getInstance();
    virtual bool init();
    CREATE_FUNC(LoginScene);
private:
    static LoginScene* _instance;
    Node* rootNode;
    Node* loginNode;
    TextField* accountText;
    TextField* passwordText;
    TextField* nickNameText;
    Button* regitBtn;
    Button* loginBtn;
    void loginSusses(Ref*);
    void loginFailed(Ref*);
    void regitSusses(Ref*);
    void regitFailed(Ref*);
    void receiveData();
    void sprAddGray(Sprite * sprite);
    void sprRemoveGray(Sprite * sprite);
    void capture(Ref* sender);
    void afterCapture(bool succeed, const std::string& outputFile);
    ODSocket socket;
};

