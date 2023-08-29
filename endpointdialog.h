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
    explicit EndpointDialog(QWidget *parent = nullptr, const QString &endpoint="", const QString &target="", const QString &desc="");
    ~EndpointDialog();
    QString endpoint() const;
    QString target() const;
    QString desc() const;

private slots:
    void saveEndpoint();
    void resetEndpoint();

private:
    Ui::EndpointDialog *ui;
    QString m_endpoint;
    QString m_target;
    QString m_desc;
};

#endif // ENDPOINTDIALOG_H
