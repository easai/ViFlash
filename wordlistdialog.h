#ifndef WORDLISTDIALOG_H
#define WORDLISTDIALOG_H

#include "wordlist.h"
#include <QDialog>

namespace Ui {
class WordListDialog;
}

class WordListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WordListDialog(QWidget *parent = nullptr, const WordList &lst=WordList(), const QString &target="vi", const QString &desc="en");
    ~WordListDialog();

private:
    void saveWordList();
    Ui::WordListDialog *ui;
    WordList m_wordlist;
    QString m_target;
    QString m_desc;
};

#endif // WORDLISTDIALOG_H
