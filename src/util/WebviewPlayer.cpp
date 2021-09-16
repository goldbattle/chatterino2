#include "WebviewPlayer.hpp"

namespace chatterino {

bool WebviewPlayer::getIfWebviewHidden()
{
    return view == NULL || !view->isVisible();
}

void WebviewPlayer::updateWebviewProcess(const QString &channel)
{
    // Create the window we will stream the video into
    // TODO: we should try to dock this to the application main window??
    // TODO: we should be able to handle having multiple webviews for multi-stream!
    //QUrl twitchUrl("https://www.twitch.tv/" + channel);
    QUrl twitchUrl("https://player.twitch.tv/?channel=" + channel +
                   "&enableExtensions=true&muted=false&parent=twitch.tv&player="
                   "popout&volume=0.25");
    //    QString twitchEmbedd(
    //        "<html><body><div id=\"twitch-embed\"></div><script "
    //        "src=\"https://embed.twitch.tv/embed/v1.js\"></script><script "
    //        "type=\"text/javascript\">new Twitch.Embed(\"twitch-embed\", { width: "
    //        "\"100%\", height: \"100%\", channel: \"" +
    //        channel + "\", parent: [\"twitch.tv\"] });</script></body></html>");
    //    QString testBrowser(
    //        R"(data:text/html,<!doctype html><html><body>hello</body><script>window.onload = function() {document.body.innerText = `hello, ${navigator.userAgent}`;</script></html>)");
    if (getIfWebviewHidden())
    {
        view = std::make_shared<QWebEngineView>();
        view->show();
        view->resize(700, 500);
        view->page()->profile()->setHttpUserAgent(
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
            "(KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36");
        view->page()->setDevToolsPage(view->page());

        // Interceptor to add headers....
        view->page()->profile()->setRequestInterceptor(&interceptor);

        view->setUrl(twitchUrl);
        //view->setHtml(twitchEmbedd, QUrl("https://www.twitch.tv/"));
        //view->setHtml(testBrowser, QUrl("https://www.twitch.tv/"));
        lastChannelChange = channel;
    }
    else if (!getIfWebviewHidden() && lastChannelChange != channel)
    {
        view->setUrl(twitchUrl);
        //view->setHtml(twitchEmbedd, QUrl("https://www.twitch.tv/"));
        //view->setHtml(testBrowser, QUrl("https://www.twitch.tv/"));
        lastChannelChange = channel;
    }
}

}  // namespace chatterino
