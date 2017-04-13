#include "MyActions.h"


USING_NS_CC;
MyActions* MyActions::_instance = nullptr;

MyActions::MyActions() {
    _instance = this;
}

MyActions::~MyActions() {
    delete _instance;
    _instance = nullptr;
}

MyActions* MyActions::getInstance() {
    if (_instance == nullptr) {
        _instance = new MyActions();
    }
    return _instance;
}

Sequence* MyActions::TipsOpen() {
    return Sequence::create(TIPSBEGIN, SPAWN(SCALE(.2f, 1.1f), FADEIN(.2f)), SCALE(.1f, .9f), SCALE(.1f, 1.0f), nullptr);
}

Sequence* MyActions::TipsClose(const MyActionsFunc& func) {
    return Sequence::create(SCALE(.1f, .9f), SCALE(.1f, 1.1f), SPAWN(FADEOUT(.2f), SCALE(.2f, .01f)), CallFunc::create(func),nullptr);
}

Sequence* MyActions::roomListItem(int p) {
    int _p = (MAXROOMLISTITEM - p) * ROOMLISTITEMGAP - (ROOMLISTITEMGAP >> 1);
    Sequence* _s = Sequence::create(MOVETO(.03f, ROOLLISTMIDDLE, _p + 20), MOVETO(.05f, ROOLLISTMIDDLE, _p - 10), MOVETO(.03f, ROOLLISTMIDDLE, _p), nullptr);
    DelayTime* _delay = DelayTime::create(FLOAT(p) / 8.0f);
    return Sequence::create(MOVETO(.01f, ROOLLISTMIDDLE, -200.0f), _delay, MOVETO(.25f, ROOLLISTMIDDLE, _p), _s, nullptr);
}


cocos2d::Sequence* MyActions::shock(float startX /*= 0*/, float startY /*= 0*/, float radius /*= SHORKRADIUS*/, float time /*= SHORKTIME*/, int times /*= SHORKTIMES*/) {
    float _shorkGap = time / times;
    Sequence* _shork = Sequence::create(MOVETO(_shorkGap, (startX + RANDOM(radius)), startY + RANDOM(radius)),nullptr);
    for (int _times = 0; _times < times; ++_times) {
        _shork = Sequence::create(_shork, MOVETO(_shorkGap, (startX + RANDOM(radius)), startY + RANDOM(radius)), nullptr);
    }
    return Sequence::create(_shork, MOVETO(_shorkGap, startX, startY), nullptr);
}
