#ifndef QCEFWINDOW_H
#define QCEFWINDOW_H

#include <QWindow>
#include "QCefApp.h"

class QCefWindow : public QWindow
{
    Q_OBJECT
public:
    explicit QCefWindow(QWindow *parent = nullptr);
    ~QCefWindow();

    CefRefPtr<QCefClient> createBrowser();

public slots:
    void embedBrowser();

protected:
    virtual void resizeEvent(QResizeEvent *e);

private:
    HWND	hwndCefBrowser;
    CefRefPtr<QCefClient> m_cefClient;
    void updateCefBrowserWindow();
};

#endif // QCEFWINDOW_H
