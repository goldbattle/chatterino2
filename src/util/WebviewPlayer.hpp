#pragma once

#include <QString>
#include <QWindow>
#include <memory>

#include <QApplication>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEngineUrlRequestInterceptor>
#include <QWebEngineView>

namespace chatterino {

class RequestInterceptor : public QWebEngineUrlRequestInterceptor
{
public:
    RequestInterceptor(QObject *parent = nullptr)
        : QWebEngineUrlRequestInterceptor(parent)
    {
    }

    void interceptRequest(QWebEngineUrlRequestInfo &info) override
    {
        info.setHttpHeader("sec-ch-ua",
                           "\"Google Chrome\";v=\"93\", \" Not;A "
                           "Brand\";v=\"99\", \"Chromium\";v=\"93\"");
        info.setHttpHeader("sec-ch-ua-mobile", "");
        info.setHttpHeader("sec-ch-ua-platform", "?0");
        info.setHttpHeader("sec-ch-ua-platform", "\"Windows\"");
        info.setHttpHeader("sec-fetch-dest", "script");
        info.setHttpHeader("sec-fetch-mode", "no-cors");
        info.setHttpHeader("sec-fetch-site", "cross-site");
        info.setHttpHeader(
            "user-agent",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
            "(KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36");
    }
};

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
    RequestInterceptor interceptor;
    std::shared_ptr<QWebEngineView> view = nullptr;
};

}  // namespace chatterino
