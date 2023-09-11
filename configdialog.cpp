#include "configdialog.h"
#include "mainwindow.h"
#include "ui_configdialog.h"
#include <QColorDialog>
#include <QFontDialog>

ConfigDialog::ConfigDialog(QWidget *parent, const Config &config)
    : QDialog(parent), ui(new Ui::ConfigDialog), m_config(config) {
  ui->setupUi(this);

  ui->lineEdit->setText(m_config.endpoint());
  ui->lineEdit_target->setText(m_config.target());
  ui->lineEdit_desc->setText(m_config.desc());

  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &ConfigDialog::saveEndpoint);
  connect(ui->pushButton, &QPushButton::clicked, this,
          &ConfigDialog::resetEndpoint);
  connect(ui->fontButton, &QPushButton::clicked, this,
          &ConfigDialog::selectFont);
  connect(ui->colorButton, &QPushButton::clicked, this,
          &ConfigDialog::selectColor);
  connect(ui->backgroundButton, &QPushButton::clicked, this,
          &ConfigDialog::selectBackground);
  connect(ui->buttonButton, &QPushButton::clicked, this,
          &ConfigDialog::selectButton);
}

ConfigDialog::~ConfigDialog() { delete ui; }

void ConfigDialog::saveEndpoint() {
  QString url = ui->lineEdit->text();
  QString target = ui->lineEdit_target->text();
  QString desc = ui->lineEdit_desc->text();
  if (!url.isEmpty() && !target.isEmpty() && !desc.isEmpty()) {
    m_config.setEndpoint(url);
    m_config.setTarget(target);
    m_config.setDesc(desc);
  }
}

void ConfigDialog::resetEndpoint() {
  m_config.setEndpoint(DEFAULT_ENDPOINT);
  ui->lineEdit->setText(DEFAULT_ENDPOINT);
  m_config.setTarget(DEFAULT_TARGET);
  ui->lineEdit_target->setText(DEFAULT_TARGET);
  m_config.setDesc(DEFAULT_DESC);
  ui->lineEdit_desc->setText(DEFAULT_DESC);
}

void ConfigDialog::selectFont() {
  bool ok;
  QFont font = QFontDialog::getFont(&ok, m_config.font(), this);
  if (ok) {
    m_config.setFont(font);
  } else {
  }
}

void ConfigDialog::selectColor() {
  QColor color = QColorDialog::getColor(m_config.color(), this, "Choose color");
  if (color.isValid()) {
    m_config.setColor(color);
  }
}

void ConfigDialog::selectBackground() {
  QColor color =
      QColorDialog::getColor(m_config.background(), this, "Choose color");
  if (color.isValid()) {
    m_config.setBackground(color);
  }
}

void ConfigDialog::selectButton() {
  QColor color =
      QColorDialog::getColor(m_config.button(), this, "Choose color");
  if (color.isValid()) {
    m_config.setButton(color);
  }
}

Config ConfigDialog::config() const { return m_config; }
