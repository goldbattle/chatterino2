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
    QUrl twitchUrl("https://www.twitch.tv/" + channel);
    //QString twitchEmbedd("<html><body><div id=\"twitch-embed\"></div><script src=\"https://embed.twitch.tv/embed/v1.js\"></script><script type=\"text/javascript\">new Twitch.Embed(\"twitch-embed\", { width: \"100%\", height: \"100%\", channel: \""+channel+"\", parent: [\"twitch.tv\"] });</script></body></html>");
    if (getIfWebviewHidden())
    {
        view = std::make_shared<QWebEngineView>();
        view->show();
        view->resize(700, 500);
        view->setUrl(twitchUrl);
        //view->setHtml(twitchEmbedd, QUrl("https://www.twitch.tv/"));
        lastChannelChange = channel;
    }
    else if (!getIfWebviewHidden() && lastChannelChange != channel)
    {
        view->setUrl(twitchUrl);
        //view->setHtml(twitchEmbedd, QUrl("https://www.twitch.tv/"));
        lastChannelChange = channel;
    }
}

}  // namespace chatterino
