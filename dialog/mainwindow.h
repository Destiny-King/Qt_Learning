#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "spreadsheet.h"
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QSlider>
class QAction;
class QLabel;
class FindDialog;
class Spreadsheet;
class QToolBar;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void find();
    void goToCell();
    void sort();
    void about();
    void selectAll();
    bool setShowGrid();
    void aboutQt();

    void openRecentFile();
    void updateStatusBar();
    void spreadsheetModified();

private:
    //私有函数
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool okToContinu();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);

    //私有变量
    Spreadsheet *spreadsheet;
    FindDialog *findDialog;
    QLabel *locationLabel;
    QLabel *formulaLabel;
    QStringList recentFiles;
    QString curFile;

    enum {MaxRecentFiles = 5};
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *selectSubMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *selectAllAction;
    QAction *selectRowAction;
    QAction *selectColumnAction;
    QAction *findAction;
    QAction *goToCellAction;
    QAction *recalculateAction;
    QAction *autoRecalcAction;
    QAction *sortAction;
    QAction *showGridAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

signals:
    void fingNext(const QString &,Qt::CaseSensitivity);
    void findPrevious(const QString &,Qt::CaseSensitivity);

//    QWidget *hWidget;
//    QHBoxLayout *hBoxLayout;
//    QSpinBox *spinBox;
//    QSlider *slider;
};
#endif // MAINWINDOW_H
