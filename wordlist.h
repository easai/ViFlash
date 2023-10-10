#ifndef WORDLIST_H
#define WORDLIST_H

#include "word.h"
#include <QList>

class WordList : public QList<Word>
{
public:
    WordList();
    operator QString() const;
    QString format(const QString target, const QString desc);
};

#endif // WORDLIST_H
