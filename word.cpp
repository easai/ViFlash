#include "word.h"


Word::Word(QObject *parent, const QVariantMap &map)
{
    this->vi = map["vi"].toString();
    this->en = map["en"].toString();
}

QString Word::getVi() const
{
    return vi;
}

QString Word::getEn() const
{
    return en;
}
