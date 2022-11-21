#include "connection.h"

Connection::Connection()
{

}

bool Connection::ouvrirconnection()
{bool test=false;

QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("98219966");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}

void Connection::closeConnection(){
    db.close();
}
