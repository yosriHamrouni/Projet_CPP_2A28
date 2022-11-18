#ifndef EMPLOYEE1_H
#define EMPLOYEE1_H

#include <QDialog>

namespace Ui {
class employee1;
}

class employee1 : public QDialog
{
    Q_OBJECT

public:
    explicit employee1(QWidget *parent = nullptr);
    ~employee1();

private:
    Ui::employee1 *ui;
};

#endif // EMPLOYEE1_H
