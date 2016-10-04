#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QTabWidget>
#include <QToolBar>
#include <QStatusBar>
#include "dialog.h"
#include "gotocelldialog.h"
#include "finddialog.h"

//QT_BEGIN_NAMESPACE
//class QTabWidget;
//class QMenu;
//class QToolBar;
//class QAction;
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();

private slots:
    void newFile();
//    void open();
//    bool save();
//    bool saveAs();
//    void find();
//    void goToCell();
//    void sort();
//    void about();
//    void openRecentFile();
//    void updateStatusBar();
//    void spreadsheetModified();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTabWidget *tabWidget;
    FindDialog *findDialog;
    QLabel *locationLabel;
    QLabel *formulaLabel;
    QStringList recentFiles;
    QString curFile;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    enum { MaxRecentFile = 5 };
    QAction *recentFileActions[MaxRecentFile];
    QAction *separatorAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *aboutMenu;
    //File Action
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    //Edit Action
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *selectAction;
    QMenu *subMenu;
    QAction *rowAction;
    QAction *columnAction;
    QAction *allAction;
    QAction *findAction;
    QAction *goToCellAction;

    //Help Action
    QAction *aboutAction;
    QAction *aboutQtAction;
};

#endif // MAINWINDOW_H
