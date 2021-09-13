#include "WebviewPlayer.hpp"

namespace chatterino {

bool WebviewPlayer::getIfWebviewHidden()
{
    return thread == nullptr || webview == nullptr || thread_done;
}

void WebviewPlayer::updateWebviewProcess(const QString &channel)
{
    // Create the attached window we will stream the video into
    // TODO: we should try to dock this to the application main window??
    if (getIfWebviewHidden())
    {
        thread_done = false;
        thread = std::make_shared<std::thread>([this, &channel]() {
            // create the webview
            webview = std::make_shared<webview::webview>(true, nullptr);
            webview->set_title("StreamView");
            webview->set_size(480, 320, WEBVIEW_HINT_NONE);
            webview->set_size(480, 320, WEBVIEW_HINT_MIN);

            // Append script to auto maximize the stream on first load
            // This should run each time the page is refreshed
            // TODO: make this a bit more robust to slow page load times!
            webview->init(
                "document.onload = setTimeout(function() { "
                "if(!window.has_inited) "
                "{ "
                "document.body.querySelector('[data-a-target=\"player-theatre-"
                "mode-"
                "button\"]').click(); window.has_inited = true; } }, 2500);");

            // Then show the twitch stream to the user and the window
            lastChannelChange = channel;
            webview->navigate("https://www.twitch.tv/" + channel.toStdString());
            webview->run();

            // for some reason there is no "destroy" c++ function..
            webview = nullptr;
            thread_done = true;
        });
        thread->detach();
    }
    else
    {
        // Else just request the channel to change
        // We run this on the webview UI thread since the webview is async from our gui
        webview->dispatch([this, channel] {
            if (lastChannelChange != channel)
            {
                webview->navigate("https://www.twitch.tv/" +
                                  channel.toStdString());
                lastChannelChange = channel;
            }
        });
    }
}
}  // namespace chatterino
