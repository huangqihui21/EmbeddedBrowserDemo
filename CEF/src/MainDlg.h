#ifndef MAINDLG_H
#define MAINDLG_H

#include <QDialog>

#include "src/cef/QCefView.h"

namespace Ui {
class MainDlg;
}

class MainDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MainDlg(QWidget *parent = 0);
    ~MainDlg();

private:
    void initWebview();

private slots:
    void onRecvFromWeb(QString msg);

private:
    Ui::MainDlg *ui;
    QCefView* m_webview;
};

#endif // MAINDLG_H
