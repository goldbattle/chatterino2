

INCLUDEPATH += $$PWD/webview/include/

# it seems that gtk has issues with QT's slot and signal macros
# thus this should disable those macros...
DEFINES += QT_NO_SIGNALS_SLOTS_KEYWORDS=1

win32 {

    INCLUDEPATH += $$PWD/webview/microsoft.web.webview2.1.0.664.37/build/native/include/
    LIBS += $$PWD/webview/microsoft.web.webview2.1.0.664.37/build/native/x64/WebView2LoaderStatic.lib
    LIBS += version.lib
    LIBS += Shell32.lib
#    LIBS += $$PWD/webview/dll/x64/WebView2Loader.dll
#    LIBS += $$PWD/webview/dll/x64/webview.dll

}

macx {

    LIBS += -framework WebKit
#    PKGCONFIG += gtk+-3.0 webkit2gtk-4.0

}

linux {

#    PKGCONFIG += pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0
    CONFIG += link_pkfconfig
    PKGCONFIG += gtk+-3.0 webkit2gtk-4.0

}


