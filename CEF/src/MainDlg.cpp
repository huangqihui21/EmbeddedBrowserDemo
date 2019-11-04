#include "MainDlg.h"
#include "ui_MainDlg.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QSplitter>
#include <QStackedLayout>
#include <QVBoxLayout>

MainDlg::MainDlg(QWidget* parent) : QDialog(parent),
                                                               ui(new Ui::MainDlg)
{
    ui->setupUi(this);
    initWebview();
}

MainDlg::~MainDlg()
{
    delete ui;
}

void MainDlg::initWebview()
{
    QCefView* page1 = new QCefView(this);
    page1->load( QUrl("www.baidu.com"));
    connect(page1, SIGNAL(webMsgReceived(QString)), this, SLOT(onRecvFromWeb(QString)));
    ui->tabWidget->addTab(page1, "baidu");

    QCefView* page2 = new QCefView(this);
    page2->load( QUrl("www.sohu.com"));
    ui->tabWidget->addTab(page2, "sohu");
    connect(page2, SIGNAL(webMsgReceived(QString)), this, SLOT(onRecvFromWeb(QString)));

    QCefView* page3 = new QCefView(this);
    page3->load( QUrl("www.sina.com"));
    ui->tabWidget->addTab(page3, "sina");
    connect(page3, SIGNAL(webMsgReceived(QString)), this, SLOT(onRecvFromWeb(QString)));

    connect(ui->btnGo, SIGNAL(clicked()), this, SLOT(onNavigate()));
}

void MainDlg::onRecvFromWeb(QString msg)
{
    QMessageBox::information(this, "Received Message from Web Page", msg);
}

void MainDlg::onNavigate()
{
    QCefView* webView = dynamic_cast<QCefView*>(ui->tabWidget->currentWidget());
    webView->load(QUrl(ui->editAddress->text()));
}
