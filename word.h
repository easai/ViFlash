#ifndef WORD_H
#define WORD_H

#include <QObject>
#include <QVariantMap>

class Word : public QObject
{
    Q_OBJECT
public:
    explicit Word(QObject *parent, const QVariantMap &map);

    QString getVi() const;

    QString getEn() const;

private:
    QString vi;
    QString en;
};

#endif // WORD_H
