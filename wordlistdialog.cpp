#include "wordlistdialog.h"
#include "ui_wordlistdialog.h"
#include <QFileDialog>

WordListDialog::WordListDialog(QWidget *parent, const WordList &lst, const QString &target, const QString &desc) :
    QDialog(parent), m_wordlist(lst), m_target(target), m_desc(desc),
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
    connect(ui->button_save, &QPushButton::clicked, this, &WordListDialog::saveWordList);
}

WordListDialog::~WordListDialog()
{
    delete ui;
}


void WordListDialog::saveWordList() {
    QString fn = QFileDialog::getSaveFileName(this, "Save as");
    if (fn.isEmpty())
        return;
    QFile file(fn);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;
    QTextStream out(&file);
    out << m_wordlist.format(m_target, m_desc) << "\n\n";
    file.close();
}
