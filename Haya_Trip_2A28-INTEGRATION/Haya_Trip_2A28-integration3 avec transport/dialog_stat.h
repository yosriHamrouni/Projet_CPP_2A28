#ifndef DIALOG_STAT_H
#define DIALOG_STAT_H

#include <QDialog>
#include <QDialog>
#include "QtPrintSupport"

namespace Ui {
class dialog_stat;
}

class dialog_stat : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_stat(QWidget *parent = nullptr);
    ~dialog_stat();

private slots:
    void on_pushButton_Fermer_clicked();

private:
    Ui::dialog_stat *ui;
    void MakeStat();
    void statistiques(QVector<double>* ticks,QVector<QString> *labels);
};

#endif // DIALOG_STAT_H

