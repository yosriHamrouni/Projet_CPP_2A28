#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "voyage.h"
#include "dialog_stat.h"
#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include "qcustomplot.h"
#include <vector>
#include "connection.h"
#include <QFont>
#include "qrcode.h"
#include "qrwidget.h"
#include "QWidget"
#include <QFile>
#include <QPainter>
#include <string>
#include <QtSvg>
#include <QTextDocument>
#include <QTextEdit>
#include <fstream>
#include <QTextStream>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgGenerator>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QAbstractPrintDialog>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_num_voyag->setValidator( new QIntValidator(0, 9999999, this));
    ui->tab_voyageur_2->setModel(V.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quitter_button_clicked()
{
    this->close();

}

void MainWindow::on_le_ajouter_clicked()
{
    int num_voyage=ui->le_num_voyag->text().toInt();
    QString depart=ui->le_depart->text();
    QString destination=ui->le_destination->text();
    QString date_depart=ui->date_depart->text();
    QString date_retour=ui->date_retour->text();

    voyage V(num_voyage,depart,destination,date_depart,date_retour);

     bool test=V.ajouter();
     if (test){
         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("ajout effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tab_voyageur_2->setModel(V.afficher());
         ui->tab_voyageur_2->setModel(V.rechercher(""));
         ui->tab_voyageur_2->setModel(V.rechercher2(""));
         ui->tab_voyageur_2->setModel(V.rechercher3(""));



 }
     else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                     QObject::tr("ajout non effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);


 }


void MainWindow::on_boutton_supp_clicked()
{
    voyage VS;
    VS.setnum_voyage(ui->le_voyage_supp_2->text().toInt());
    bool test=VS.supprimer(VS.getnum_voyage());
    if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
ui->tab_voyageur_2->setModel(V.afficher());
ui->tab_voyageur_2->setModel(V.rechercher(""));
ui->tab_voyageur_2->setModel(V.rechercher2(""));
ui->tab_voyageur_2->setModel(V.rechercher3(""));



}
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

    /* int num_voyage = ui->comboBox->currentText().toInt();
        bool test=tmpclient.supprimer(num_voyage);
        if(test)
        {ui->tab_voyageur_2->setModel(tmpclient.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Supprimer un client"),
                        QObject::tr("client supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            QSqlQueryModel * model= new QSqlQueryModel;
            model->setQuery("SELECT MATRICULE_FISCALE FROM client");
            ui->comboBox_3->setModel(model);
            ui->comboBox_2->setModel(model);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un client"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

       */


void MainWindow::on_le_update_clicked()
{
    int num_voyage=ui->le_num_voyag->text().toInt();
    QString depart=ui->le_depart->text();
    QString destination=ui->le_destination->text();
    QString date_depart=ui->date_depart->text();
    QString date_retour=ui->date_retour->text();

    voyage V(num_voyage,depart,destination,date_depart,date_retour);

     bool test=V.update();
     if (test){
         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("update effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tab_voyageur_2->setModel(V.afficher());
         ui->tab_voyageur_2->setModel(V.rechercher(""));


 }
     else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                     QObject::tr("update non effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);


}


void MainWindow::on_recherche_button_clicked()
{
    QString search=ui->le_search_numv->text();
        ui->tab_voyageur_2->setModel(V.rechercher(search));
       }

void MainWindow::on_recherche_button_2_clicked()
{
    QString search2=ui->le_search_depart->text();
        ui->tab_voyageur_2->setModel(V.rechercher2(search2));

}

void MainWindow::on_recherche_button_3_clicked()
{
    QString search3=ui->le_search_destination->text();
        ui->tab_voyageur_2->setModel(V.rechercher3(search3));
}



void MainWindow::on_tri_button_clicked()
{

       ui->tab_voyageur_2->setModel(V.tri());
}

void MainWindow::on_tri_button_2_clicked()
{
     ui->tab_voyageur_2->setModel(V.tri2());
}


void MainWindow::on_tri_button_3_clicked()
{
     ui->tab_voyageur_2->setModel(V.tri3());
}



void MainWindow::on_pdf_button_clicked()
{
       V.genererPDFact();
       bool test=V.update();
       if (test){
           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("pdf is ready now.\n"
                                   " Click Cancel to exit."), QMessageBox::Cancel);
           ui->tab_voyageur_2->setModel(V.afficher());
           ui->tab_voyageur_2->setModel(V.rechercher(""));


   }
       else
           QMessageBox::critical(nullptr, QObject::tr("not OK"),
                       QObject::tr("pdf has failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);



}



void MainWindow::on_tab_voyageur_2_activated(const QModelIndex &index)
{
    int num_voyage=ui->tab_voyageur_2->model()->data(index).toInt();
    
        QString num_voyage_string = QString::number(num_voyage) ;
    
            QSqlQuery qry ;
            qry.prepare("SELECT* FROM VOYAGE WHERE num_voyage='"+num_voyage_string+"' or num_voyage='"+num_voyage_string+"' or depart='"+num_voyage_string+"' or destination='"+num_voyage_string+"' or date_depart='"+num_voyage_string+"'or date_retour='"+num_voyage_string+"'  " ) ;
            if(qry.exec())
            {
                while(qry.next())
                {
                    ui->le_num_voyag->setText(qry.value(0).toString()) ;
                    ui->le_depart->setText(qry.value(1).toString()) ;
                    ui->le_destination->setText(qry.value(2).toString()) ;
                    ui->date_depart->setText(qry.value(3).toString()) ;
                    ui->date_retour->setText(qry.value(4).toString()) ;
                    ui->le_voyage_supp_2->setText(qry.value(0).toString()) ;

                }
            }
}



void MainWindow::on_stat_button_clicked()
{
             QTableView table_necessiteux,table_n2;
                 QSqlQueryModel * Mod=new  QSqlQueryModel();
                 QSqlQueryModel * Mod2=new  QSqlQueryModel();
                      Connection c;
                      QSqlQuery qry,q2;
                      qry.prepare("select DESTINATION from VOYAGE");
                      qry.exec();
                      Mod->setQuery(qry);
                      table_necessiteux.setModel(Mod);

                      q2.prepare("select NUM_VOYAGE from VOYAGE group by DESTINATION");
                      q2.exec();
                      Mod2->setQuery(q2);
                      table_n2.setModel(Mod2);

                      c.closeConnection();

                     qDebug()<<table_necessiteux.model()->data(table_necessiteux.model()->index(0, 0)).toString().simplified();
                     qDebug()<<table_n2.model()->data(table_n2.model()->index(0, 0)).toInt();

                     const int rowCount = table_necessiteux.model()->rowCount();
                     const int rowCount2 = table_n2.model()->rowCount();



                    // set dark background gradient:
                     QLinearGradient gradient(0, 0, 0, 400);
                     gradient.setColorAt(0, QColor(192, 192, 192));
                     gradient.setColorAt(0.38, QColor(192, 192, 192));
                     gradient.setColorAt(1, QColor(70, 70, 70));
                     ui->customplot->setBackground(QBrush(gradient));

                     // create empty bar chart objects:
                     QCPBars *besoin = new QCPBars(ui->customplot->xAxis, ui->customplot->yAxis);

                     besoin->setAntialiased(false); // gives more crisp, pixel aligned bar borders

                     besoin->setStackingGap(1);

                     // set names and colors:

                     besoin->setName("Destinations");
                     besoin->setPen(QPen(QColor(0, 168, 140).lighter(130)));
                 besoin->setBrush(QColor(18, 116, 161));
                     // stack bars on top of each other:


                     // prepare x axis with needs' labels:
                     QVector<double> ticks;
                     QVector<QString> labels;

                     for(int i=0; i<rowCount; ++i){
                         ticks.push_back(i);
                         labels.push_back(table_necessiteux.model()->data(table_necessiteux.model()->index(i, 0)).toString().simplified());
                         qDebug()<<ticks[i];
                         qDebug()<<labels[i];
                     }
                     QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                     textTicker->addTicks(ticks, labels);
                     ui->customplot->xAxis->setTicker(textTicker);
                     ui->customplot->xAxis->setTickLabelRotation(60);
                     ui->customplot->xAxis->setSubTicks(false);
                     ui->customplot->xAxis->setTickLength(0, 4);
                     ui->customplot->xAxis->setRange(0, 8);
                     ui->customplot->xAxis->setBasePen(QPen(Qt::black));
                     ui->customplot->xAxis->setTickPen(QPen(Qt::black));
                     ui->customplot->xAxis->grid()->setVisible(true);
                     ui->customplot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                     ui->customplot->xAxis->setTickLabelColor(Qt::black);
                     ui->customplot->xAxis->setLabelColor(Qt::black);

                     // prepare y axis:
                     ui->customplot->yAxis->setRange(0,50);
                 ui->customplot->yAxis->setPadding(5); // a bit more space to the left border
                 ui->customplot->yAxis->setBasePen(QPen(Qt::white));
                 ui->customplot->yAxis->setTickPen(QPen(Qt::white));
                 ui->customplot->yAxis->setSubTickPen(QPen(Qt::white));
                 ui->customplot->yAxis->grid()->setSubGridVisible(true);
                 ui->customplot->yAxis->setTickLabelColor(Qt::white);
                 ui->customplot->yAxis->setLabelColor(Qt::white);
                 ui->customplot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
                 ui->customplot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

                     // Add data:
                     QVector<double>besoinData;

                     for(int i=0; i<rowCount2; ++i){
                         besoinData.push_back(table_n2.model()->data(table_n2.model()->index(i, 0)).toInt());
                         qDebug()<<besoinData;

                     }
                    besoin->setData(ticks, besoinData);

                     // setup legend:
                     ui->customplot->legend->setVisible(true);
                 ui->customplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                 ui->customplot->legend->setBrush(QColor(255, 255, 255, 100));
                 ui->customplot->legend->setBorderPen(Qt::NoPen);
                 QFont legendFont = font();
                 legendFont.setPointSize(10);
                 ui->customplot->legend->setFont(legendFont);
                 ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
                 ui->customplot->replot();
    }




  void MainWindow::on_qr_button_clicked()
    {
if(ui->tab_voyageur_2->currentIndex().row()==-1)
                    QMessageBox::information(nullptr, QObject::tr("suppression"),
                                             QObject::tr("Veuillez Choisir un num_voyage du tab.\n"
                                                         "Click Ok to exit."), QMessageBox::Ok);
                else
                {
                     int  Code=ui->tab_voyageur_2->model()->data(ui->tab_voyageur_2->model()->index(ui->tab_voyageur_2->currentIndex().row(),0)).toInt();
                     const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(std::to_string(Code).c_str(), qrcodegen::QrCode::Ecc::LOW);
                     std::ofstream myfile;
                     myfile.open ("qrcode.svg") ;
                     myfile << qr.toSvgString(1);
                     myfile.flush();
                     myfile.close();
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                     QPixmap pix( QSize(90, 90) );
                     QPainter pixPainter( &pix );
                    svgRenderer.render(&pixPainter);
                     ui->label_6->setPixmap(pix);
                }
}
/* void MainWindow::on_actionplay_video_triggered()
{
    player= new QMediaPlayer;
    vw=new QVideoWidget;

    auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",QDir::rootPath(),"Excel Files(*.mp4)");


    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile(filename));
    vw->setGeometry(100,100,300,400);
    vw->show();
    player->play();
}
void MainWindow::on_actionstop_video_triggered()
{
    player->stop();
    vw->close();
}
*/

void MainWindow::on_traduire_clicked()
{
    QString test ;
        test = ui->label_11->text();
        if(test=="Num_voyage")
        {
            ui->label_11->setText("Num_travel");
            ui->label_2->setText("Depart");
            ui->label_5->setText("Destination");
            ui->label->setText("Date_depart");
            ui->label_3->setText("Date_return");
            ui->label_12->setText("Look for");
            ui->label_13->setText("Erase");
            ui->label_15->setText("scan Qrcode");

            ui->tri_button->setText("sort by num_travel");
            ui->tri_button_2->setText("sort by depart");
            ui->tri_button_3->setText("sort by destination");

            ui->le_search_numv->setPlaceholderText("num_travel");
            ui->le_search_depart->setPlaceholderText("depart");
            ui->le_search_destination->setPlaceholderText("destination");
            ui->le_voyage_supp_2->setPlaceholderText("num travel to erase");

            ui->traduire->setText("translate in french");
            ui->le_ajouter->setText("Add");
            ui->quitter_button->setText("exit");

        }

        else
        {
            ui->label_11->setText("Num_voyage");
            ui->label_2->setText("Depart");
            ui->label_5->setText("Destination");
            ui->label->setText("Date_depart");
            ui->label_3->setText("Date_retour");
            ui->label_12->setText("chercher");
            ui->label_13->setText("supprimer");
            ui->label_15->setText("scanner Qrcode");

            ui->tri_button->setText("tri par num_voyage");
            ui->tri_button_2->setText("tri par depart");
            ui->tri_button_3->setText("tri par destination");

            ui->le_search_numv->setPlaceholderText("num_voyage");
            ui->le_search_depart->setPlaceholderText("depart");
            ui->le_search_destination->setPlaceholderText("destination");
            ui->le_voyage_supp_2->setPlaceholderText("num voyage a supprimé");

            ui->traduire->setText("traduire en anglais");
            ui->le_ajouter->setText("Ajouter");
            ui->quitter_button->setText("quitter");



        }

}

void MainWindow::on_pB_Stats_clicked()
{
    dialog_stat stats;
       stats.setModal(true);
       stats.exec();
}
void dialog_stat::on_pushButton_Fermer_clicked()
{
    close();
}
