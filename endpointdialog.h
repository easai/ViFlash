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
    void saveEndpoint();
    void resetEndpoint();

private:
    Ui::EndpointDialog *ui;
    QString m_endpoint;
};

#endif // ENDPOINTDIALOG_H
