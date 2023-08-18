#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>


QT_BEGIN_NAMESPACE
namespace Ui { class ViFlash; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void dataReadyToRead();
    void dataReadFinished();

private slots:
    void on_pushButton_clicked();

    void on_action_Quit_triggered();

    void on_actionAbout_Qt_triggered();

    void on_action_About_triggered();

private:
    Ui::ViFlash *ui;
    QNetworkAccessManager *net_manager;
    QNetworkReply *net_reply;
    QByteArray *m_data_buffer;
};
#endif // MAINWINDOW_H
