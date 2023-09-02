#include "configdialog.h"
#include "mainwindow.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent, const QString &endpoint,
                               const QString &target, const QString &desc)
    : QDialog(parent), ui(new Ui::ConfigDialog), m_endpoint(endpoint) {
  ui->setupUi(this);
  ui->lineEdit->setText(endpoint);
  ui->lineEdit_target->setText(target);
  ui->lineEdit_desc->setText(desc);

  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &ConfigDialog::saveEndpoint);
  connect(ui->pushButton, &QPushButton::clicked, this,
          &ConfigDialog::resetEndpoint);
}

ConfigDialog::~ConfigDialog() { delete ui; }

void ConfigDialog::saveEndpoint() {
  QString url = ui->lineEdit->text();
  QString target = ui->lineEdit_target->text();
  QString desc = ui->lineEdit_desc->text();
  if (!url.isEmpty() && !target.isEmpty() && !desc.isEmpty()) {
    m_endpoint = url;
    m_target = target;
    m_desc = desc;
  }
}

void ConfigDialog::resetEndpoint() {
  m_endpoint = DEFAULT_ENDPOINT;
  ui->lineEdit->setText(m_endpoint);
  m_target = DEFAULT_TARGET;
  ui->lineEdit_target->setText(m_target);
  m_desc = DEFAULT_DESC;
  ui->lineEdit_desc->setText(m_desc);
}

QString ConfigDialog::endpoint() const { return m_endpoint; }

QString ConfigDialog::desc() const { return m_desc; }

QString ConfigDialog::target() const { return m_target; }
