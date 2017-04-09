#ifndef GLOBAL_BTN
#define GLOBAL_BTN


#define INITBTN(btn,node,name,callback)\
do {btn = static_cast<Button*>(node->getChildByName(name)); \
btn->addClickEventListener(callback); \
} while (0)

#endif