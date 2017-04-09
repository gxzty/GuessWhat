#include "network/HttpClient.h"
#include "cocos2d.h"
#include "../macro/Define.h"
#include "../macro/mHttp.h"
#include "./json/document.h"

using namespace std;
using namespace cocos2d::network;
USING_NS_CC;

class Http {
public:
    Http();
    ~Http();
    static Http* getInstance();
    void sendHttpRequest(const char* _url, HttpRequest::Type _type, const char* _tag, const char* _data="");
    void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
private:
    static Http* _instance;
    HttpRequest* getRequest();
};
