#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "appinfo.h"
#include "targetfilehandler.h"
//#include "treemodel.h"
//#include "treeitem.h"
#include "treeitem.h"
#include "treemodel.h"


#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QMessageBox>
#include <QApplication>
#include <QMenuBar>
#include <QDebug>
#include <QTreeView>
#include <QTreeWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void createNewTarget();
    void clickOnActtion_OpenTarget();
    void about();

private:
    void createActions();
    void createMenus();

    QMenu* fileMenu;
    QMenu* helpMenu;

    QAction* actCreateNewTarget;
    QAction* actOpenTarget;
    QAction* actExit;
    QAction* actAbout;
    QAction* actAboutQt;

    TreeModel* model;
    QTreeView* treeView;
};

#endif // MAINWINDOW_H
