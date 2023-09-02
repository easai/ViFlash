#include "endpointdialog.h"
#include "mainwindow.h"
#include "ui_settingsdialog.h"

EndpointDialog::EndpointDialog(QWidget *parent, const QString &endpoint,
                               const QString &target, const QString &desc)
    : QDialog(parent), ui(new Ui::SettingsDialog), m_endpoint(endpoint) {
  ui->setupUi(this);
  ui->lineEdit->setText(endpoint);
  ui->lineEdit_target->setText(target);
  ui->lineEdit_desc->setText(desc);

  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &EndpointDialog::saveEndpoint);
  connect(ui->pushButton, &QPushButton::clicked, this,
          &EndpointDialog::resetEndpoint);
}

EndpointDialog::~EndpointDialog() { delete ui; }

void EndpointDialog::saveEndpoint() {
  QString url = ui->lineEdit->text();
  QString target = ui->lineEdit_target->text();
  QString desc = ui->lineEdit_desc->text();
  if (!url.isEmpty() && !target.isEmpty() && !desc.isEmpty()) {
    m_endpoint = url;
    m_target = target;
    m_desc = desc;
  }
}

void EndpointDialog::resetEndpoint() {
  m_endpoint = DEFAULT_ENDPOINT;
  ui->lineEdit->setText(m_endpoint);
  m_target = DEFAULT_TARGET;
  ui->lineEdit_target->setText(m_target);
  m_desc = DEFAULT_DESC;
  ui->lineEdit_desc->setText(m_desc);
}

QString EndpointDialog::endpoint() const { return m_endpoint; }

QString EndpointDialog::desc() const { return m_desc; }

QString EndpointDialog::target() const { return m_target; }
