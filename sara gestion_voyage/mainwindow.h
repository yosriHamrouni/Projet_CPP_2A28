#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "voyage.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

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

    void on_le_ajouter_clicked();

    void on_boutton_supp_clicked();

    void on_le_update_clicked();

    void on_recherche_button_clicked();

    void on_tri_button_clicked();

    void on_tri_button_2_clicked();

    void on_tri_button_3_clicked();

    void on_pdf_button_clicked();

    void on_tab_voyageur_2_activated(const QModelIndex &index);

    void on_recherche_button_2_clicked();

    void on_recherche_button_3_clicked();

    void on_quitter_button_clicked();

    void on_stat_button_clicked();

    void on_qr_button_clicked();

    void on_traduire_clicked();

   void  on_pushButton_Fermer_clicked();


   void on_pB_Stats_clicked();

private:
    Ui::MainWindow *ui;
     QByteArray data;
    voyage V;


};

#endif // MAINWINDOW_H
