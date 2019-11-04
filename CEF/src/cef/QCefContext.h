#ifndef QCEFINITIALIZER_H
#define QCEFINITIALIZER_H

#include "QCefApp.h"
#include "QCefRenderHandler.h"
#include "include/base/cef_logging.h"

#include <QMutex>

class QCefContext
{
public:
    QCefContext();
    ~QCefContext();

    //Init Cef
    int initCef(int argc, char *argv[]);

    static QCefContext *getInstance()
    {
        static QMutex mutex;
        if(_instance==nullptr)
        {
            QMutexLocker locker(&mutex);
            if(!_instance)
            {
                _instance = new QCefContext;
            }
        }
        return _instance;
    }

public:
    CefRefPtr<QCefApp> cefApp() const;
    CefRefPtr<QCefRenderHandler> cefRenderer() const;

    void setApplicationDir(const QString& path) {appDir = path;};

private:
    int initCef(CefMainArgs& mainArgs);

private:
    CefSettings m_settings;
    CefRefPtr<QCefApp> m_cefApp;
    CefRefPtr<QCefRenderHandler> m_cefRenderer;
    CefRefPtr<CefCommandLine> m_cmdLine;

    static QCefContext *_instance;
    QString appDir;
};

#endif // QCEFINITIALIZER_H
