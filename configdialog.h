#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = nullptr, const QString &endpoint="", const QString &target="", const QString &desc="");
    ~ConfigDialog();
    QString endpoint() const;
    QString target() const;
    QString desc() const;

private slots:
    void saveEndpoint();
    void resetEndpoint();

private:
    Ui::ConfigDialog *ui;
    QString m_endpoint;
    QString m_target;
    QString m_desc;
};

#endif // CONFIGDIALOG_H
