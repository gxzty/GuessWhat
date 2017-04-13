#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#define SCALE(t,s)      ScaleTo::create(t,s)
#define FADEOUT(t)      FadeOut::create(t)
#define FADEIN(t)       FadeIn::create(t)
#define SPAWN(m,n)      Spawn::createWithTwoActions(m,n)
#define TIPSBEGIN       SPAWN(FADEOUT(.01f),SCALE(.01f,.01f))
#define MOVETO(t,x,y)   MoveTo::create(t,Vec2((x),(y)))

#define FLOAT(x)        static_cast<float>(x)

// 房间列表
#define MAXROOMLISTITEM     4             // 最大展示列表数量
#define ROOLLISTMIDDLE      485.0f        // ListView高度半值
#define ROOMLISTITEMGAP     120           // 列表间隔
#define WINDOWWIDTHMIDDLE   568.0f        // 窗口宽度半值
#define WINDOWHEIGHTMIDDLE  320.0f        // 窗口高度半值

// 屏幕震动
#define SHORKRADIUS   5.0f                      // 震动半径
#define RANDOM(r)     random(-r,r)              // 震动坐标范围
#define SHORKTIME     .5f                       // 震动总时间
#define SHORKTIMES    30                        // 震动次数
#define SHORKGAP      SHORKTIME/SHORKTIMES      // 单次震动间隔


USING_NS_CC;

typedef std::function<void()> MyActionsFunc;
class MyActions {
public:
    MyActions();
    ~MyActions();
    static MyActions* getInstance();
    Sequence* TipsOpen();
    Sequence* TipsClose(const MyActionsFunc &func);
    Sequence* roomListItem(int p);
    Sequence* shock(float startX = 0, float startY = 0, float radius = SHORKRADIUS, float time = SHORKTIME, int times = SHORKTIMES);
private:
    static MyActions* _instance;
};