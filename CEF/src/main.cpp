#include "MainDlg.h"
#include <QApplication>

#include "src/cef/QCefContext.h"

int main(int argc, char *argv[])
{
    int result = 0;

    result = QCefContext::getInstance()->initCef(argc, argv);
    if (result >= 0)
        return result;

    QApplication a(argc, argv);
    QApplication::addLibraryPath(".");

    MainDlg* browser = new MainDlg();
    browser->show();
    result = a.exec();

    delete browser;
    delete QCefContext::getInstance();

    CefShutdown();

    return result;
}
