#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"
#include "word.h"
#include <QMainWindow>
#include <QNetworkAccessManager>

#define AUTHOR "easai"
#define APPNAME "ViFlash"
#define WINDOW "Window"
#define GEOMETRY "Geometry"
#define APIURL "API"
#define DEFAULT_ENDPOINT "https://botudien.pythonanywhere.com/api/nrand/1"
#define LANG "Lang"
#define TARGET "Target"
#define DEFAULT_TARGET "vi"
#define DESC "Description"
#define DEFAULT_DESC "en"
#define FONT "Font"
#define COLOR "Color"
#define BACKGROUND "Background"
#define BUTTON "Button"

QT_BEGIN_NAMESPACE
namespace Ui {
class ViFlash;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void dataReadyToRead();
  void dataReadFinished();
  void copyWord();

private slots:
  void refresh();
  void about();
  void setConfig();
  void showWordList();

private:
  Ui::ViFlash *ui;
  Config m_config;
  Word m_word;
  QList<Word> m_wordlist;
  QNetworkAccessManager *net_manager;
  QNetworkReply *net_reply;
  QByteArray *m_data_buffer;
  void saveSettings();
  void loadSettings();
  void setWord();
};
#endif // MAINWINDOW_H
