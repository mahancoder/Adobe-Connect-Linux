#include "MyApp.h"
#include "CEF/include/cef_app.h"
MyApp::MyApp()
{
}
void MyApp::OnBeforeCommandLineProcessing(const CefString &process_type, CefRefPtr<CefCommandLine> command_line)
{
    command_line->AppendSwitchWithValue("ppapi-flash-path", "./libpepflashplayer.so");
    command_line->AppendSwitchWithValue("ppapi-flash-version", "32.0.0.465");
    command_line->AppendSwitch("allow-outdated-plugins");
    command_line->AppendSwitchWithValue("plugin-policy", "allow");
    command_line->AppendSwitch("no-sandbox");
    command_line->AppendSwitch("enable-media-stream");
    command_line->AppendSwitch("enable-usermedia-screen-capturing");
}