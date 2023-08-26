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
}

EndpointDialog::~EndpointDialog()
{
    delete ui;
}


void EndpointDialog::on_buttonBox_accepted()
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


void EndpointDialog::on_pushButton_clicked()
{
    m_endpoint=ENDPOINT;
    ui->lineEdit->setText(m_endpoint);
}

