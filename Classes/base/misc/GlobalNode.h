#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

class GlobalNode {
public:
    GlobalNode();
    ~GlobalNode();
    static GlobalNode* getInstance();
    Sprite* m_sprite;
private:
    static GlobalNode* m_instance;
};