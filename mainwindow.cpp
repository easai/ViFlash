#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"
#include <QApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ViFlash),
      net_manager(new QNetworkAccessManager(this)), net_reply(nullptr),
      m_data_buffer(new QByteArray) {
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::refresh);
  connect(ui->action_Quit, &QAction::triggered, this, &QApplication::quit);
  connect(ui->action_About, &QAction::triggered, this, &MainWindow::about);
  connect(ui->actionAbout_Qt, &QAction::triggered, this,
          &QApplication::aboutQt);
  refresh();
}

MainWindow::~MainWindow() {
  delete ui;
  delete m_data_buffer;
}

void MainWindow::dataReadyToRead() {
  m_data_buffer->append(net_reply->readAll());
}

void MainWindow::dataReadFinished() {
  if (net_reply->error()) {
    qDebug() << "Error : " << QString(*m_data_buffer);
  } else {
    QJsonDocument doc = QJsonDocument::fromJson(*m_data_buffer);
    QJsonArray array = doc.array();
    for (int i = 0; i < array.size(); i++) {
      QJsonObject object = array.at(i).toObject();
      QVariantMap map = object.toVariantMap();
      QString vi = map["vi"].toString();
      ui->label_vi->setText(vi);
      QString en = map["en"].toString();
      ui->label_en->setText(en);
    }
    m_data_buffer->clear();
  }
}

void MainWindow::refresh() {
  const QUrl API_ENDPOINT("https://botudien.pythonanywhere.com/api/nrand/1");
  QNetworkRequest request;
  request.setUrl(API_ENDPOINT);

  net_reply = net_manager->get(request);
  connect(net_reply, &QIODevice::readyRead, this, &MainWindow::dataReadyToRead);
  connect(net_reply, &QNetworkReply::finished, this,
          &MainWindow::dataReadFinished);
}

void MainWindow::about() {
  AboutDialog *dlg=new AboutDialog(this);
  dlg->exec();
}
