#include "wordlistdialog.h"
#include "ui_wordlistdialog.h"

WordListDialog::WordListDialog(QWidget *parent, const QList<Word> &lst, const QString &target, const QString &desc) :
    QDialog(parent),
    ui(new Ui::WordListDialog)
{
    ui->setupUi(this);
    int nRows=lst.count();
    QStringList header;
    header << target << desc;

    ui->tableWidget->setColumnCount(header.count());
        ui->tableWidget->setHorizontalHeaderLabels(header);

    for (int i=0;i<nRows;i++){
        ui->tableWidget->insertRow(i);
        Word word=lst.at(i);
        QString targetWord=word.getValue(target);
        QTableWidgetItem *targetItem=new QTableWidgetItem(targetWord);
        ui->tableWidget->setItem(i, 0, targetItem);
        QString descWord=word.getValue(desc);
        QTableWidgetItem *descItem=new QTableWidgetItem(descWord);
        ui->tableWidget->setItem(i, 1, descItem);
    }
}

WordListDialog::~WordListDialog()
{
    delete ui;
}
