#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include "config.h"
#include <QDialog>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog {
  Q_OBJECT

public:
  explicit ConfigDialog(QWidget *parent = nullptr,
                        const Config &m_config = Config());
  ~ConfigDialog();
  Config config() const;

private slots:
  void saveEndpoint();
  void resetEndpoint();
  void selectFont();
  void selectColor();
  void selectBackground();
  void selectButton();

private:
  Ui::ConfigDialog *ui;
  Config m_config;
};

#endif // CONFIGDIALOG_H
