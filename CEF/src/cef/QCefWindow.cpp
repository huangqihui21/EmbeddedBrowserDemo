#include "QCefWindow.h"
#include "Windows.h"
#include "QCefContext.h"

QCefWindow::QCefWindow(QWindow *parent)
    : QWindow(parent)
{
    hwndCefBrowser = nullptr;
    setFlags(Qt::FramelessWindowHint);
}

QCefWindow::~QCefWindow()
{

}

CefRefPtr<QCefClient> QCefWindow::createBrowser()
{
    m_cefClient = QCefContext::getInstance()->cefApp()->addBrowser((HWND)winId());
    connect(m_cefClient, SIGNAL(browserCreated()), this, SLOT(embedBrowser()));
    return m_cefClient;
}

void QCefWindow::updateCefBrowserWindow()
{
    if (hwndCefBrowser)
        ::MoveWindow(hwndCefBrowser, 0, 0, width(), height(), TRUE);
}

void QCefWindow::resizeEvent(QResizeEvent *e)
{
    updateCefBrowserWindow();
    return QWindow::resizeEvent(e);
}

void QCefWindow::embedBrowser()
{
  //  disconnect(m_cefClient, SIGNAL(browserCreated()), this, SLOT(embedBrowser()));
    hwndCefBrowser = m_cefClient->browserWinId();
    updateCefBrowserWindow();
}
