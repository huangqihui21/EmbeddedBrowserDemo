#include "QCefView.h"
#include <QMenu>
#include <QHBoxLayout>
#include <QEventLoop>

QCefView::QCefView(QWidget* parent) : QWidget(parent)
{
    m_cefWindow = new QCefWindow(windowHandle());

    m_cefClient = m_cefWindow->createBrowser();
    QEventLoop eventLoop;
    connect(m_cefClient, SIGNAL(browserCreated()),&eventLoop,SLOT(quit()));
    eventLoop.exec();

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    QWidget* windowContainer = createWindowContainer(m_cefWindow, this);
    layout->addWidget(windowContainer);
    setLayout(layout);

    QCefClient* cefClientPtr = m_cefClient.get();
    connect(cefClientPtr, SIGNAL(loadStarted(bool)), this, SIGNAL(loadStarted(bool)));
    connect(cefClientPtr, SIGNAL(loadFinished(bool, bool)), this, SIGNAL(loadFinished(bool, bool)));
    connect(cefClientPtr, SIGNAL(loadError(QString)), this, SIGNAL(loadError(QString)));
    connect(cefClientPtr, SIGNAL(webMsgReceived(QString)), this, SIGNAL(webMsgReceived(QString)));
    connect(cefClientPtr, SIGNAL(inspectorRequested()), this, SIGNAL(inspectorRequested()));
}

QCefView::~QCefView()
{
}

void QCefView::load(QUrl url)
{
    m_cefClient->load(url.toString().toStdString());
}

void QCefView::reload()
{
    m_cefClient->reload();
}

void QCefView::runJavaScript(QString script)
{
    CefRefPtr<CefFrame> frame = m_cefClient->browser()->GetMainFrame();
    frame->ExecuteJavaScript(script.toStdString(), frame->GetURL(), 0);
}

void QCefView::sendToWeb(QString msg)
{
    runJavaScript(QString("ckRecvMessage('%1');").arg(msg));
}
