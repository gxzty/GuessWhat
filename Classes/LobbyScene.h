#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d::ui;

class LobbyScene : public cocos2d::Layer
{
public:
    static Scene* createScene();
    static LobbyScene* getInstance();
    virtual bool init();
    CREATE_FUNC(LobbyScene);
private:
    static LobbyScene* _instance;
};

