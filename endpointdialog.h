#ifndef ENDPOINTDIALOG_H
#define ENDPOINTDIALOG_H

#include <QDialog>

namespace Ui {
class EndpointDialog;
}

class EndpointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndpointDialog(QWidget *parent = nullptr, const QString &endpoint="");
    ~EndpointDialog();

    QString endpoint() const;

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::EndpointDialog *ui;
    QString m_endpoint;
};

#endif // ENDPOINTDIALOG_H
