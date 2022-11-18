#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_clicked();

    void on_bin_image_clicked();

    void on_tri_clicked();

    void on_recherher_clicked();

    void on_tab_employe_activated(const QModelIndex &index);

    void on_pdf_clicked();

    void on_le_modd_clicked();

    void on_le_fich_excel_clicked();

    void on_tri_alpha_clicked();

   // void on_tri_salaire_clicked();

private:
    Ui::MainWindow *ui;
    Employe E;
};

#endif // MAINWINDOW_H
