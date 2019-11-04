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
    QVBoxLayout* boxLayout = new QVBoxLayout(ui->webviewFrame);
    boxLayout->setContentsMargins(0, 0, 0, 0);
    boxLayout->setSpacing(16);

    m_webview = new QCefView(ui->webviewFrame);
    m_webview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    boxLayout->addWidget(m_webview);

    connect(m_webview, SIGNAL(webMsgReceived(QString)), this, SLOT(onRecvFromWeb(QString)));

    connect(ui->btnGo, &QPushButton::clicked, this, [this]() {
        m_webview->load(QUrl(ui->editAddress->text()));
    });
}

void MainDlg::onRecvFromWeb(QString msg)
{
    QMessageBox::information(this, "Received Message from Web Page", msg);
}
