#include "word.h"
#include <iostream>

using namespace std;

Word::Word(QObject *parent, const QVariantMap &map) {
    m_dat=map;
}

Word::Word(QObject *parent)
{
}

QString Word::getValue(const QString &key) const { return m_dat[key].toString(); }

Word::operator QString() const
{
    QString res="";
    QList<QString> keys=m_dat.keys();
    for(int i=0;i<keys.size();i++)
    {
        QString key=keys[i];
        res+="["+key+"]"+m_dat[key].toString()+" ";
    }
    return res;
}

Word::Word(const Word &other)
    :m_dat(other.m_dat)
{

}

Word &Word::operator=(const Word &other)
{
    if (this != &other) {
        m_dat=other.m_dat;
    }
    return *this;
}

void Word::setDat(const QVariantMap &newDat)
{
    m_dat = newDat;
}
