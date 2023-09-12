#ifndef WORDLISTDIALOG_H
#define WORDLISTDIALOG_H

#include "word.h"
#include <QDialog>

namespace Ui {
class WordListDialog;
}

class WordListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WordListDialog(QWidget *parent = nullptr, const QList<Word> &lst=QList<Word>(), const QString &target="vi", const QString &desc="en");
    ~WordListDialog();

private:
    Ui::WordListDialog *ui;
};

#endif // WORDLISTDIALOG_H
