#ifndef GLOBAL_HTTP
#define GLOBAL_HTTP


#define HTTPREQUEST(request,URL,type,tag,callback,data) \
do {request->setUrl(URL); \
request->setRequestType(type); \
if (type == HttpRequest::Type::POST) {\
request->setRequestData(data);\
}\
request->setResponseCallback(CC_CALLBACK_2(callback, this)); \
request->setTag(tag); \
HttpClient::getInstance()->send(request); \
} while (0)

#define ON_HTTP_COMPLET_CHECK(strTag,document) \
if (!response) {\
return; \
}\
if (!response->isSucceed()) {    \
        CCLOG("response failed"); \
        CCLOG("error buffer: %s", response->getErrorBuffer()); \
        return; \
}\
strTag = response->getHttpRequest()->getTag(); \
int statusCode = response->getResponseCode(); \
std::vector<char> *responseData = response->getResponseData(); \
std::string responseStr = std::string(responseData->begin(), responseData->end()); \
CCLOG("responseStr: %s", responseStr.c_str()); \
document.Parse<0>(responseStr.c_str());

#endif