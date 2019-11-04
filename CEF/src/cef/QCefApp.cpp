﻿/*
 * QCefApp
* @brief: CefApp接口的实现
* @author: kevin_yang
* @note:
*/
#include "QCefApp.h"

QCefApp::QCefApp()
{
    m_contextReady = false;
}

QCefApp::~QCefApp()
{

}

void QCefApp::OnContextInitialized()
{
    CEF_REQUIRE_UI_THREAD();
    m_contextReady = true;
}

CefRefPtr<QCefClient> QCefApp::addBrowser(HWND hwnd)
{
    if (m_contextReady)
    {
        // Information used when creating the native window.
        CefWindowInfo windowInfo;
        RECT rc = { 0 };
#if defined(OS_WIN)
        // On Windows we need to specify certain flags that will be passed to
        // CreateWindowEx().
        windowInfo.SetAsChild(hwnd, rc);
#endif

        // SimpleHandler implements browser-level callbacks.
        CefRefPtr<QCefClient> client(new QCefClient());

        // Specify CEF browser settings here.
        CefBrowserSettings browserSettings;
        std::string url = "data:text/html,chromewebdata";

        // Create the first browser window.
        CefBrowserHost::CreateBrowser(windowInfo, client.get(), url,
                                      browserSettings, NULL);
        m_clients.enqueue(client);
        return client;
    }
    return nullptr;
}

void QCefApp::closeAllBrowser()
{
    while (!m_clients.empty())
    {
        m_clients.dequeue()->browser()->GetHost()->CloseBrowser(true);
    }
}
