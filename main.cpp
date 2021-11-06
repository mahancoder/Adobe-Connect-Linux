#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"
#include "MyApp.h"
#include "MyClient.h"
#include <unistd.h>
#include <gtk-3.0/gtk/gtk.h>
#include <gdk/gdkx.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <iostream>
using namespace std;
CefRefPtr<CefBrowser> browser;
void function(GdkEvent *event, gpointer data) 
{
        browser->GetHost()->CloseBrowser(true);
}
void destroy(gpointer data)
{
    cout << "Hi";
}
int main(int argc, char *argv[])
{
    string launch_args = string(argv[1]);

    CefMainArgs main_args(argc, argv);

    CefWindowInfo window_info;
    CefSettings settings;
    CefBrowserSettings browser_settings = CefBrowserSettings();

    CefRefPtr<MyApp> cefapp(new MyApp);
    CefRefPtr<MyClient> cefclient(new MyClient);

    string cache_path = "/home/" + string(getlogin()) + "/.config/";
    CefString(&settings.root_cache_path).FromString(cache_path);
    CefString(&settings.cache_path).FromString(cache_path + "adobe_connect/cache");
    CefString(&settings.user_agent).FromString("Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko");

    settings.remote_debugging_port = 9450;
    settings.no_sandbox = 1;

    CefInitialize(main_args, settings, cefapp.get(), nullptr);
    gtk_init(&argc, &argv);

    CefRefPtr<CefRequestContext> ctx = CefRequestContext::GetGlobalContext();

    CefRefPtr<CefValue> val(CefValue::Create());
    val->SetInt(1);

    CefString err = CefString();

    ctx->SetPreference("profile.default_content_setting_values.plugins", val, *&err);
    ctx->SetPreference("plugins.run_all_flash_in_allow_mode", val, *&err);

    browser_settings.application_cache = cef_state_t::STATE_ENABLED;
    CefString(&window_info.window_name).FromString("Adobe Connect");

    browser = CefBrowserHost::CreateBrowserSync(window_info, cefclient, launch_args.substr(11), browser_settings, nullptr, ctx);

    Window window_xid = browser->GetHost()->GetWindowHandle();
    auto gdk_display = gdk_display_get_default();
    auto window = gdk_x11_window_foreign_new_for_display(gdk_display, window_xid);
    gdk_window_maximize(window);
    gdk_window_set_icon_name(window, "Adobe Connect");
    XClassHint *hint = XAllocClassHint();
    char *name = new char(strlen("Adobe Connect") + 1);
    strcpy(name, "Adobe Connect");
    hint->res_class = name;
    hint->res_name = name;
    XSetClassHint(gdk_x11_get_default_xdisplay(), window_xid, hint);
    gdk_event_handler_set(function, window, destroy);
    CefRunMessageLoop();
    browser->GetHost()->CloseBrowser(true);
    CefQuitMessageLoop();
    CefShutdown();

    return 0;
}
