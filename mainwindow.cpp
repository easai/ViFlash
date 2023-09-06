#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"
#include "configdialog.h"
#include "word.h"
#include <QApplication>
#include <QClipboard>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkReply>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ViFlash), m_word(this),
      net_manager(new QNetworkAccessManager(this)), net_reply(nullptr),
      m_data_buffer(new QByteArray) {
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::refresh);
  connect(ui->action_Quit, &QAction::triggered, this, &QApplication::quit);
  connect(ui->action_Copy, &QAction::triggered, this, &MainWindow::copyWord);
  connect(ui->action_About, &QAction::triggered, this, &MainWindow::about);
  connect(ui->actionAbout_Qt, &QAction::triggered, this,
          &QApplication::aboutQt);
  connect(ui->action_Set_API_URL, &QAction::triggered, this,
          &MainWindow::setConfig);
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
      m_word.setDat(map);
      setWord();
    }
    m_data_buffer->clear();
  }
}

void MainWindow::copyWord() {
  QClipboard *clipboard = QGuiApplication::clipboard();
  QString word = "";
  word += ui->label_target->text();
  word += ": ";
  word += ui->label_desc->text();
  clipboard->setText(word);
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

void MainWindow::setConfig() {
  ConfigDialog *dlg = new ConfigDialog(this, m_endpoint, m_target, m_desc,
                                       m_font, m_color, m_background);
  auto res = dlg->exec();
  if (res == QDialog::Accepted) {
    m_endpoint = dlg->endpoint();
    m_target = dlg->target();
    m_desc = dlg->desc();
    m_font = dlg->font();
    m_color = dlg->color();
    m_background = dlg->background();
    setWord();
  }
}

void MainWindow::saveSettings() {
  QSettings settings(AUTHOR, APPNAME);
  settings.beginGroup(WINDOW);
  settings.setValue(GEOMETRY, saveGeometry());
  settings.setValue(APIURL, m_endpoint);
  settings.setValue(FONT, m_font.toString());
  settings.setValue(COLOR, m_color.name());
  settings.setValue(BACKGROUND, m_background.name());
  settings.endGroup();
  settings.beginGroup(LANG);
  settings.setValue(TARGET, m_target);
  settings.setValue(DESC, m_desc);
  settings.endGroup();
}

void MainWindow::loadSettings() {
  QSettings settings(AUTHOR, APPNAME);
  settings.beginGroup(WINDOW);
  restoreGeometry(settings.value(GEOMETRY).toByteArray());
  m_endpoint = settings.value(APIURL, DEFAULT_ENDPOINT).toString();
  m_font.fromString(settings.value(FONT).toString());
  m_color = QColor::fromString(settings.value(COLOR, "#000000").toString());
  m_background = QColor::fromString(settings.value(BACKGROUND, "#e0e0e0").toString());
  settings.endGroup();
  settings.beginGroup(LANG);
  m_target = settings.value(TARGET, DEFAULT_TARGET).toString();
  m_desc = settings.value(DESC, DEFAULT_DESC).toString();
  settings.endGroup();
}

void MainWindow::setWord() {
  ui->label_target->setText(m_word.getValue(m_target));
  ui->label_desc->setText(m_word.getValue(m_desc));
  ui->label_target->setFont(m_font);
  this->centralWidget()->setStyleSheet("background-color: " + m_background.name() + ";");
  QPalette palette = ui->label_target->palette();
  palette.setColor(QPalette::WindowText, m_color);
  ui->label_target->setPalette(palette);
  qDebug() << m_word;
}
