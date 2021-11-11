#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"
class MyApp : public CefApp, public CefRenderProcessHandler
{    
public:
    MyApp();
    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override
    {
        return this;
    }
    void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) override;
    IMPLEMENT_REFCOUNTING(MyApp);
};