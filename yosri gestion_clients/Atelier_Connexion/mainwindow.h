#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}


class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu ;
class QAction;

















class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
   // void on_pushButton_clicked();

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();




    //void on_comboBox_supp_activated(const QString &arg1);

    void on_pb_update_clicked();

    void on_tab_clients_activated(const QModelIndex &index);

    void on_pb_find_clicked();

    void on_pushButton_clicked();

    void on_pb_genererPdf_clicked();

private:
    Ui::MainWindow *ui;
    Client C;

    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;
    QMenu *mOptionsMenu;
    QAction *mEncenderAction;
    QAction  *mApagarAction;
    QAction *mCapturarAction;
  //  QAction



};

#endif // MAINWINDOW_H
