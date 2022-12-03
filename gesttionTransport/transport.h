#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include "connection.h"


class transport
{
public:
    transport();
    transport(QString,int,QString,int,QString);

    int getmat();
    QString getetat();
    QString gettype();
    QString getnom();
    int getcapacite();

    void setmat(int a);
    void setnom(QString b);
    void settype(QString c);
    void setcapacite(int d );
    void setetat(QString e);



    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modify();
    QSqlQueryModel* rechercheT(int mat) ;
    QSqlQueryModel* trierC(QString nom) ;
    QSqlQueryModel* trier2(QString nom) ;
    void CREATION_PDF() ;

private:

    QString etat;
    QString nom;
    QString type;
    int mat;
    int capacite;

};

#endif // TRANSPORT_H
