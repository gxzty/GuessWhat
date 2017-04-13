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

// �����б�
#define MAXROOMLISTITEM     4             // ���չʾ�б�����
#define ROOLLISTMIDDLE      485.0f        // ListView�߶Ȱ�ֵ
#define ROOMLISTITEMGAP     120           // �б���
#define WINDOWWIDTHMIDDLE   568.0f        // ���ڿ�Ȱ�ֵ
#define WINDOWHEIGHTMIDDLE  320.0f        // ���ڸ߶Ȱ�ֵ

// ��Ļ��
#define SHORKRADIUS   5.0f                      // �𶯰뾶
#define RANDOM(r)     random(-r,r)              // �����귶Χ
#define SHORKTIME     .5f                       // ����ʱ��
#define SHORKTIMES    30                        // �𶯴���
#define SHORKGAP      SHORKTIME/SHORKTIMES      // �����𶯼��


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