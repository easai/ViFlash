#include "endpointdialog.h"
#include "ui_endpointdialog.h"
#include "mainwindow.h"

EndpointDialog::EndpointDialog(QWidget *parent, const QString &endpoint) :
    QDialog(parent),
    ui(new Ui::EndpointDialog),
    m_endpoint(endpoint)
{
    ui->setupUi(this);
    ui->lineEdit->setText(endpoint);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EndpointDialog::saveEndpoint);
    connect(ui->pushButton,  &QPushButton::clicked, this, &EndpointDialog::resetEndpoint);
}

EndpointDialog::~EndpointDialog()
{
    delete ui;
}


void EndpointDialog::saveEndpoint()
{
    QString url=ui->lineEdit->text();
    if(!url.isEmpty()){
        m_endpoint=url;
    }else{
        reject();
    }
}

QString EndpointDialog::endpoint() const
{
    return m_endpoint;
}


void EndpointDialog::resetEndpoint()
{
    m_endpoint=ENDPOINT;
    ui->lineEdit->setText(m_endpoint);
}

