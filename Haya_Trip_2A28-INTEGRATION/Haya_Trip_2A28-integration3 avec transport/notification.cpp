#include "notification.h"
#include <QSystemTrayIcon>
#include<QString>
notification::notification()
{

}

void notification::notification_ajouter()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:Desktop\33\add"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des transport ","nouveau moyen transport est ajouté ",QSystemTrayIcon::Information,15000);
}
void notification::notification_supprimer(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

notifyIcon->setIcon(QIcon("D:/iconP/supp"));
notifyIcon->show();
    notifyIcon->showMessage("Gestion des  transport ","Un  moyen transport est supprimé",QSystemTrayIcon::Information,15000);
}
void notification::notification_modifier(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

notifyIcon->setIcon(QIcon("D:/iconP/modif"));

notifyIcon->show();
    notifyIcon->showMessage("Gestion des  transport ","nouveau  moyen transport est modifié",QSystemTrayIcon::Information,15000);

}
