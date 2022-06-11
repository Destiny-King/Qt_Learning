#include "jsonmain.h"

#include <QDomDocument>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>
#include <QNetworkReply>
#include <QXmlStreamReader>

#include "ui_jsonmain.h"

JsonMain::JsonMain(QWidget* parent) : QWidget(parent), ui(new Ui::JsonMain) {
    ui->setupUi(this);

    this->setWindowTitle("北京时间");           //设置标题
    manager = new QNetworkAccessManager(this);  //实例化QNetworkAccessManager
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replayFinished(QNetworkReply*)));
}

JsonMain::~JsonMain() { delete ui; }

//解析时间
void JsonMain::getInternetTime(QByteArray& byte_array) {
    //解析数据
    QString time;
    QJsonParseError json_error;
    //将json解析为UTF-8编码的json文档
    QJsonDocument parse_document = QJsonDocument::fromJson(byte_array, &json_error);
    //没有错误
    if (json_error.error != QJsonParseError::NoError) {
        return;
    }
    // 1.解析状态,判断是否解析成功
    if (parse_document.isObject()) {
        QJsonObject obj = parse_document.object();  //获取文档对象
        if (obj.contains("success")) {
            //返回一个包含值引用键QJsonValue
            QJsonValue success = obj.take("success");  //移除success键
            //如果值包含一个字符串返回true
            if (success.isString()) {
                //将值转为字符串
                QString flag = success.toString();
                //判断返回的状态值
                if (flag != "1") {
                    QMessageBox::warning(this, tr("错误信息提示"), tr("时间获取错误,请检查网络是否畅通!"),
                                         QMessageBox::Ok);
                    return;
                }
            }
        }
        // 2.解析结果
        //如果对象包含指定的标记
        if (obj.contains("result")) {
            //返回一个包含值引用键QJsonValue
            QJsonValue datetime = obj.take("result");  //移除result键
            //如果值包含一个对象返回true
            if (datetime.isObject()) {
                //将值转为字符串
                QJsonObject obj1 = datetime.toObject();
                //解析时间
                if (obj1.contains("datetime_2")) {
                    //返回一个包含值引用键QJsonValue
                    QJsonValue datetime = obj1.take("datetime_2");  //移除datetime_2键
                    //如果值包含一个字符串返回true
                    if (datetime.isString()) {
                        //将值转为字符串
                        time += datetime.toString() + " ";
                    }
                }
                //解析星期
                if (obj1.contains("week_2")) {
                    QJsonValue week = obj1.take("week_2");
                    if (week.isString()) {
                        //将值转换成字符串
                        time += week.toString();
                    }
                }
            }
        }
    }
    ui->lab_Display->setText(time);
}

//回复完成
void JsonMain::replayFinished(QNetworkReply* network) {
    //无错误返回
    if (network->error() == QNetworkReply::NoError) {
        //读取所有数据
        QByteArray byte_array = network->readAll();
        getInternetTime(byte_array);
    } else {
        QMessageBox::warning(this, tr("错误信息提示"), tr("失败，请检查网络"), QMessageBox::Ok);
    }
    //删除reply
    network->deleteLater();
}

//获取网络时间
void JsonMain::on_btn_Get_clicked() {
    //获取北京时间接口
    QString text = "http://api.k780.com:88/?app=life.time"
                   "&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json";
    manager->get(QNetworkRequest(QUrl(text)));  //获取网络数据
}
