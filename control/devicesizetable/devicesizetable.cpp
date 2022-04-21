#include "devicesizetable.h"
#include <QHeaderView>
#include <QProgressBar>
#include <QFileInfo>
#include <QDir>

#ifdef Q_OS_WIN
#include "windows.h"
#endif
#define GB (1024 * 1024 * 1024)
#define MB (1024 * 1024)
#define KB (1024)

DeviceSizeTable::DeviceSizeTable(QWidget *parent) : QTableWidget(parent)
{
    bgColor = QColor(255,255,255);

    chunkColor1 = QColor(100, 184, 255);
    chunkColor2 = QColor(24, 189, 155);
    chunkColor3 = QColor(255, 107, 107);

    textColor1 = QColor(10, 10, 10);
    textColor2 = QColor(255, 255, 255);
    textColor3 = QColor(255, 255, 255);

    process = new QProcess(this);
    connect(process,SIGNAL(readyRead()),this,SLOT(readData()));

    this->clear();

    //设置列数和列宽
    this->setColumnCount(5);
    this->setColumnWidth(0, 100);
    this->setColumnWidth(1, 120);
    this->setColumnWidth(2, 120);
    this->setColumnWidth(3, 120);
    this->setColumnWidth(4, 120);

    this->setStyleSheet("QTableWidget::item{padding:0px;}");

    QStringList headText;
    headText  << "盘符" << "已用空间" << "可用空间" << "总空间" << "已用百分比";

    this->setHorizontalHeaderLabels(headText);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->verticalHeader()->setVisible(true);
    //保存头中最后可见的部分是否占用所有可用空间
    this->horizontalHeader()->setStretchLastSection(true);
    //调用对象obj上的成员
    //当控件返回到接收方线程的事件循环时，将调用该插槽。插槽在接收器线程中执行。
    QMetaObject::invokeMethod(this,"load",Qt::QueuedConnection);
}

void DeviceSizeTable::readData()
{
    while(!process->atEnd()){
        QString result = QLatin1String(process->readLine());

        if(result.startsWith("dev/sd")){
            checkSize(result," ");
            QStringList list = result.split(" ");
            emit udiskReceive(list.at(0));
        }
    }
}

void DeviceSizeTable::checkSize(const QString &result, const QString &name)
{
    QString dev,use,free,all;
    int percent = 0;
    QStringList list = result.split(" ");
    int index = 0;

    for (int i = 0; i < list.count(); i++) {
        //从开头和结尾删除了空格的字符串
        QString s = list.at(i).trimmed();
        if(s == ""){
            continue;
        }
        index++;
        if(index == 1){
            dev = s;
        }else if(index == 2){
            all = s;
        }else if(index == 3){
            use = s;
        }else if(index == 4){
            free = s;
        }else if(index == 5){
            percent = s.left(s.length() - 1).toInt();
            break;
        }
    }
    if(name.length() > 0){
        dev = name;
    }
    insertSize(dev,use,free,all,percent);
}

void DeviceSizeTable::insertSize(const QString &name, const QString &use, const QString &free, const QString &all, int percent)
{
    int row = this->rowCount();
    this->insertRow(row);

    QTableWidgetItem *itemname = new QTableWidgetItem(name);
    QTableWidgetItem *itemuse = new QTableWidgetItem(use);
    //文本居中
    itemuse->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem *itemfree = new QTableWidgetItem(free);
    itemfree->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem *itemall = new QTableWidgetItem(all);
    itemall->setTextAlignment(Qt::AlignCenter);

    this->setItem(row,0,itemname);
    this->setItem(row,1,itemuse);
    this->setItem(row,2,itemfree);
    this->setItem(row,3,itemall);

    QProgressBar *bar = new QProgressBar;
    bar->setRange(0,100);
    bar->setValue(percent);

    QString qss = QString("QProgressBar{background:%1;border-width:0px;border-radius:0px;text-align:center;}"
                          "QProgressBar::chunk{border-radius:0px;}").arg(bgColor.name());

    if(percent < 50){
        qss += QString("QProgressBar{color:%1;}QProgressBar::chunk{background:%2;}").arg(textColor1.name()).arg(chunkColor1.name());
    }else if(percent < 90){
        qss += QString("QProgressBar{color:%1;}QProgressBar::chunk{background:%2;}").arg(textColor2.name()).arg(chunkColor2.name());
    }else{
        qss += QString("QProgressBar{color:%1;}QProgressBar::chunk{background:%2;}").arg(textColor3.name()).arg(chunkColor3.name());
    }

    bar->setStyleSheet(qss);
    this->setCellWidget(row,4,bar);
}

void DeviceSizeTable::load()
{
    //清空原有数据
    int row = this->rowCount();
    for (int i = 0; i < row; i++) {
        this->removeRow(0);
    }

#ifdef Q_OS_WIN
    //返回此系统上根目录的列表。
    QFileInfoList list = QDir::drives();
    //foreach: 变量，容器
    foreach(QFileInfo dir,list){
        QString dirName = dir.absolutePath();
        //LPCWSTR 强制转换
        LPCWSTR lpcwstrDriver = (LPCWSTR)dirName.utf16();
        //一个64位的无符号整型值
        ULARGE_INTEGER liFreeBytesAvailable,liTotalBytes,liTotalFreeBytes;

        //检测磁盘空间大小
        if(GetDiskFreeSpaceEx(lpcwstrDriver,&liFreeBytesAvailable,&liTotalBytes,&liTotalFreeBytes)){
            QString use = QString::number((double)(liTotalBytes.QuadPart - liTotalFreeBytes.QuadPart) / GB,'f',1);
            use += "G";
            QString free = QString::number((double)liTotalFreeBytes.QuadPart / GB,'f',1);
            free += "G";
            QString all = QString::number((double)liTotalBytes.QuadPart / GB,'f',1);
            all += "G";
            int percent = 100 - ((double)liTotalFreeBytes.QuadPart / liTotalBytes.QuadPart * 100);
            insertSize(dirName,use,free,all,percent);
        }
    }

#else
    process.start("df -h");
#endif
}
