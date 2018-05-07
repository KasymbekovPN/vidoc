#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "appinfo.h"

#include <QMainWindow>
#include <QAction>
//#include <QActionGroup>
//#include <QLabel>
#include <QMenu>
#include <QVBoxLayout>
//#include <QString>
#include <QStatusBar>
//#include <QContextMenuEvent>
#include <QMessageBox>
#include <QApplication>
#include <QMenuBar>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void createNewTarget();
    void about();

private:
    void createActions();
    void createMenus();

    QMenu* fileMenu;
    QMenu* helpMenu;

    QAction* actCreateNewTarget;
    QAction* actExit;
    QAction* actAbout;
    QAction* actAboutQt;
};

#endif // MAINWINDOW_H