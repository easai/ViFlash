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
    explicit ConfigDialog(QWidget *parent = nullptr, const QString &endpoint="", const QString &target="", const QString &desc="", const QFont &font= QFont("Helvetica [Cronyx]", 10));
    ~ConfigDialog();
    QString endpoint() const;
    QString target() const;
    QString desc() const;
    QFont font() const;

private slots:
    void saveEndpoint();
    void resetEndpoint();
    void selectFont();

private:
    Ui::ConfigDialog *ui;
    QString m_endpoint;
    QString m_target;
    QString m_desc;
    QFont m_font;
};

#endif // CONFIGDIALOG_H
