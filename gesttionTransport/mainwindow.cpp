#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transport.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include<QFile>
#include <QDate>
#include <QTextDocument>
#include <QTextStream>
#include <QSslSocket>
#include <QAbstractSocket>
#include "smtp.h"
#include"notification.h"
#include <QSettings>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mat->setValidator( new QIntValidator(0, 9999999, this));
    ui->tab_abo->setModel(T.afficher());
       connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
                 connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

                          /*//maps
                           QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                                                QCoreApplication::organizationName(), QCoreApplication::applicationName());

           // ui->webbrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");

*/
}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_7_clicked()

{
    notification N ;
    int mat=ui->mat->text().toInt() ;
       int capacite=ui->capacite->text().toInt() ;
       QString nom=ui->le_nom->text() ;
       QString type=ui->type->text() ;
       QString etat=ui->etat->text() ;
transport T(nom,mat,type,capacite,etat) ;


       bool test=T.ajouter(); //etablir la connexion
    if(test)
      {
          ui->tab_abo->setModel(T.afficher()) ;
          N.notification_ajouter();
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                     QObject::tr("Ajout effectue.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

     }
         else
        QMessageBox::critical(nullptr, QObject::tr("Not okay"),
                     QObject::tr("connection failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}





    void MainWindow::on_pb_supprimer_clicked()
    {notification N ;

           T.setmat(ui->matsup->text().toInt()) ;
            bool test=T.supprimer(T.getmat()) ;
            QMessageBox msgBox ;
            if(test)
            {
                N.notification_supprimer();
                msgBox.setText("Suppression avec succes") ;
                       } else
                    msgBox.setText("suppression echoué");
                    msgBox.exec() ;
        ui->tab_abo->setModel(T.afficher()) ; //refresh maj
    }


void MainWindow::on_pb_supprimer_2_clicked()
{
    notification N ;
        QString nom=ui->le_nom_2->text() ;
        QString type=ui->type_2->text() ;
        QString etat=ui->etat_2->text() ;
        int mat=ui->mat_2->text().toInt() ;
        int capacite=ui->capacite_2->text().toInt() ;


      transport T(nom,mat,type,capacite,etat) ;

      bool test=T.modify() ;

        QMessageBox msgBox;

        if(test)
           {
            N.notification_modifier();
            msgBox.setText("Modification avec succes.");
          ui->tab_abo->setModel(T.afficher()) ;

           }
        else
            msgBox.setText("Echec de Modification.!!!");
            msgBox.exec();
}

void MainWindow::on_recher_clicked()
{
    int mat=(ui->line->text().toInt());
              ui->tab_abo->setModel(T.rechercheT(mat));

}


void MainWindow::on_trier_2_clicked()
{
    transport T ;
    QString nom=ui->fontComboBox->currentText();
        if (ui->croissant->isChecked())
        {
        ui->tab_abo->setModel(T.trierC(nom));
        }
        else if (ui->decroissant->isChecked())
        {
        ui->tab_abo->setModel(T.trier2(nom));
        }

}


void MainWindow::on_pushButton_3_clicked()
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

                          const int rowCount = ui->tab_abo->model()->rowCount();
                          const int columnCount = ui->tab_abo->model()->columnCount();
                          QString TT = QDateTime::currentDateTime().toString();
                          out <<"<html>\n"
                                "<head>\n"
                                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                              << "<title>ERP - COMmANDE LIST<title>\n "
                              << "</head>\n"
                              "<body bgcolor=#ffffff link=#5000A0>\n"
                                 "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                                +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />" //path
                              "<h1 style=\"text-align: center;\"><strong> ****LISTE DES TRANSPORTS **** </strong></h1>"

                              "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                                "</br> </br>";
                          // headers
                          out << "<thead><tr bgcolor=#d6e5ff>";
                          for (int column = 0; column < columnCount; column++)
                              if (!ui->tab_abo->isColumnHidden(column))
                                  out << QString("<th>%1</th>").arg(ui->tab_abo->model()->headerData(column, Qt::Horizontal).toString());
                          out << "</tr></thead>\n";

                          // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++)
                            {
                                  if (!ui->tab_abo->isColumnHidden(column)) {
                                      QString data =ui->tab_abo->model()->data(ui->tab_abo->model()->index(row, column)).toString().simplified();
                                      out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
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

void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("melek.benabdelkarim@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("melek.benabdelkarim@esprit.tn", ui->rcpt->text() , ui->subject->text() ,ui->msg->text(), files );
    else
        smtp->sendMail("melek.benabdelkarim@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->text());
}

void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}
