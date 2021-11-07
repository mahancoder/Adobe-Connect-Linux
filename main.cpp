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
#include <thread>
using namespace std;

CefRefPtr<CefBrowser> browser;
Display *main_display;
Window window_xid;
Window child_window;

volatile bool isOpen = true;

void event_loop()
{
    Atom wmDeleteMessage = XInternAtom(main_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(main_display, window_xid, &wmDeleteMessage, 1);
    XEvent event;
    while (true)
    {
        XNextEvent(main_display, &event);
        if (event.type == ClientMessage)
        {
            if (event.xclient.data.l[0] == wmDeleteMessage)
            {
                isOpen = false;
                XCloseDisplay(main_display);
                break;
            }
        }
        else if (event.type == ConfigureNotify)
        {
            auto ce = event.xconfigure;
            XResizeWindow(main_display, child_window, ce.width, ce.height);
            browser->GetHost()->WasResized();
        }
    }
}
void maximizeWindow(Window win, Display *display)
{
    XEvent ev;
    ev.xclient.window = win;
    ev.xclient.type = ClientMessage;
    ev.xclient.format = 32;
    ev.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
    ev.xclient.data.l[0] = 1;
    ev.xclient.data.l[1] = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
    ev.xclient.data.l[2] = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
    ev.xclient.data.l[3] = 1;

    XSendEvent(display, DefaultRootWindow(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &ev);
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

    settings.remote_debugging_port = 9450;
    settings.no_sandbox = 1;

    CefInitialize(main_args, settings, cefapp.get(), nullptr);

    CefRefPtr<CefRequestContext> ctx = CefRequestContext::GetGlobalContext();
    CefRefPtr<CefValue> val(CefValue::Create());
    val->SetInt(1);
    CefString err = CefString();
    ctx->SetPreference("profile.default_content_setting_values.plugins", val, *&err);
    ctx->SetPreference("plugins.run_all_flash_in_allow_mode", val, *&err);

    gtk_init(&argc, &argv);

    main_display = XOpenDisplay(0);
    Window root_window = XDefaultRootWindow(main_display);
    window_xid = XCreateWindow(main_display, root_window, 10, 10, 800, 600, 10, CopyFromParent, InputOutput, CopyFromParent, 0, nullptr);
    XMapWindow(main_display, window_xid);
    XFlush(main_display);
    XSelectInput(main_display, window_xid, StructureNotifyMask | PropertyChangeMask | SubstructureNotifyMask);
    XStoreName(main_display, window_xid, "Adobe Connect");
    window_info.SetAsChild(window_xid, CefRect(0, 0, 800, 600));

    browser_settings.application_cache = cef_state_t::STATE_ENABLED;
    CefString(&window_info.window_name).FromString("Adobe Connect");

    browser = CefBrowserHost::CreateBrowserSync(window_info, cefclient, launch_args.substr(11), browser_settings, nullptr, ctx);

    child_window = browser->GetHost()->GetWindowHandle();

    XClassHint *hint = XAllocClassHint();
    char *name = new char(strlen("Adobe Connect") + 1);
    strcpy(name, "Adobe Connect");
    hint->res_class = name;
    hint->res_name = name;
    XSetClassHint(main_display, window_xid, hint);

    maximizeWindow(window_xid, main_display);

    thread event_loop_thread(event_loop);

    while (isOpen)
    {
        CefDoMessageLoopWork();
        sleep((1000 / 30) / 1000);
    }

    CefShutdown();

    return 0;
}
