#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"
#include "configdialog.h"
#include "word.h"
#include "wordlistdialog.h"
#include <QApplication>
#include <QClipboard>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkReply>
#include <QSettings>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ViFlash), m_word(this), m_config(this),
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
  connect(ui->action_Word_List, &QAction::triggered, this,
          &MainWindow::showWordList);
  connect(ui->action_Open_Botudien, &QAction::triggered, this, &MainWindow::openBotudien);
  loadSettings();
  setWindowIcon(QIcon("://images/favicon.ico"));
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
  const QUrl API_ENDPOINT(m_config.endpoint());
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
  ConfigDialog *dlg = new ConfigDialog(this, m_config);
  auto res = dlg->exec();
  if (res == QDialog::Accepted) {
    m_config = dlg->config();
    setWord();
  }
}

void MainWindow::showWordList()
{
  WordListDialog *dlg=new WordListDialog(this, m_wordlist, m_config.target(), m_config.desc());
  dlg->exec();
}

void MainWindow::openBotudien()
{
  const QUrl botudien("https://botudien.pythonanywhere.com/");
  QDesktopServices::openUrl(botudien);
}

void MainWindow::saveSettings() {
  QSettings settings(AUTHOR, APPNAME);
  settings.beginGroup(WINDOW);
  settings.setValue(GEOMETRY, saveGeometry());
  settings.setValue(APIURL, m_config.endpoint());
  settings.setValue(FONT, m_config.font().toString());
  settings.setValue(COLOR, m_config.color().name());
  settings.setValue(BACKGROUND, m_config.background().name());
  settings.setValue(BUTTON, m_config.button().name());
  settings.endGroup();
  settings.beginGroup(LANG);
  settings.setValue(TARGET, m_config.target());
  settings.setValue(DESC, m_config.desc());
  settings.endGroup();
}

void MainWindow::loadSettings() {
  QSettings settings(AUTHOR, APPNAME);
  settings.beginGroup(WINDOW);
  restoreGeometry(settings.value(GEOMETRY).toByteArray());
  m_config.setEndpoint(settings.value(APIURL, DEFAULT_ENDPOINT).toString());
  QFont font = ui->label_target->font();
  font.fromString(settings.value(FONT, font.toString()).toString());
  m_config.setFont(font);
  m_config.setColor(
      QColor::fromString(settings.value(COLOR, DEFAULT_COLOR).toString()));
  m_config.setBackground(
      QColor::fromString(settings.value(BACKGROUND, DEFAULT_BACKGROUND).toString()));
  m_config.setButton(
      QColor::fromString(settings.value(BUTTON, DEFAULT_BUTTON).toString()));
  settings.endGroup();
  settings.beginGroup(LANG);
  m_config.setTarget(settings.value(TARGET, DEFAULT_TARGET).toString());
  m_config.setDesc(settings.value(DESC, DEFAULT_DESC).toString());
  settings.endGroup();
}

void MainWindow::setWord() {
  ui->label_target->setText(m_word.getValue(m_config.target()));
  ui->label_desc->setText(m_word.getValue(m_config.desc()));
  ui->label_target->setFont(m_config.font());
  this->centralWidget()->setStyleSheet(
      "background-color: " + m_config.background().name() + ";");
  ui->pushButton->setStyleSheet("background: " + m_config.button().name() +
                                ";");
  QPalette palette = ui->label_target->palette();
  palette.setColor(QPalette::WindowText, m_config.color());
  ui->label_target->setPalette(palette);
  qDebug() << m_word;
  m_wordlist.append(m_word);
}
