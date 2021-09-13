#include "WebviewPlayer.hpp"

namespace chatterino {

bool WebviewPlayer::getIfWebviewHidden()
{
    return thread == NULL || webview == NULL || thread_done;
}

void WebviewPlayer::updateWebviewProcess(const QString &channel)
{
    // Create the attached window we will stream the video into
    // TODO: we should try to dock this to the application main window??
    // TODO: we should be able to handle having multiple webviews for multi-stream!
    if (getIfWebviewHidden())
    {
        thread_done = false;
        thread = std::make_shared<std::thread>([this, &channel]() {
            // create the webview
            std::string title = "SV " + std::to_string(std::time(nullptr));
            webview = webview_create(0, NULL);
            webview_set_title(webview, title.c_str());
            webview_set_size(webview, 480, 320, WEBVIEW_HINT_NONE);
            webview_set_size(webview, 480, 320, WEBVIEW_HINT_MIN);

            // Append script to auto maximize the stream on first load
            // This should run each time the page is refreshed
            // TODO: make this a bit more robust to slow page load times!
            std::string js = "document.onload = setTimeout(function() { "
                             "if(!window.has_inited) { "
                             "document.body.querySelector('[data-a-target="
                             "\"player-theatre-mode-button\"]').click(); "
                             "window.has_inited = true; } }, 2500);";
            webview_init(webview, js.c_str());

            // Then show the twitch stream to the user and the window
            lastChannelChange = channel;
            webview_navigate(
                webview,
                ("https://www.twitch.tv/" + channel.toStdString()).c_str());
            webview_run(webview);

            // for some reason there is no "destroy" c++ function..
            webview_destroy(webview);
            webview = NULL;
            thread_done = true;
        });
        thread->detach();
    }
    else
    {
        // Else just request the channel to change
        // We run this on the webview UI thread since the webview is async from our gui
        lastChannelRequest = channel;
        webview_dispatch(webview, &WebviewPlayer::callbackUpdateStreamInWebview,
                         NULL);
    }
}

void WebviewPlayer::callbackUpdateStreamInWebview(webview_t w, void *arg)
{
    WebviewPlayer &inst = WebviewPlayer::getInstance();
    if (inst.lastChannelChange != inst.lastChannelRequest)
    {
        inst.lastChannelChange = inst.lastChannelRequest;
        webview_navigate(
            w, ("https://www.twitch.tv/" + inst.lastChannelChange.toStdString())
                   .c_str());
    }
}

}  // namespace chatterino
