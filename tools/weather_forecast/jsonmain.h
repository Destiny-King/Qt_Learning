#ifndef JSONMAIN_H
#define JSONMAIN_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWidget>

namespace Ui {
    class JsonMain;
}

class JsonMain : public QWidget {
    Q_OBJECT

public:
    explicit JsonMain(QWidget* parent = nullptr);
    ~JsonMain();

    QNetworkAccessManager* manager;
    void getInternetTime(QByteArray& byte_array);

private slots:
    void replayFinished(QNetworkReply* network);
    void on_btn_Get_clicked();

private:
    Ui::JsonMain* ui;
};

#endif  // JSONMAIN_H
