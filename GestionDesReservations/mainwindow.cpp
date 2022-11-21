#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "dialog_statistiques.h"
#include "dialog_mailing.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include <QPdfWriter>
#include <QPainter>
#include<QUrl>
#include <QTextStream>
#include <QTextDocument>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtWidgets>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->lineEdit_Mont->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox_ID->setModel(R.afficher_id());
    R.write(R.time(),"App started");
    ui->tab_res->setModel (R.afficher());
    connection c;
    bool test=c.CreateConnexion();
    if(test)
    {
        ui->label_db->setText("Database: CONNECTED");
    }
    else
        ui->label_db->setText("Database: FAILED");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pB_Ajouter_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->lineEdit_Prenom->text();
    int MONTANT=ui->lineEdit_Mont->text().toInt();
    reservation R(ID,NOM,PRENOM,MONTANT);
    bool test=R.ajouterS();
    if(test)
    {
        ui->label_Info->setText("Ajout effectué");
        ui->comboBox_ID->setModel(R.afficher_id());
        ui->tab_res->setModel(R.afficher());
        R.write(R.time(),"RESERVATION: Ajout effectué");
        ui->textBrowser_res->setText(R.read());
    }
    else
    {
        ui->label_Info->setText("Ajout non effectué");
    }
}

void MainWindow::on_pB_Supprimer_clicked()
{
    reservation R;
    R.setid(ui->comboBox_ID->currentText().toInt());
    bool test=R.supprimerS(R.getid());
    if(test)
    {
        ui->label_Info->setText("Suppression effectué");
        ui->tab_res->setModel(R.afficher());
        ui->comboBox_ID->setModel(R.afficher_id());
        R.write(R.time(),"RESERVATION: Suppression effectué");
        ui->textBrowser_res->setText(R.read());
    }
    else
    {
        ui->label_Info->setText("Suppression non effectué");
    }
}

void MainWindow::on_pB_Modifier_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->lineEdit_Prenom->text();
    int MONTANT=ui->lineEdit_Mont->text().toInt();
    reservation R(ID,NOM,PRENOM,MONTANT);
    bool test=R.modifierS();
    if(test)
    {
        ui->label_Info->setText("Modification effectué");
        ui->tab_res->setModel(R.afficher());
        ui->comboBox_ID->setModel(R.afficher_id());
        R.write(R.time(),"RESERVATION: Modification effectué");
        ui->textBrowser_res->setText(R.read());
    }
    else
    {
        ui->label_Info->setText("Modification non effectué");
    }
}

void MainWindow::on_pB_TirerParID_clicked()
{
    ui->label_Info->setText("Tri par ID effectué");
    ui->tab_res->setModel(R.tri_id());
}

void MainWindow::on_pB_TirerParType_clicked()
{
    ui->label_Info->setText("Tri par Nom effectué");
    ui->tab_res->setModel(R.tri_nom());
}

void MainWindow::on_comboBox_ID_currentIndexChanged(int)
{
    int id=ui->comboBox_ID->currentText().toInt();
        QString id_1=QString::number(id);
        QSqlQuery query;
        query.prepare("SELECT * FROM RESERVATION where ID='"+id_1+"'");
        if(query.exec())
        {
            while (query.next())
            {
                ui->lineEdit_ID->setText(query.value(0).toString()) ;
                ui->lineEdit_Nom->setText(query.value(1).toString()) ;
                ui->lineEdit_Prenom->setText(query.value(2).toString()) ;
                ui->lineEdit_Mont->setText(query.value(3).toString()) ;
            }
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                                  QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void MainWindow::on_pB_Recherche_clicked()
{
    reservation R;
    QString text;

    if (ui->rB_ID->isChecked()==true)
    {
        R.clearTable(ui->tab_res);
            int ID=ui->lineEdit_IDRecherche->text().toInt();
            R.chercheID(ui->tab_res,ID);
    }
    if (ui->rB_Nom->isChecked()==true)
    {
        R.clearTable(ui->tab_res);
            QString Nom=ui->lineEdit_IDRecherche->text();
            R.chercheNom(ui->tab_res,Nom);
    }
    if (ui->rB_Mont->isChecked()==true)
    {
        R.clearTable(ui->tab_res);
            int MONTANT=ui->lineEdit_IDRecherche->text().toInt();
            R.chercheMont(ui->tab_res,MONTANT);
    }
}

void MainWindow::on_pB_ExPDF_clicked()
{
    QPdfWriter pdf("C:/Users/pc/Desktop/GestionDesReservations/ListeReservation.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    //painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("D:/images/logo.png"));
    painter.drawText(3000,1500,"LISTE DES RESERVATIONS");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    //painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"ID");
    painter.drawText(2300,3300,"NOM");
    painter.drawText(4300,3300,"PRENOM");
    painter.drawText(6300,3300,"MONTANT");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select * from RESERVATION");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(6300,i,query.value(3).toString());
        painter.drawText(8000,i,query.value(4).toString());
        painter.drawText(10000,i,query.value(5).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/pc/Desktop/GestionDesReservations/ListeReservation.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void MainWindow::on_pushButton_SupprimerS_clicked()
{
    R.clearh();
    ui->textBrowser_res->setText(R.read());
}

void MainWindow::on_pushButton_Fermer_clicked()
{
    close();
}

void MainWindow::on_pB_Mailing_clicked()
{
    Dialog_Mailing mailing;
    mailing.setModal(true);
    mailing.exec();
}

void MainWindow::on_pB_Stats_clicked()
{
    Dialog_Statistiques stats;
    stats.setModal(true);
    stats.exec();
}

void MainWindow::on_pB_TirerParMontant_clicked()
{
    ui->label_Info->setText("Tri par Montant effectué");
    ui->tab_res->setModel(R.tri_Montant());
}
