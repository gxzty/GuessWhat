#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../macro/mButton.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

class Tips : public cocos2d::Layer {
public:
    static Tips* show();
    virtual bool init();
    CREATE_FUNC(Tips);
private:
    Node* rootNode;
    Node* tipsNode;
    Button* closeBtn; 
    Sprite* forBlur;
    Node* captureNode;
    void afterCapture(bool succeed, const std::string& outputFile);
    void sprAddGray(Sprite* sp);
    void sprRemoveGray(Sprite * sprite);
};
