#ifndef CONNECT_H
#define CONNECT_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnect(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("first");
    if(!db.open()){
        QMessageBox::critical(0,"cannot open database","unable to establish a database connect.",QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    query.exec("craete table student(id int primary key,name varchar(20))");
    query.exec("insert into student values(1,'first')");
    query.exec("insert into student values(2,'second')");
    query.exec("insert into student values(3,'third')");
    query.exec("insert into student values(4,'fourth')");
    query.exec("insert into student values(5,'fifth')");

    return true;
}

#endif // CONNECT_H
