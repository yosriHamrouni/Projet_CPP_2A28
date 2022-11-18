#include "employee1.h"
#include "ui_employee1.h"

employee1::employee1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employee1)
{
    ui->setupUi(this);
}

employee1::~employee1()
{
    delete ui;
}
