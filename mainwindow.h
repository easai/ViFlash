#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "word.h"
#include <QMainWindow>
#include <QNetworkAccessManager>

#define AUTHOR "easai"
#define APPNAME "ViFlash"
#define WINDOW "Window"
#define GEOMETRY "Geometry"
#define APIURL "API"
#define ENDPOINT "https://botudien.pythonanywhere.com/api/nrand/1"

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

private slots:
  void refresh();
  void about();
  void setEndpoint();

private:
  Ui::ViFlash *ui;
  QString m_endpoint;
  QNetworkAccessManager *net_manager;
  QNetworkReply *net_reply;
  QByteArray *m_data_buffer;
  void saveSettings();
  void loadSettings();
  void setWord(const Word &word);
};
#endif // MAINWINDOW_H
