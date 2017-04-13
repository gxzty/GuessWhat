#include "GlobalNode.h"


GlobalNode* GlobalNode::m_instance = nullptr;


GlobalNode::GlobalNode() {
    m_sprite = nullptr;
}

GlobalNode::~GlobalNode() {
    if (m_instance != nullptr) {
        delete m_instance;
    }
}

GlobalNode* GlobalNode::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new GlobalNode();
    }
    return m_instance;
}
//
//cocos2d::Sprite* GlobalNode::getGlobalSprite() {
//    CCASSERT(m_sprite == nullptr,"no sprite for use");
//    return m_sprite;
//}
