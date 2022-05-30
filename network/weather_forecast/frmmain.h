#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWidget>
#include <QXmlStreamReader>

QT_BEGIN_NAMESPACE
namespace Ui {
    class frmMain;
}
QT_END_NAMESPACE

class frmMain : public QWidget {
    Q_OBJECT

public:
    frmMain(QWidget* parent = nullptr);
    ~frmMain();

    QNetworkAccessManager* manager;  //允许应用程序发送网络请求并接收响应
    void getXmlWeatherInfo(QFile& file);

private slots:
    void replyFinished(QNetworkReply* network);
    void on_btnGet_clicked();

private:
    Ui::frmMain* ui;
};
#endif  // FRMMAIN_H
