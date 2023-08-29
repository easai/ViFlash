#include "word.h"

Word::Word(QObject *parent, const QVariantMap &map, const QString &target_lang, const QString &desc_lang)
{
    this->target = map[target_lang].toString();
    this->desc = map[desc_lang].toString();
}


QString Word::getTarget() const
{
    return target;
}

QString Word::getDesc() const
{
    return desc;
}
