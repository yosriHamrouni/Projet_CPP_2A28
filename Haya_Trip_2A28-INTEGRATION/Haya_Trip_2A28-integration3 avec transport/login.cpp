#include "login.h"

#include<QMessageBox>
#include<qmessagebox.h>
#include "mainwindow.h"
#include"ui_mainwindow.h"




    login::login()
    {
 username="";password="";
    }
        login::login(QString usr,QString pwd  )
    {
            this->username=usr; this->password=pwd;


        }

