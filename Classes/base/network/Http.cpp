#include "Http.h"

std::string PlayerVO::szNickName = "";
std::string PlayerVO::szPassword = "";
std::string PlayerVO::szAccount = "";





Http* Http::_instance = nullptr;

Http::Http() {}

Http::~Http() {
    CCLOG("~Http");
}

Http* Http::getInstance() {
    if (_instance == nullptr) {
        _instance = new Http();
    }
    return _instance;
}

HttpRequest* Http::getRequest() {
    return new HttpRequest();
}

void Http::sendHttpRequest(const char* _url, HttpRequest::Type _type, const char* _tag,const char* _data) {
    auto _request = getRequest();
    CCLOG("%s", _url);
    //HTTPREQUEST(_request, _url, _type, _tag, Http::onHttpRequestCompleted, _data);
    _request->setUrl(_url);
    _request->setRequestType(_type);
    if (_type == HttpRequest::Type::POST) {
        _request->setRequestData(_data,strlen(_data));
    }
    _request->setResponseCallback(CC_CALLBACK_2(Http::onHttpRequestCompleted, this));
    _request->setTag(_tag);
    HttpClient::getInstance()->send(_request);
    // _request->autorelease();
}
int a = 0;
void Http::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response) {
    CCLOG("%d",a++);
    string strTag;
    rapidjson::Document document;
    ON_HTTP_COMPLET_CHECK(strTag, document);
    CCLOG("tag: %s", strTag.c_str());
    if (strTag == "LOGIN_login") {
        if (document.IsArray() && !document.Empty() &&
            document[0].HasMember("account") && document[0].HasMember("password")) {
            CCLOG("loginOK");
            PlayerVO::szNickName = document[0]["nickName"].GetString();
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(strTag, nullptr);
        } else {
            CCLOG("Wrong");
        }
    } else if (strTag == "LOGIN_regit") {
        if (document.IsArray() && !document.Empty() &&
            document[0].HasMember("account") && document[0].HasMember("password")) {
            CCLOG("loginOK");
            PlayerVO::szNickName = document[0]["nickName"].GetString();
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("LOGIN_regit_0", nullptr);
        } else {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("LOGIN_regit_1", nullptr);
        }
    }
    
    
    else {
        CCLOG("have no tag: %s", strTag.c_str());
    }
}
//response->getHttpRequest()->autorelease();
