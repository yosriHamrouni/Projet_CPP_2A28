#ifndef LOGIN_H
#define LOGIN_H





#include <QDialog>




class login
{


public:

      login();

     login(QString usr,QString pwd  );



    ~login();







private:
  QString username,password;
};

#endif // LOGIN_H



















