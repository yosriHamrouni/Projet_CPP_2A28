#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "transport.h"
#include "smtp.h"
#include <QFile>
#include <QFileDialog>
#include<QObject>
#include <QSettings>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_7_clicked();


    void on_pb_supprimer_clicked();

    void on_pb_supprimer_2_clicked();

    void on_recher_clicked();

    void on_trier_2_clicked();

    void on_pushButton_3_clicked();

    void browse();

    void sendMail();

    void mailSent(QString);

private:
    Ui::MainWindow *ui;
    transport T ;
    QTcpSocket *socket ;
    QStringList files ;
};
#endif // MAINWINDOW_H
