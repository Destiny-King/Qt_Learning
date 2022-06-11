#include "frmmain.h"

#include <QDomDocument>
#include <QMessageBox>
#include <QNetworkRequest>

#include "ui_frmmain.h"

frmMain::frmMain(QWidget* parent) : QWidget(parent), ui(new Ui::frmMain) {
    ui->setupUi(this);
    this->setWindowTitle("百度天气预报");  //设置标题
    // 1.实例化QNetworkAccessManager
    manager = new QNetworkAccessManager(this);
    // 2.关联finished信号
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    ui->lineEdit->setText("shenzhen");  //设置文本
}

frmMain::~frmMain() { delete ui; }

//解析XML格式的天气预报
void frmMain::getXmlWeatherInfo(QFile& file) {
    QDomDocument document;
    QString info;

    if (!file.exists()) {
        QMessageBox::warning(this, tr("错误信息提示"), tr("文件不存在"), QMessageBox::Ok);
        return;
    }

    // 1.检测XML文件格式,从字节数组数据解析XML文档
    if (!document.setContent(&file)) {
        QMessageBox::warning(this, tr("错误信息提示"), tr("XML文件读取错误"), QMessageBox::Ok);
        return;
    }
    // 2.判断是否有节点
    if (document.isNull()) {
        QMessageBox::warning(this, tr("错误信息提示"), tr("XML格式错误"), QMessageBox::Ok);
        return;
    }
    // 3.返回XML文档的根元素。最外层<></>元素
    QDomElement root = document.documentElement();

    // 4.获取元素子节点列表
    QDomNodeList list = root.childNodes();
    // 5.判断天气预报是否获取成功
    QDomNode domNode = list.item(0);            //取出存放状态信息子节点
    QDomElement element = domNode.toElement();  //得到子节点的元素对象
    if (element.tagName() != "status") {
        QMessageBox::warning(this, tr("错误信息提示"), tr("标签名错误，请检查城市名称是否正确"), QMessageBox::Ok);
        return;
    }
    // 5.获取城市的名称
    domNode = list.item(1);         //取出存放城市名称子节点
    element = domNode.toElement();  //得到子节点的元素对象
    if (element.text().isEmpty()) {
        QMessageBox::warning(this, tr("错误信息提示"), tr("元素文本为空，请检查城市名称是否正确"), QMessageBox::Ok);
        return;
    }
    info += "城市名称：" + element.text() + "\n" + "\n";  //得到城市名称
    // 5.循环取出每一个子节点进行解析
    domNode = list.item(2);         //取出存放天气预报信息子节点
    element = domNode.toElement();  //得到子节点的元素对象
    list = element.childNodes();    //得到天气预报列表
    //循环解析子节点
    for (int i = 0; i < list.count(); ++i) {
        domNode = list.item(i);
        element = domNode.toElement();
        QDomNodeList list2 = element.childNodes();
        for (int j = 0; j < list2.count(); ++j) {
            QDomNode domNode2 = list2.item(j);
            QDomElement element2 = domNode2.toElement();
            if (element2.tagName() == "date") {
                info += "日期：" + element2.text() + "\n";
            } else if (element2.tagName() == "weather") {
                info += "天气：" + element2.text() + "\n";
            } else if (element2.tagName() == "wind") {
                info += "风量：" + element2.text() + "\n";
            } else if (element2.tagName() == "temperature") {
                info += "温度：" + element2.text() + "\n" + "\n";
            }
        }
    }
    ui->plainTextEdit->appendPlainText(info);  //在文本编辑的末尾追加一个带有文本的新段落
}

//回复完成
void frmMain::replyFinished(QNetworkReply* network) {
    //无错误返回
    if (network->error() == QNetworkReply::NoError) {
        //读取所有数据
        // QByteArray byte_array = network->readAll();
        // getXmlWeatherInfo(byte_array);  //将数据传递给getXmlWeatherInfo()函数
    } else {
        QMessageBox::warning(this, tr("错误信息提示"), tr("失败,请检查网络是否正常!"), QMessageBox::Ok);
    }
    //删除reply
    network->deleteLater();
}

//获取信息
void frmMain::on_btnGet_clicked() {
    QString str = ui->lineEdit->text();  //接收输入框的文本
    if (str.isEmpty()) {
        QMessageBox::warning(this, tr("错误信息提示"), tr("输入数据为空"), QMessageBox::Ok);
        return;
    }
    //保存接口地址
    /*QString text = "https://api.map.baidu.com/weather/v1/?district_id=";
    text += str;                                                   //连接字符串位置
    text += "&data_type=all&ak=Kk5z48X9uIzZYb7pK6o4VuR4kb5PImuc";  //连接字符串密钥
    ui->plainTextEdit->clear();                                    //清空文本框
    manager->get(QNetworkRequest(QUrl(text)));                     //获取网页数据,发送请求*/
    QFile file("shenzhen.xml");
    getXmlWeatherInfo(file);
}
