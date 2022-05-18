#ifndef IMGPROCESSOR_H
#define IMGPROCESSOR_H

#include "showwidget.h"
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QFontComboBox>
#include <QComboBox>
#include <QToolButton>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QSpinBox>
#include <QToolBar>
#include <QTextCharFormat>

class ImgProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImgProcessor(QWidget *parent = 0);
    ~ImgProcessor();

    //创建动作
    void createActions();
    //创建菜单
    void createMenus();
    //创建工具栏
    void createToolBars();

    void loadFile(QString fileName);
    void mergeFormat(QTextCharFormat);

private:
    //各项菜单栏
    //文件菜单
    QMenu *fileMenu;
    //编辑菜单
    QMenu *zoomMenu;
    //旋转菜单
    QMenu *rotateMenu;
    //镜像菜单
    QMenu *mirrorMenu;

    QImage img;
    QString fileName;
    ShowWidget *showWidget;

    //文件菜单项
    QAction *openFileAction;
    QAction *NewFileAction;
    QAction *PrintTextAction;
    QAction *PrintImageAction;
    QAction *exitAction;

    //编辑菜单项
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;

    //旋转菜单项
    QAction *rotate90Action;
    QAction *rotate180Action;
    QAction *rotate270Action;

    //镜像菜单项
    QAction *mirrorVerticalAction;
    QAction *mirrorHorizontalAction;

    QAction *undoAction;
    QAction *redoAction;

    //工具栏
    QToolBar *fileTool;
    QToolBar *zoomTool;
    QToolBar *rotateTool;
    QToolBar *mirrorTool;

    QToolBar *doToolBar;

    //字体设置项
    QLabel *fontLabel1;
    QFontComboBox *fontComboBox;
    QLabel *fontlabel2;
    QComboBox *sizeComboBox;
    QToolButton *boldBtn;
    QToolButton *italicBtn;
    QToolButton *underlineBtn;
    QToolButton *colorBtn;

    //字体工具栏
    QToolBar *fontToolBar;

    //排序设置项
    QLabel *listLabel;
    QComboBox *listComboBox;
    QActionGroup *actGrp;
    QAction *leftAction;
    QAction *rightAction;
    QAction *centerAction;
    QAction *justifyAction;

    //排序工具栏
    QToolBar *listToolBar;

protected slots:
    void ShowNewFile();
    void ShowOpenFile();
    void ShowPrintText();
    void ShowPrintImage();
    void ShowZoomIn();
    void ShowZoomOut();
    void ShowRotate90();
    void ShowRotate180();
    void ShowRotate270();
    void ShowMirrorVertical();
    void ShowMirrorHorizontal();

    void ShowFontComboBox(QString comboStr);
    void ShowSizeSpinBox(QString spinValue);
    void ShowBoldBtn();
    void ShowItalicBtn();
    void ShowUnderlineBtn();
    void ShowColorBtn();
    void ShowCurrentFormatChanged(const QTextCharFormat &fmt);

    void ShowList(int);
    void ShowAlignment(QAction *act);
    void ShowCursorPositionChanged();

};
#endif // IMGPROCESSOR_H
