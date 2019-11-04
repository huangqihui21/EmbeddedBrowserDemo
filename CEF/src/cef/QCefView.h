#ifndef QCEFVIEW_H
#define QCEFVIEW_H

#include <QWidget>
#include <QTimer>
#include <QStackedLayout>
#include <QWindow>
#include <QUrl>
#include <QString>

#include "QCefApp.h"
#include "qcefwindow.h"

class QCefView : public QWidget
{
    Q_OBJECT
public:
    explicit QCefView(QWidget *parent = 0);
    virtual ~QCefView();

signals:
    void loadStarted(bool isMainFrame);
    void loadFinished(bool ok, bool isMainFrame);
    void loadError(QString errorStr);
    void webMsgReceived(QString msg);
    void inspectorRequested();



public:
    void load(QUrl url);
    void runJavaScript(QString script);
    void sendToWeb(QString msg);
    void reload();

protected:
    CefRefPtr<QCefClient> m_cefClient;

private:
    QCefWindow* m_cefWindow;
};

#endif // QCEFVIEW_H
