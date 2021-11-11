#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/wrapper/cef_helpers.h"
class MyClient : public CefClient, public CefLifeSpanHandler
{
private:
    IMPLEMENT_REFCOUNTING(MyClient);
public:
    MyClient();
};

MyClient::MyClient()
{
}