#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
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
    Ui::SettingsDialog *ui;
    QString m_endpoint;
    QString m_target;
    QString m_desc;
};

#endif // SETTINGSDIALOG_H
