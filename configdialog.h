#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog {
  Q_OBJECT

public:
  explicit ConfigDialog(QWidget *parent = nullptr, const QString &endpoint = "",
                        const QString &target = "", const QString &desc = "",
                        const QFont &font = QFont("Helvetica [Cronyx]", 10),
                        const QColor &color = Qt::black,
                        const QColor &background = Qt::lightGray);
  ~ConfigDialog();
  QString endpoint() const;
  QString target() const;
  QString desc() const;
  QFont font() const;
  QColor color() const;
  QColor background() const;

  QColor button() const;

  private slots:
  void saveEndpoint();
  void resetEndpoint();
  void selectFont();
  void selectColor();
  void selectBackground();
  void selectButton();

private:
  Ui::ConfigDialog *ui;
  QString m_endpoint;
  QString m_target;
  QString m_desc;
  QFont m_font;
  QColor m_color;
  QColor m_background;
  QColor m_button;
};

#endif // CONFIGDIALOG_H
