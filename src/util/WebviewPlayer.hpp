#pragma once

#include <QString>
#include <memory>

// header only library for webview
// needs to be built with cpp files!
// https://github.com/webview/webview
#include "webview.h"

namespace chatterino {

class WebviewPlayer
{
public:
    // Our singleton method
    static WebviewPlayer &getInstance()
    {
        static WebviewPlayer instance;
        return instance;
    }

    // Gets if the webview stream is hidden from the user
    bool getIfWebviewHidden();

    // This will open the attached webview player and play a given stream
    // If it is not open then this will try to open the window
    void updateWebviewProcess(const QString &channel);

private:
    // singleton cannot be created or copied
    WebviewPlayer()
    {
    }
    WebviewPlayer(WebviewPlayer const &);
    void operator=(WebviewPlayer const &);

    QString lastChannelChange = "";
    QString lastChannelRequest = "";
    //std::shared_ptr<std::thread> thread = nullptr;
    std::thread thread;
    webview_t webview = NULL;
    bool thread_done = true;

    // callback function which will run on webkit ui thread
    static void callbackUpdateStreamInWebview(webview_t w, void *arg);
};

}  // namespace chatterino
