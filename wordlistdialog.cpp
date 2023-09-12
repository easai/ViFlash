#include "wordlistdialog.h"
#include "ui_wordlistdialog.h"

WordListDialog::WordListDialog(QWidget *parent, const QList<Word> &lst, const QString &target, const QString &desc) :
    QDialog(parent),
    ui(new Ui::WordListDialog)
{
    ui->setupUi(this);
    for (int i=0;i<lst.count();i++){
        Word word=lst.at(i);
        QString targetWord=word.getValue(target);
        QString descWord=word.getValue(desc);
        ui->listWidget->addItem(targetWord+" : "+descWord);
    }
}

WordListDialog::~WordListDialog()
{
    delete ui;
}
