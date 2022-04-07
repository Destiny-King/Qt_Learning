#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gotocelldialog.h"
#include "mainwindow.h"
#include "sortdialog.h"
#include "spreadsheet.h"
#include "qtoolbar.h"
#include "finddialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    spinBox = new QSpinBox;
//    spinBox->setMaximumWidth(60);
//    slider = new QSlider(Qt::Horizontal);
//    spinBox->setRange(0,130);
//    slider->setRange(0,130);

//    connect(spinBox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
//    connect(slider,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
//    spinBox->setValue(35);

//    hBoxLayout = new QHBoxLayout();
//    hBoxLayout->addWidget(spinBox);
//    hBoxLayout->addWidget(slider);

//    hWidget = new QWidget;
//    hWidget->setLayout(hBoxLayout);
//    hWidget->setParent(this);

    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();
    findDialog = 0;

    setWindowIcon(QIcon(":/images/logo.png"));
    setCurrentFile("");
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(okToContinu()){
        writeSettings();
        event->accept();
    }else{
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if(okToContinu()){
        spreadsheet->clear();
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if(okToContinu()){
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open Spreadsheet"),".",tr("Spreadsheet files(*.sp)"));
        if(!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if(curFile.isEmpty()){
        return saveAs();
    }else{
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Spreadsheet"),".",tr("Spreadsheet file(*.sp)"));
    if(fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

void MainWindow::find()
{
    if(!findDialog){
        findDialog = new FindDialog(this);
        connect(findDialog,SIGNAL(findNext(const QString &,Qt::CaseSensitivity)),spreadsheet,SLOT(findNext(const QString &,Qt::CaseSensitivity)));
        connect(findDialog,SIGNAL(findPrevious(const QString &,Qt::CaseSensitivity)),spreadsheet,SLOT(findPrevious(const QString &,Qt::CaseSensitivity)));
    }
    findDialog->show();
    //让窗口成为顶层窗口
    findDialog->raise();
    //让窗口成为激活状态
    findDialog->activateWindow();
}

void MainWindow::goToCell()
{
    GoToCellDialog *dialog = new GoToCellDialog() ;
    if(dialog->exec()){
        QString str = dialog->lineEdit->text().toUpper();
        //行索引，列索引
        spreadsheet->setCurrentCell(str.mid(1).toInt() - 1,str[0].unicode() - 'A');
    }
    delete dialog;
}

void MainWindow::sort()
{
    SortDialog dialog(this);
    dialog.setSpreadsheet(spreadsheet);
    dialog.exec();
}

void MainWindow::about()
{
    QMessageBox::about(this,tr("About Spreadsheet"),
                       tr("<h2>Spreadsheet 1.1</h2>"
                          "<p>Copyright &copy;2008 Software Inc."
                          "<p>Spreadsheet is a small application that"
                          "demonstrates QAction,QMainWindow,QMenuBar,"
                          "QStatusBar,QTableWidget,QToolBar,and many other"
                          "Qt classes."));
}

void MainWindow::selectAll()
{

}

bool MainWindow::setShowGrid()
{

}

void MainWindow::aboutQt()
{

}

void MainWindow::openRecentFile()
{
    if(okToContinu()){
        QAction *action = qobject_cast<QAction *>(sender());
        if(action)
            loadFile(action->data().toString());
    }
}

void MainWindow::updateStatusBar()
{
    locationLabel->setText(spreadsheet->currentLocation());
    formulaLabel->setText(spreadsheet->currenFormula());
}

void MainWindow::spreadsheetModified()
{
    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&new"),this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(newFile()));

    openAction = new QAction(tr("&open"),this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a spreadsheet file"));
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

    saveAction = new QAction(tr("&save"),this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a spreadsheet file"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(save()));

    saveAsAction = new QAction(tr("&saveAs"),this);
    saveAsAction->setIcon(QIcon(":/images/saveAs.png"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("saveAs a spreadsheet file"));
    connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i],SIGNAL(triggered()),this,SLOT(openRecentFile()));
    }

    exitAction = new QAction(tr("&Exit"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    selectAllAction = new QAction(tr("&All"),this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction,SIGNAL(triggered()),spreadsheet,SLOT(selectAll()));

    showGridAction = new QAction(tr("&Show Grid"),this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the spreadsheet's grid"));
    connect(showGridAction,SIGNAL(toggled(bool)),spreadsheet,SLOT(setShowGrid(bool)));

    aboutAction = new QAction(tr("About &Qt"),this);
    aboutAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    separatorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    selectSubMenu = editMenu->addMenu(tr("&Select"));
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalcAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createContextMenu()
{
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);
}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel("W99");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    //添加缩进格式
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel,1);

    connect(spreadsheet,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(updateStatusBar()));
    connect(spreadsheet,SIGNAL(modified()),this,SLOT(spreadsheetModified()));
    updateStatusBar();
}

void MainWindow::readSettings()
{
    QSettings settings("Software Inc.","Spreadsheet");
    restoreGeometry(settings.value("gemotry").toByteArray());
    recentFiles = settings.value("recentFile").toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value("showGrid",true).toBool();
    showGridAction->setChecked(showGrid);

    bool autoRecalc = settings.value("autoRecalc",true).toBool();
    autoRecalcAction->setChecked(autoRecalc);
}

void MainWindow::writeSettings()
{
    QSettings settings("Software Inc.","Spreadsheet");
    settings.setValue("geometry",saveGeometry());
    settings.setValue("recentFiles",recentFiles);
    settings.setValue("showGrid",showGridAction->isChecked());
    settings.setValue("autoRecalc",autoRecalcAction->isChecked());
}

bool MainWindow::okToContinu()
{
    if(isWindowModified()){
        int r = QMessageBox::warning(this,tr("Spreadsheet"),tr("The document has been modified.\n" "Do you want to save your changes?"),QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(r == QMessageBox::Yes){
            return save();
        }else if(r == QMessageBox::Cancel){
            return false;
        }
    }
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    if(!spreadsheet->readFile(fileName)){
        statusBar()->showMessage(tr("Loading canceled"),2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"),2000);
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    if(!spreadsheet->writeFile(fileName)){
        statusBar()->showMessage(tr("Saving canceled"),2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File save"),2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = tr("Untitled");
    if(!curFile.isEmpty()){
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Spreadsheet")));
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);
    while (i.hasNext()) {
        if(!QFile::exists(i.next()))
            i.remove();
    }
    for (int j = 0; j < MaxRecentFiles; ++j) {
        if(j < recentFiles.count()){
            QString text = tr("&%1 %2").arg(j + 1).arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }else{
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

