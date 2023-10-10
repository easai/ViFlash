#include "word.h"
#include "wordlist.h"

WordList::WordList()
{

}

WordList::operator QString() const
{
    QString res = "";
    int nRows=this->count();
    for(int i=0;i<nRows;i++){
        Word word=this->at(i);
        res += word;
    }
    return res;
}

QString WordList::format(const QString target, const QString desc)
{
    QString res = "";
    int nRows=this->count();
    for(int i=0;i<nRows;i++){
        Word word=this->at(i);
        res += word.getValue(target)+": "+word.getValue(desc);
    }
    return res;
}

