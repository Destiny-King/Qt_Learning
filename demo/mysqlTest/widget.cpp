#include "widget.h"

#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

Widget::Widget(QWidget* parent) : QWidget(parent) {
    //得到可以使用的数据库驱动名字的集合
    QStringList list = QSqlDatabase::drivers();
    qDebug() << list;

    // 1、添加一个数据库实例
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    if (db.isValid()) {
        QMessageBox::information(this, "conn", "ok");
    } else {
        QMessageBox::information(this, "conn", "error");
    }
    // 2、初始化连接信息
    db.setHostName("127.0.0.1");  // 本地连接
    db.setPort(3306);             // 如果使用的是默认端口可以不设置
    db.setUserName("root");       // 数据库用户名
    db.setPassword("root");       // 数据库密码
    db.setDatabaseName("mysql");  // 数据库名字
    // 3、连接数据库
    if (db.open()) {
        QMessageBox::information(this, "打开数据库", "数据库打开成功, 可以读写数据了......");
    } else {
        QString msg = "数据库打开失败: " + db.lastError().text();
        QMessageBox::information(this, "打开数据库", msg);
    }
    //查询数据库
    QSqlQuery query;
    // 4、插入数据
    QString sql = "insert into dept values(23,'Romin','深圳')";
    //开启事务
    db.transaction();
    bool flag = query.exec(sql);
    if (flag) {
        //业务流程中每一个写操作完毕之后都要判断其是否成功了，如果所有的写操作都成功了，提交事务，数据库数据被更新
        db.commit();
    } else {
        //业务流程中只要有一个写操作失败了，数据回滚到创建事务时候的状态，保证数据的安全性和完整性
        db.rollback();
    }
    // 5、查询数据表 - dept
    query.exec("select dname,loc from dept");
    //遍历结果集
    while (query.next()) {
        //从当前记录中取出各个字段的值
        //通过 value() 方法将遍历到的当前记录中的每个字段的值取出并打印出来
        qDebug() << query.value(0).toString() << query.value(1).toString() << query.value("dname").toString()
                 << query.value("loc").toString();
    }
    // 6、关闭数据库
    db.close();
}

Widget::~Widget() {}
