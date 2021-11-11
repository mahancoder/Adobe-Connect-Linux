#include "CEF/include/cef_app.h"
#include "CEF/include/cef_client.h"
#include "CEF/include/wrapper/cef_helpers.h"
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