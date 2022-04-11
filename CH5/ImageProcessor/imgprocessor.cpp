#include "imgprocessor.h"
#include <QApplication>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QColor>
#include <QColorDialog>
#include <QTextList>

ImgProcessor::ImgProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    //设置窗体标题
    setWindowTitle(tr("Easy Word"));

    showWidget = new ShowWidget(this);
    setCentralWidget(showWidget);

    //在工具栏上嵌入控件
    //设置字体
    fontLabel1 = new QLabel(tr("字体:"));
    fontComboBox = new QFontComboBox;
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);

    //设置字号
    fontlabel2 = new QLabel(tr("字号:"));
    sizeComboBox = new QComboBox;
    QFontDatabase db;
    foreach(int size,db.standardSizes())
        sizeComboBox->addItem(QString::number(size));

    //设置文字加粗
    boldBtn = new QToolButton;
    boldBtn->setIcon(QIcon(":/images/bold.png"));
    boldBtn->setCheckable(true);

    //设置文字斜体
    italicBtn = new QToolButton;
    italicBtn->setIcon(QIcon(":/images/italic.png"));
    italicBtn->setCheckable(true);

    //设置文字加下划线
    underlineBtn =new QToolButton;
    underlineBtn->setIcon(QIcon(":/images/underline.png"));
    underlineBtn->setCheckable(true);

    //设置文字颜色
    colorBtn =new QToolButton;
    colorBtn->setIcon(QIcon(":/images/color.png"));
    colorBtn->setCheckable(true);

    //排序
    listLabel = new QLabel(tr("排序"));
    listComboBox = new QComboBox();
    listComboBox->addItem("Standard");
    listComboBox->addItem("QTextListFormat::ListDisc");
    listComboBox->addItem("QTextListFormat::ListCircle");
    listComboBox->addItem("QTextListFormat::ListSquare");
    listComboBox->addItem("QTextListFormat::ListDecimal");
    listComboBox->addItem("QTextListFormat::ListLowerAlpha");
    listComboBox->addItem("QTextListFormat::ListUpperAlpha");
    listComboBox->addItem("QTextListFormat::ListLowerRoman");
    listComboBox->addItem("QTextListFormat::ListUpperRoman");

    //创建动作、菜单、工具栏的函数
    createActions();
    createMenus();
    createToolBars();

    if(img.load(":/images/image.png")){
        //在imagelabel对象中放置图像
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    }

    //字体设置项
    connect(fontComboBox,SIGNAL(activated(QString)),this,SLOT(ShowFontComboBox(QString)));
    connect(sizeComboBox,SIGNAL(activated(QString)),this,SLOT(ShowSizeSpinBox(QString)));
    connect(boldBtn,SIGNAL(clicked()),this,SLOT(ShowBoldBtn()));
    connect(italicBtn,SIGNAL(clicked()),this,SLOT(ShowItalicBtn()));
    connect(underlineBtn,SIGNAL(clicked()),this,SLOT(ShowUnderlineBtn()));
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(ShowColorBtn()));
    connect(showWidget->text,SIGNAL(currentCharFormatChanged(QtextCharFormat&)),this,SLOT(ShowCurrentFormatChanged(QTextCharFormat&)));

    connect(listComboBox,SIGNAL(activated(int)),this,SLOT(ShowList(int)));
    connect(showWidget->text->document(),SIGNAL(undoAvailable(bool)),undoAction,SLOT(setEnabled(bool)));
    connect(showWidget->text->document(),SIGNAL(redoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(showWidget->text,SIGNAL(cursorPositionChanged()),this,SLOT(ShowCursorPositionChanged()));
}

ImgProcessor::~ImgProcessor()
{
}

void ImgProcessor::createActions()
{
    //"打开"动作
    openFileAction = new QAction(QIcon(":/images/open.png"),tr("打开"),this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(tr("打开一个文件"));
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(ShowOpenFile()));

    //"新建"动作
    NewFileAction = new QAction(QIcon(":/images/new.png"),tr("新建"),this);
    NewFileAction->setShortcut(tr("Ctrl+N"));
    NewFileAction->setStatusTip(tr("新建一个文件"));
    connect(NewFileAction,SIGNAL(triggered()),this,SLOT(ShowNewFile()));

    //"退出"动作
    exitAction =new QAction(tr("退出"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出程序"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    //"复制"动作
    copyAction =new QAction(QIcon(":/images/copy.png"),tr("复制"),this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("复制文件"));
    connect(copyAction,SIGNAL(triggered()),showWidget->text,SLOT(copy()));

    //"剪切"动作
    cutAction =new QAction(QIcon(":/images/cut.png"),tr("剪切"),this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("剪切文件"));
    connect(cutAction,SIGNAL(triggered()),showWidget->text,SLOT(cut()));

    //"粘贴"动作
    pasteAction =new QAction(QIcon(":/images/paste.png"),tr("粘贴"),this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("粘贴文件"));
    connect(pasteAction,SIGNAL(triggered()),showWidget->text,SLOT(paste()));

    //"关于"动作
    aboutAction = new QAction(tr("关于"),this);
    connect(aboutAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));

    //"打印文本"动作
    PrintTextAction =new QAction(QIcon(":/images/printText.png"),tr("打印文本"), this);
    PrintTextAction->setStatusTip(tr("打印一个文本"));
    connect(PrintTextAction,SIGNAL(triggered()),this,SLOT(ShowPrintText()));

    //"打印图像"动作
    PrintImageAction =new QAction(QIcon(":/images/printImage.png"),tr("打印图像"), this);
    PrintImageAction->setStatusTip(tr("打印一幅图像"));
    connect(PrintImageAction,SIGNAL(triggered()),this,SLOT(ShowPrintImage()));

    //"放大"动作
    zoomInAction =new QAction(QIcon(":/images/zoomin.png"),tr("放大"),this);
    zoomInAction->setStatusTip(tr("放大一张图片"));
    connect(zoomInAction,SIGNAL(triggered()),this,SLOT(ShowZoomIn()));

    //"缩小"动作
    zoomOutAction =new QAction(QIcon(":/images/zoomout.png"),tr("缩小"),this);
    zoomOutAction->setStatusTip(tr("缩小一张图片"));
    connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(ShowZoomOut()));

    //实现图像旋转的动作（Action）
    //旋转90°
    rotate90Action = new QAction(QIcon(":/images/rotate90.png"),tr("旋转90°"),this);
    rotate90Action->setStatusTip(tr("将一幅图旋转90°"));
    connect(rotate90Action,SIGNAL(triggered()),this,SLOT(ShowRotate90()));

    //旋转180°
    rotate180Action =new QAction(QIcon(":/images/rotate180.png"),tr("旋转180°"), this);
    rotate180Action->setStatusTip(tr("将一幅图旋转180°"));
    connect(rotate180Action,SIGNAL(triggered()),this,SLOT(ShowRotate180()));

    //旋转270°
    rotate270Action =new QAction(QIcon(":/images/rotate270.png"),tr("旋转270°"), this);
    rotate270Action->setStatusTip(tr("将一幅图旋转270°"));
    connect(rotate270Action,SIGNAL(triggered()),this,SLOT(ShowRotate270()));

    //实现图像镜像的动作（Action）
    //纵向镜像
    mirrorVerticalAction =new QAction(tr ("纵向镜像"),this);
    mirrorVerticalAction->setStatusTip(tr("对一张图作纵向镜像"));
    connect(mirrorVerticalAction,SIGNAL(triggered()),this,SLOT(ShowMirrorVertical()));

    //横向镜像
    mirrorHorizontalAction =new QAction(tr("横向镜像"),this);
    mirrorHorizontalAction->setStatusTip(tr("对一张图作横向镜像"));
    connect(mirrorHorizontalAction,SIGNAL(triggered()),this,SLOT(ShowMirrorHorizontal()));

    //排序：左对齐、右对齐、居中和两端对齐
    actGrp = new QActionGroup(this);
    leftAction = new QAction(QIcon(":/images/left.png"),tr("左对齐"),this);
    leftAction->setCheckable(true);

    rightAction =new QAction(QIcon(":/images/right.png"),"右对齐",actGrp);
    rightAction->setCheckable(true);

    centerAction =new QAction(QIcon(":/images/center.png"),"居中",actGrp);
    centerAction->setCheckable(true);

    justifyAction =new QAction(QIcon(":/images/justify.png"),"两端对齐",actGrp);
    justifyAction->setCheckable(true);

    connect(actGrp,SIGNAL(triggered(QAction*)),this,SLOT(ShowAlignment(QAction*)));

    //实现撤销和重做的动作（Action）
    //撤销和重做
    undoAction = new QAction(QIcon(":/images/undo.png"),tr("撤销"),this);
    connect(undoAction,SIGNAL(triggered()),showWidget->text,SLOT(undo()));

    redoAction = new QAction(QIcon(":/images/redo.png"),tr("重做"),this);
    connect(redoAction,SIGNAL(triggered()),showWidget->text,SLOT(redo()));
}

void ImgProcessor::createMenus()
{
    //文件菜单
    fileMenu =menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(NewFileAction);
    fileMenu->addAction(PrintTextAction);
    fileMenu->addAction(PrintImageAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //缩放菜单
    zoomMenu = menuBar()->addMenu(tr("缩放"));
    zoomMenu->addAction(copyAction);
    zoomMenu->addAction(cutAction);
    zoomMenu->addAction(pasteAction);
    zoomMenu->addAction(aboutAction);
    zoomMenu->addSeparator();
    zoomMenu->addAction(zoomInAction);
    zoomMenu->addAction(zoomOutAction);

    //旋转菜单
    rotateMenu =menuBar()->addMenu(tr("旋转"));
    rotateMenu->addAction(rotate90Action);
    rotateMenu->addAction(rotate180Action);
    rotateMenu->addAction(rotate270Action);

    //镜像菜单
    mirrorMenu =menuBar()->addMenu(tr("镜像"));
    mirrorMenu->addAction(mirrorVerticalAction);
    mirrorMenu->addAction(mirrorHorizontalAction);
}

void ImgProcessor::createToolBars()
{
    //文件工具条
    fileTool = addToolBar("File");
    fileTool->addAction(openFileAction);
    fileTool->addAction(NewFileAction);
    fileTool->addAction(PrintTextAction);
    fileTool->addAction(PrintImageAction);

    //编辑工具条
    zoomTool =addToolBar("Edit");
    zoomTool->addAction(copyAction);
    zoomTool->addAction(cutAction);
    zoomTool->addAction(pasteAction);
    zoomTool->addSeparator();
    zoomTool->addAction(zoomInAction);
    zoomTool->addAction(zoomOutAction);

    //旋转工具条
    rotateTool =addToolBar("rotate");
    rotateTool->addAction(rotate90Action);
    rotateTool->addAction(rotate180Action);
    rotateTool->addAction(rotate270Action);

    //撤销和重做工具条
    doToolBar = addToolBar("doEdit");
    doToolBar->addAction(undoAction);
    doToolBar->addAction(redoAction);

    //字体工具条
    fontToolBar = addToolBar("Font");
    fontToolBar->addWidget(fontLabel1);
    fontToolBar->addWidget(fontComboBox);
    fontToolBar->addWidget(fontlabel2);
    fontToolBar->addWidget(sizeComboBox);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(boldBtn);
    fontToolBar->addWidget(italicBtn);
    fontToolBar->addWidget(underlineBtn);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(colorBtn);

    //排序工具条
    listToolBar = addToolBar("list");
    listToolBar->addWidget(listLabel);
    listToolBar->addWidget(listComboBox);
    listToolBar->addSeparator();
    listToolBar->addActions(actGrp->actions());
}

void ImgProcessor::loadFile(QString fileName)
{
    printf("file name: %s\n",fileName.data());
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream textStream(&file);
        while(!textStream.atEnd()){
            showWidget->text->append(textStream.readLine());
            printf("read line\n");
        }
        printf("end\n");
    }
}

void ImgProcessor::mergeFormat(QTextCharFormat format)
{
    //获得编辑框内的光标
    QTextCursor cursor = showWidget->text->textCursor();
    if(!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    showWidget->text->mergeCurrentCharFormat(format);
}

void ImgProcessor::ShowNewFile()
{
    ImgProcessor *newImgProcessor = new ImgProcessor;
    newImgProcessor->show();
}

void ImgProcessor::ShowOpenFile()
{
    fileName = QFileDialog::getOpenFileName(this,"打开");
    if(!fileName.isEmpty()){
        if(showWidget->text->document()->isEmpty()){
            loadFile(fileName);
        }else{
            ImgProcessor *newImgProcessor = new ImgProcessor;
            newImgProcessor->show();
            newImgProcessor->loadFile(fileName);
        }
    }
}

void ImgProcessor::ShowPrintText()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec()){
        QTextDocument *doc = showWidget->text->document();
        doc->print(&printer);
    }
}

void ImgProcessor::ShowPrintImage()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec()){
        QPainter painter(&printer);
        //获得QPainter对象的视图矩形区域
        QRect rect = painter.viewport();
        //获得图像大小
        QSize size = img.size();
        //按照图形的比例大小重新设置视图矩形区域
        size.scale(rect.size(),Qt::KeepAspectRatio);
        painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
        //设置QPainter窗口大小为图像的大小
        painter.setWindow(img.rect());
        //打印图像
        painter.drawImage(0,0,img);
    }
}

void ImgProcessor::ShowZoomIn()
{
    //有效性判断
    if(img.isNull())
        return;
    //声明一个QMatrix类的实例
    QMatrix matrix;
    matrix.scale(2,2);
    img = img.transformed(matrix);
    //重新设置显示图形
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowZoomOut()
{
    //有效性判断
    if(img.isNull())
        return;
    //声明一个QMatrix类的实例
    QMatrix matrix;
    matrix.scale(0.5,0.5);
    img = img.transformed(matrix);
    //重新设置显示图形
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowRotate90()
{
    //有效性判断
    if(img.isNull())
        return;
    //声明一个QMatrix类的实例
    QMatrix matrix;
    matrix.rotate(90);
    img = img.transformed(matrix);
    //重新设置显示图形
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowRotate180()
{
    //有效性判断
    if(img.isNull())
        return;
    //声明一个QMatrix类的实例
    QMatrix matrix;
    matrix.rotate(180);
    img = img.transformed(matrix);
    //重新设置显示图形
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowRotate270()
{
    //有效性判断
    if(img.isNull())
        return;
    //声明一个QMatrix类的实例
    QMatrix matrix;
    matrix.rotate(270);
    img = img.transformed(matrix);
    //重新设置显示图形
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowMirrorVertical()
{
    //有效性判断
    if(img.isNull())
        return;
    img = img.mirrored(false,true);
    //重新设置显示图形
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowMirrorHorizontal()
{
    //有效性判断
    if(img.isNull())
        return;
    img = img.mirrored(true,false);
    //重新设置显示图形
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

//设置选定文字字体
void ImgProcessor::ShowFontComboBox(QString comboStr)
{
    //创建一个QTextCharFormat对象
    QTextCharFormat frm;
    //选择的字体名称设置给QTextCharFormat对象
    frm.setFontFamily(comboStr);
    //将新的格式应用到光标选区内的字符
    mergeFormat(frm);
}

//设置字号
void ImgProcessor::ShowSizeSpinBox(QString spinValue)
{
    QTextCharFormat frm;
    frm.setFontPointSize(spinValue.toDouble());
    showWidget->text->mergeCurrentCharFormat(frm);
}

//设置文字加粗
void ImgProcessor::ShowBoldBtn()
{
    QTextCharFormat frm;
    frm.setFontWeight(boldBtn->isChecked()?QFont::Bold:QFont::Normal);
    showWidget->text->mergeCurrentCharFormat(frm);
}

void ImgProcessor::ShowItalicBtn()
{
    QTextCharFormat frm;
    frm.setFontItalic(italicBtn->isChecked());
    showWidget->text->mergeCurrentCharFormat(frm);
}

//设置文字下划线
void ImgProcessor::ShowUnderlineBtn()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(underlineBtn->isChecked());
    showWidget->text->mergeCurrentCharFormat(fmt);
}

//设置文字颜色
void ImgProcessor::ShowColorBtn()
{
    QColor color = QColorDialog::getColor(Qt::white,this);
    if(color.isValid()){
        QTextCharFormat fmt;
        fmt.setForeground(color);
        showWidget->text->mergeCurrentCharFormat(fmt);
    }
}

//设置字符格式
void ImgProcessor::ShowCurrentFormatChanged(const QTextCharFormat &fmt)
{
    fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.fontFamily()));
    sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(fmt.fontPointSize())));
    boldBtn->setChecked(fmt.font().bold());
    italicBtn->setChecked(fmt.font().italic());
    underlineBtn->setChecked(fmt.font().underline());
}

void ImgProcessor::ShowList(int index)
{
    QTextCursor cursor = showWidget->text->textCursor();

    if(index != 0){
        QTextListFormat::Style style = QTextListFormat::ListDisc;
        switch (index) {
            default:
            case 1:
                style = QTextListFormat::ListDisc;
                break;
            case 2:
                style = QTextListFormat::ListCircle;
                break;
            case 3:
                style = QTextListFormat::ListSquare;
                break;
            case 4:
                style = QTextListFormat::ListDecimal;
                break;
            case 5:
                style = QTextListFormat::ListLowerAlpha;
                break;
            case 6:
                style = QTextListFormat::ListUpperAlpha;
                break;
            case 7:
                style = QTextListFormat::ListLowerRoman;
                break;
            case 8:
                style = QTextListFormat::ListUpperRoman;
                break;
        }
        //设置缩进值
        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();
        QTextListFormat listFmt;

        if(cursor.currentList()){
            listFmt = cursor.currentList()->format();
        }
        else{
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);

        cursor.endEditBlock();
    }else{
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

//实现段落对齐
void ImgProcessor::ShowAlignment(QAction *act)
{
    if(act == leftAction)
        showWidget->text->setAlignment(Qt::AlignLeft);
    if(act == rightAction)
        showWidget->text->setAlignment(Qt::AlignRight);
    if(act == centerAction)
        showWidget->text->setAlignment(Qt::AlignCenter);
    if(act == justifyAction)
        showWidget->text->setAlignment(Qt::AlignJustify);
}

//响应文本中光标位置
void ImgProcessor::ShowCursorPositionChanged()
{
    if(showWidget->text->alignment() == Qt::AlignLeft)
        leftAction->setChecked(true);
    if(showWidget->text->alignment() == Qt::AlignRight)
        rightAction->setChecked(true);
    if(showWidget->text->alignment() == Qt::AlignCenter)
        centerAction->setChecked(true);
    if(showWidget->text->alignment() == Qt::AlignJustify)
        justifyAction->setChecked(true);
}

