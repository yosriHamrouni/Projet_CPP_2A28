#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include "connection.h"
#include "QDebug"
#include <QRegExpValidator>
#include "mainwindow.h"


#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QVBoxLayout>

#include <QMenu>
#include <QAction>
#include <QFileDialog>







MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->le_idc->setValidator(new QIntValidator(0, 9999999, this));

   /* QRegExp rxEmail(EMAIL_RX);
    QRegExpValidator *valiEmail = new QRegExpValidator(rxEmail, this);

*/
ui->le_email->setValidator(new QRegExpValidator(  QRegExp("[a-z]{1,19}@[a-z]{1,9}\\.[a-z]{1,4}")  ));

    ui->tab_clients->setModel(C.afficher());
      ui->verticalLayout->addWidget(C.stat());

      //CAMERA


      mCamera= new QCamera(this);
     mCameraViewfinder= new QCameraViewfinder(this);
     mCameraImageCapture = new QCameraImageCapture(mCamera, this);
     mLayout= new QVBoxLayout;

     mOptionsMenu = new QMenu("options", this);



     mEncenderAction = new QAction("Switchon",this);
     mApagarAction = new QAction("apagar",this);
     mCapturarAction= new QAction("Capture",this);

     mOptionsMenu->addActions({mEncenderAction,mApagarAction, mCapturarAction});
     ui->Options__pushButton->setMenu(mOptionsMenu);
     mCamera->setViewfinder(mCameraViewfinder);
     mLayout->addWidget(mCameraViewfinder);

     mLayout->setMargin(0);


     ui->scrollArea->setLayout(mLayout);

     connect(mEncenderAction,&QAction::triggered ,[&](){
         mCamera->start();
     });



     connect(mApagarAction,&QAction::triggered ,[&](){
         mCamera->stop();

     });



     connect(mCapturarAction, &QAction::triggered , [&](){


          auto filename=  QFileDialog::getSaveFileName(this,"Capture", "/","Images(*.jpg;*.jpeg)" );

          if(filename.isEmpty()){
              return ;

          };



            mCameraImageCapture->setCaptureDestination(
                        QCameraImageCapture::CaptureToFile );


            QImageEncoderSettings imageEncoderSettings;
            imageEncoderSettings.setCodec("image/jpeg");
            imageEncoderSettings.setResolution(1600,1200);
            mCameraImageCapture->setEncodingSettings(imageEncoderSettings);

            mCamera->setCaptureMode(QCamera :: CaptureStillImage);
            mCamera->start();
            mCamera->searchAndLock();
            mCameraImageCapture->capture(filename);
            mCamera->unlock();







     });








}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
        //int idc=ui->le_idc
              int idc=ui->le_idc->text().toInt();

                QString nom=ui->le_nom->text();
                QString prenom=ui->le_prenom->text();
                QString tel=ui->le_tel->text();
                QString email=ui->le_email->text();
                QString  rdv=ui->le_rdv->text();





                Client C(idc,nom,prenom,tel,email,rdv);




                bool test=C.ajouter();
                if (test){
                    QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("ajout effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
                    ui->tab_clients->setModel(C.afficher());

            }
                else
                    QMessageBox::critical(nullptr, QObject::tr("not OK"),
                                QObject::tr("ajout non effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);




}

void MainWindow::on_pb_supprimer_clicked()
{



    Client C;
    C.setid(ui->le_id_supp->text().toInt());

   bool test=C.supprimer(C.getid());

   QMessageBox msgBox;
   if(test)
   {msgBox.setText("Suppression avec succes.");
   ui->tab_clients->setModel(C.afficher());}
   else
   msgBox.setText("Echec de suppression");
   msgBox.exec();

}

/*void MainWindow::on_comboBox_supp_activated(const QString &idc)
{
  //  ui->comboBox_supp->addItems()
}*/

void MainWindow::on_pb_update_clicked()
{

    int idc=ui->le__edit_idc->text().toInt();

      QString nom=ui->le_edit_name->text();
      QString prenom=ui->le_edit_prenom->text();
      QString tel=ui->le_edit_tel->text();
      QString email=ui->le_edit_email->text();


     QString rdv=ui->le_edit_rdv->text();


      Client C(idc,nom,prenom,tel,email,rdv);




      bool test=C.update();
      if (test){
          QMessageBox::information(nullptr, QObject::tr("OK"),
                      QObject::tr("modification effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_clients->setModel(C.afficher());

             }
      else
          QMessageBox::critical(nullptr, QObject::tr("not OK"),
                      QObject::tr("modif non effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_tab_clients_activated(const QModelIndex &index)

{




int idc=ui->tab_clients->model()->data(index).toInt();

    QString id_string = QString::number(idc) ;





   /* if (!test.createconnect()){

        qDebug()<<"Failed to open dtabase";

        return;
           }*/


        QSqlQuery qry ;
        qry.prepare("SELECT* FROM CLIENT WHERE ID_CLIENT='"+id_string+"' or NOM_CLIENT='"+id_string+"' or PRENOM_CLIENT='"+id_string+"' or TEL_CLIENT='"+id_string+"' or EMAIL_CLIENT='"+id_string+"'   " ) ;
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->le_id_supp->setText(qry.value(0).toString()) ;
                ui->le__edit_idc->setText(qry.value(0).toString()) ;
                ui->le_edit_name->setText(qry.value(1).toString()) ;
                ui->le_edit_prenom->setText(qry.value(2).toString()) ;
                ui->le_edit_tel->setText(qry.value(3).toString()) ;
                   ui->le_edit_email->setText(qry.value(4).toString()) ;

            }
        }




}

void MainWindow::on_pb_find_clicked()
{

    QString search=ui->le_id_supp->text();
    ui->tab_clients->setModel(C.search(search));


/*
    Client C;
    C.setid(ui->le_id_supp->text().toInt());




    bool test=C.search();
    if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("client trouvé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_clients->setModel(C.afficher());

           }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("client non trouvé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);*/
}

void MainWindow::on_pushButton_clicked()
{
    Client C;

     ui->tab_clients->setModel(C.tri());
     bool test=C.tri();
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

void MainWindow::on_pb_genererPdf_clicked()
{
        Client C;
  bool test= C.genererPDFact();
   if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("PDF Géneré. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
