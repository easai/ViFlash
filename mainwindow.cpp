#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"
#include "endpointdialog.h"
#include "word.h"
#include <QApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkReply>
#include <QSettings>

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
  connect(ui->action_Set_API_URL, &QAction::triggered, this,
          &MainWindow::setEndpoint);
  loadSettings();
  refresh();
}

MainWindow::~MainWindow() {
  saveSettings();
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
      Word word(nullptr, map, m_target, m_desc);
      setWord(word);
    }
    m_data_buffer->clear();
  }
}

void MainWindow::refresh() {
  const QUrl API_ENDPOINT(m_endpoint);
  QNetworkRequest request;
  request.setUrl(API_ENDPOINT);

  net_reply = net_manager->get(request);
  connect(net_reply, &QIODevice::readyRead, this, &MainWindow::dataReadyToRead);
  connect(net_reply, &QNetworkReply::finished, this,
          &MainWindow::dataReadFinished);
}

void MainWindow::about() {
  AboutDialog *dlg = new AboutDialog(this);
  dlg->exec();
}

void MainWindow::setEndpoint() {
  EndpointDialog *dlg = new EndpointDialog(this, m_endpoint, m_target, m_desc);
  auto res = dlg->exec();
  if (res == QDialog::Accepted) {
    m_endpoint = dlg->endpoint();
    m_target = dlg->target();
    m_desc = dlg->desc();
  }
}

void MainWindow::saveSettings() {
  QSettings settings(AUTHOR, APPNAME);
  settings.beginGroup(WINDOW);
  settings.setValue(GEOMETRY, saveGeometry());
  settings.setValue(APIURL, m_endpoint);
  settings.setValue(TARGET, m_target);
  settings.setValue(DESC, m_desc);
  settings.endGroup();
}

void MainWindow::loadSettings() {
  QSettings settings(AUTHOR, APPNAME);
  settings.beginGroup(WINDOW);
  restoreGeometry(settings.value(GEOMETRY).toByteArray());
  m_endpoint = settings.value(APIURL, DEFAULT_ENDPOINT).toString();
  m_target = settings.value(TARGET, DEFAULT_TARGET).toString();
  m_desc = settings.value(DESC, DEFAULT_DESC).toString();
  settings.endGroup();
}

void MainWindow::setWord(const Word &word) {
  ui->label_target->setText(word.getTarget());
  ui->label_desc->setText(word.getDesc());
  qDebug() << word;
}
