#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "reservation.h"
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
    void on_pB_Ajouter_clicked();

    void on_pB_Supprimer_clicked();

    void on_pB_Modifier_clicked();

    void on_pB_TirerParID_clicked();

    void on_pB_TirerParType_clicked();

    void on_comboBox_ID_currentIndexChanged(int index);

    void on_pB_Recherche_clicked();

    void on_pB_ExPDF_clicked();

    void on_pushButton_SupprimerS_clicked();

    void on_pushButton_Fermer_clicked();

    void on_pB_Mailing_clicked();

    void on_pB_Stats_clicked();

    void on_pB_TirerParMontant_clicked();

private:
    Ui::MainWindow *ui;
    reservation R;
};
#endif // MAINWINDOW_H
