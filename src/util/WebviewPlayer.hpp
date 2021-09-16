#pragma once

#include <QWindow>
#include <QString>
#include <memory>

#include <QApplication>
#include <QWebEngineView>

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
    std::shared_ptr<QWebEngineView> view = nullptr;

};

}  // namespace chatterino
