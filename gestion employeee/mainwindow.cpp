#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QDateTime>
#include <QTextStream>
#include <excel.h>
#include<QRegularExpression>
#include <arduino.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPieSeries *series=new QPieSeries();


    series->append("salalire inferieur à +1000 dinars ",80);
    series->append("salaire entre 1000 et 1500 dinars",70);
    series->append("salalire entre 1500 et 2000 dinars",60);
    series->append("salalire superieur à 2000 ",50);

    QChart *chart =new QChart();
    chart->addSeries(series);

    chart->setTitle("Pie chart for Employe s salary ");

    QChartView *chartview =new QChartView(chart);

    chartview->setParent(ui->horizontalFrame);
    ui->le_id->setValidator(new QIntValidator(0, 99999, this));


   ui->tab_employe->setModel(E.afficher());

   ui->horizontalLayout->addWidget(E.stat());
   /*
   ui->setupUi(this);
   int ret=A.connect_arduino(); // lancer la connexion à arduino
   switch(ret){
   case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
   break;
   case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
   break;
   case(-1):qDebug() << "arduino is not available";

   QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); */



 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{

    int id=ui->le_id->text().toInt();
    QString numero_telephone=ui->le_numero_telephone->text();
    QString salaire=ui->le_salaire->text();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString date_naissance=ui->le_date_naissance->text();
    QString image=ui->path->text();

    Employe E(id, numero_telephone,salaire,  nom, prenom, date_naissance,image);
    bool test=E.ajouter();
    QMessageBox msgBox;
    if(test)
       { msgBox.setText("Ajout avec succes.");
        ui->tab_employe->setModel(E.afficher());

    }
    else
        msgBox.setText("Echec de l'ajout.");
    msgBox.exec();
}

void MainWindow::on_pb_supprimer_clicked()
{
   Employe E1;
   E1.setid(ui->le_id_supp->text().toInt());
   bool test=E1.supprimer(E1.getid());
   QMessageBox msgBox;
   if(test)
   {msgBox.setText("Suppression avec succes.");
   ui->tab_employe->setModel(E.afficher());




   }
   else
       msgBox.setText("Echec de suppression.");

   msgBox.exec();
}

void MainWindow::on_pushButton_clicked()
{
    int id=ui->edit_id->text().toInt();
    QString numero_telephone=ui->edit_numero->text();
    QString salaire=ui->edit_salaire->text();
    QString nom=ui->edit_nom->text();
    QString prenom=ui->edit_prenom->text();
    QString date_naissance=ui->edit_date->text();
    QString image=ui->path->text();

          Employe E(id, numero_telephone,salaire, nom, prenom, date_naissance, image);


         bool test=E.update();
          if (test){
              QMessageBox::information(nullptr, QObject::tr("OK"),
                          QObject::tr("modification effectué.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);


      }
          else
            {  QMessageBox::critical(nullptr, QObject::tr("not OK"),
                          QObject::tr("modif non effectué.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);}
     ui->tab_employe->setModel(E.afficher());

}

void MainWindow::on_bin_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("choose"), "", tr("Image(*.png *.jpg *.jpeg *.bmp *.gif)")) ;
    if(QString::compare(filename, QString())!=0)
    {
       QImage image;
       bool valid = image.load(filename);
       if(valid)
       {
           image=image.scaledToWidth(ui->lbl_image_2->width(), Qt::SmoothTransformation);
          ui->lbl_image_2->setPixmap(QPixmap::fromImage(image));


          ui->path->setText(filename);
       }

    }


    }



void MainWindow::on_tri_clicked()
{
    Employe E;

    ui->tab_employe->setModel(E.tri());

    bool test=E.tri();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("tri effectué. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_recherher_clicked()
{

     QString search=ui->id_chercher->text();
            ui->tab_employe->setModel(E.Rechercher(search));


}

void MainWindow::on_tab_employe_activated(const QModelIndex &index)
{
    int id=ui->tab_employe->model()->data(index).toInt();
     QImage image;

        QString id_string = QString::number(id) ;


       /*if (!test.createconnect()){

            qDebug()<<"Failed to open dtabase";

            return;
               }*/


            QSqlQuery qry;
            qry.prepare("SELECT* FROM EMPLOYES WHERE ID='"+id_string+"' or NOM='"+id_string+"' or NUMERO_TELEPHONE='"+id_string+"' or SALAIRE='"+id_string+"' or NOM='"+id_string+"'  or PRENOM='"+id_string+"' or DATE_NAISSANCE='"+id_string+"' or IMAGE='"+id_string+"'  ") ;
            if(qry.exec())
            {
                while(qry.next())
                {
                    ui->edit_id->setText(qry.value(0).toString()) ;
                    ui->edit_numero->setText(qry.value(1).toString()) ;
                    ui->edit_salaire->setText(qry.value(2).toString()) ;
                    ui->edit_nom->setText(qry.value(3).toString()) ;
                    ui->edit_prenom->setText(qry.value(4).toString()) ;
                    ui->edit_date->setText(qry.value(5).toString()) ;

                    image.load(qry.value(6).toString());
                    image=image.scaledToWidth(ui->aff_image->width(), Qt::SmoothTransformation);
                    ui->aff_image->setPixmap(QPixmap::fromImage(image));

                    image=image.scaledToWidth(ui->edit_image->width(), Qt::SmoothTransformation);
                    ui->edit_image->setPixmap(QPixmap::fromImage(image));
                }
            }


}

void MainWindow::on_le_modd_clicked()
{



    QString filename = QFileDialog::getOpenFileName(this, tr("choose"), "", tr("Image(*.png *.jpg *.jpeg *.bmp *.gif)")) ;
    if(QString::compare(filename, QString())!=0)
    {


        QImage image;
        bool valid = image.load(filename);



       if(valid)
       {
           image=image.scaledToWidth(ui->edit_image->width(), Qt::SmoothTransformation);
          ui->edit_image->setPixmap(QPixmap::fromImage(image));


          ui->path->setText(filename);
       }

    }

    }


void MainWindow::on_pdf_clicked()
{

    QString strStream;
            strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                if (QFileInfo(strStream).suffix().isEmpty())
                    { strStream.append(".pdf"); }

                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(strStream);

                      QTextStream out(&strStream);

                      const int rowCount = ui->tab_employe->model()->rowCount();
                      const int columnCount = ui->tab_employe->model()->columnCount();
                      QString TT = QDateTime::currentDateTime().toString();
                      out <<"<html>\n"
                            "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                          << "<title>ERP - COMmANDE LIST<title>\n "
                          << "</head>\n"
                          "<body bgcolor=#ffffff link=#5000A0>\n"
                             "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                            +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />" //path
                          "<h1 style=\"text-align: center;\"><strong> ****LISTE DES EMPLOYES **** </strong></h1>"

                          "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                            "</br> </br>";
                      // headers
                      out << "<thead><tr bgcolor=#d6e5ff>";
                      for (int column = 0; column < columnCount; column++)
                          if (!ui->tab_employe->isColumnHidden(column))
                              out << QString("<th>%1</th>").arg(ui->tab_employe->model()->headerData(column, Qt::Horizontal).toString());
                      out << "</tr></thead>\n";

                      // data table
                      for (int row = 0; row < rowCount; row++) {
                          out << "<tr>";
                          for (int column = 0; column < columnCount; column++)
                        {
                              if (!ui->tab_employe->isColumnHidden(column)) {
                                  QString data =ui->tab_employe->model()->data(ui->tab_employe->model()->index(row, column)).toString().simplified();
                                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;")); //pas compriis
                              }
                          }
                          out << "</tr>\n";
                      }
                      out <<  "</table>\n"
                          "</body>\n"
                          "</html>\n";

                      QTextDocument document;
                      document.setHtml(strStream);
                      document.print(&printer);
}






void MainWindow::on_le_fich_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                            tr("Excel Files (*.xls)"));
            if (fileName.isEmpty())
                return;

            ExportExcelObject obj(fileName, "mydata", ui->tab_employe);

            //colums to export

            obj.addField(0, "id", "char(20)");
            obj.addField(1, "numero_telephone", "char(20)");
            obj.addField(2, "salaire", "char(20)");
            obj.addField(3, "nom", "char(20)");
            obj.addField(4, "prenom", "char(20)");
            obj.addField(5, "date_naissance", "char(20)");


            int retVal = obj.export2Excel();
            if( retVal > 0)
            {
                QMessageBox::information(this, tr("Done"),
                                         QString(tr("%1 records exported!")).arg(retVal)
                                         );
            }
}

void MainWindow::on_tri_alpha_clicked()
{
    Employe E;

    ui->tab_employe->setModel(E.tri_alpha());

    bool test=E.tri();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("tri effectué. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

/*void MainWindow::on_tri_salaire_clicked()
{
    Employe E;

    ui->tab_employe->setModel(E.tri_salaire());

    bool test=E.tri();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("tri effectué. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}*/
