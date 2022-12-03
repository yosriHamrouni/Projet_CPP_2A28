#include "transport.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QTextDocument>
#include<QFile>
#include <QDate>
#include <QTextDocument>
#include <QTextStream>
transport::transport()
{
    mat=0;
    nom="" ;
    type="" ;
    capacite=0 ;
    etat="" ;
}
transport::transport(QString nom,int mat,QString type,int capacite ,QString etat  )
{
    this->mat=mat;
    this->nom=nom;
    this->type=type;
    this->capacite=capacite;
    this->etat=etat;
}

bool transport::ajouter()
{
    QSqlQuery query;
      QString mat_string= QString::number(mat);
      QString cap_string= QString::number(capacite);

            query.prepare("INSERT INTO TRANSPORT (MAT,ETAT,CAPACITE,TYPE,NOM)"
                          "VALUES (:MAT,:ETAT,:CAPACITE,:TYPE,:NOM)");
            query.bindValue(":MAT", mat_string);
              query.bindValue(":ETAT", etat);
               query.bindValue(":CAPACITE", cap_string);
                query.bindValue(":TYPE", type);
                 query.bindValue(":NOM", nom);

          return query.exec();




}

QSqlQueryModel * transport::afficher()
{


    QSqlQueryModel* model=new QSqlQueryModel() ;
              model->setQuery("SELECT* FROM TRANSPORT");
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("MAT"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("CAPACITE"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOM"));
              return model ;
}

 bool transport::supprimer(int)
 {

     QSqlQuery query;
        // QString res=QString::number(mat) ;
         query.prepare("Delete from TRANSPORT where MAT= :MAT");
         query.bindValue(0 ,mat) ;
           return query.exec();
 }

 bool transport::modify()
 {QSqlQuery query;
     //  QString res= QString(cin);
       QString MAT_STRING=QString::number(mat);
      QString CAP_STRING= QString::number(capacite);
       query.prepare("UPDATE TRANSPORT SET MAT='"+MAT_STRING+"',ETAT='"+etat+"',CAPACITE='"+CAP_STRING+"',TYPE='"+type+"',NOM='"+nom+"' WHERE MAT='"+MAT_STRING+"'");

        query.bindValue(0,MAT_STRING);
          query.bindValue(1,etat);
          query.bindValue(2, CAP_STRING );
         query.bindValue(3, type);
         query.bindValue(4,nom );

         return query.exec();
 }

 QSqlQueryModel* transport::rechercheT(int mat)
 {
     QSqlQueryModel* model=new QSqlQueryModel() ;
             QString mat_string = QString::number(mat);

            model->setQuery("select * from transport where MAT='"+mat_string+"'");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("MAT"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("CAPACITE"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM"));


            return model ;
 }

 QSqlQueryModel* transport::trierC(QString nom)
 {
         QSqlQueryModel* model = new QSqlQueryModel();

         if (nom=="nom")

         {
         model->setQuery("select * from transport  order by  nom asc");

         model->setHeaderData(0, Qt::Horizontal, QObject::tr("MAT"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("CAPACITE"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM"));

     }
        if (nom=="mat")
     {model->setQuery("select *FROM TRANSPORT ORDER BY MAT ASC");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("MAT"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("CAPACITE"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM"));

     }
     return model;
     }
QSqlQueryModel* transport::trier2(QString nom)
       {

          QSqlQueryModel* model=new QSqlQueryModel() ;

          if (nom=="mat")
       {model->setQuery("select *FROM TRANSPORT ORDER BY MAT DESC");
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("MAT"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("CAPACITE"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
              model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM"));

       }
          if (nom=="nom")

          {
          model->setQuery("select * from transport  order by  nom desc");

          model->setHeaderData(0, Qt::Horizontal, QObject::tr("MAT"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("CAPACITE"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM"));

     }
           return model ;
     }
void transport::CREATION_PDF()
{

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty())
            { fileName.append(".pdf"); }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        QSqlQuery q;
        q.prepare("SELECT * FROM CITOYEN ");
        q.exec();
        QString pdf="<br> <h1  style='color:blue'>LISTE DES TRANSPORTS  <br></h1>\n <br> <table>  <tr>  <th>CIN </th> <th>NOM </th> <th>PRENOM  </th> <th>AGE  </th><th>TEL  </th><th>ADRESS   </th> </tr>" ;
    //br traja ll star oel tr tzidlek colonne th tzidlek ligne h1 asghrr size o akbr size h6 //

        while ( q.next())
            {

            pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toString() +" "" " "</td> </td>" ;
        }
        doc.setHtml(pdf);
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);
}





























int transport::getmat(){return mat;}
QString transport::getnom(){return nom;}
QString transport::gettype(){return type;}
int transport::getcapacite(){return capacite;}
QString transport::getetat(){return etat;}


void transport::setmat(int mat){this->mat=mat;}
void transport::setnom(QString nom){this->nom=nom;}
void transport::settype(QString type ){this->type=type;}
void transport::setcapacite(int capacite ){this->capacite=capacite;}
void transport::setetat(QString etat ){this->etat=etat;}


