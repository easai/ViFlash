#ifndef WORD_H
#define WORD_H

#include <QObject>
#include <QVariantMap>

class Word : public QObject
{
    Q_OBJECT
public:
    explicit Word(QObject *parent, const QVariantMap &map, const QString &target_lang, const QString &desc_lang);
    QString getTarget() const;
    QString getDesc() const;

private:
    QString target;
    QString desc;
};

#endif // WORD_H
