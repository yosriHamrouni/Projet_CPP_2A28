#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "QWidget"
#include<QObject>


class Connection
{ // Q_OBJECT
    QSqlDatabase db ;
public:
    Connection();
    bool createconnect();
    void closeconnect();
};

#endif // CONNECTION_H
