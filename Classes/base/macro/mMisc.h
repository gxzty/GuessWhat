#ifndef GLOBAL_MISC
#define GLOBAL_MISC

#define CUSTOM_EVENT_LISTENER(_eventName, _callback) \
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(_eventName, _callback), this);

#define DISPATCH_CUSTOM_EVENT(_eventName) \
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(_eventName, nullptr);
#endif
