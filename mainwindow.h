#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "appinfo.h"
#include "targetfilehandler.h"
//#include "treemodel.h"
//#include "treeitem.h"
#include "treeitem2.h"
#include "treemodel2.h"


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
#ifdef  TASK_0_0_2
    void clickOnActtion_OpenTarget();
#endif
    void about();

private:
    void createActions();
    void createMenus();

    QMenu* fileMenu;
    QMenu* helpMenu;

    QAction* actCreateNewTarget;
#ifdef  TASK_0_0_2
    QAction* actOpenTarget;
#endif
    QAction* actExit;
    QAction* actAbout;
    QAction* actAboutQt;

#ifdef  TASK_0_0_3
//    TreeModel* model;
    TreeModel2* model2;
    QTreeView* treeView;
#endif
};

#endif // MAINWINDOW_H
