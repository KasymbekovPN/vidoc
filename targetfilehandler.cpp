#include "targetfilehandler.h"

TargetFileHandler::TargetFileHandler(mode mode_, QWidget *parent) : QDialog(parent)
{

    lblName = new QLabel(tr("Имя цели:"));
    lblPath = new QLabel(tr("Путь до цели:"));
    lblIgnored = new QLabel(tr("Игнорируемое:"));
    leName = new QLineEdit;
    lePath = new QLineEdit;
    btnPath = new QPushButton(tr("..."));
    btnEsc = new QPushButton(tr("Закрыть"));
//    btnEsc->setWindow
    btnOk = new QPushButton(tr("OK"));
    btnIgnoredListClear = new QPushButton(tr("Очитить"));
    btnIgnoredListRemote = new QPushButton(tr("Удалить"));
    btnIgnoredListAdd = new QPushButton(tr("Добавить"));
    lstvIgnored = new QListView;    

    QHBoxLayout *footLay = new QHBoxLayout;
    footLay->addSpacing(300);
    footLay->addWidget(btnEsc);
    footLay->addWidget(btnOk);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lblName, 0, 0);
    layout->addWidget(leName, 0, 1);
    layout->addWidget(lblPath, 1, 0);
    layout->addWidget(lePath, 1, 1);
    layout->addWidget(btnPath, 1, 2);
    layout->addWidget(lblIgnored, 2, 0);
    layout->addWidget(lstvIgnored, 2, 1, 3, 1);
    layout->addWidget(btnIgnoredListAdd, 2, 2);
    layout->addWidget(btnIgnoredListRemote, 3, 2);
    layout->addWidget(btnIgnoredListClear, 4, 2);
    layout->addLayout(footLay, 5, 0, 1, 3);

    setLayout(layout);

    setWindowTitle(tr("Новая цель"));
    setMinimumSize(200, 200);
    resize(470, 210);

    connect(btnPath, SIGNAL(clicked()), this, SLOT(btnPathOnClick()));
    connect(btnEsc, SIGNAL(clicked()), this, SLOT(close()));
    connect(btnOk, SIGNAL(clicked()), this, SLOT(btnOkOnClick()));
    connect(btnIgnoredListAdd, SIGNAL(clicked()), this, SLOT(btnIgnoredListAddOnClick()));
    connect(btnIgnoredListClear, SIGNAL(clicked()), this, SLOT(btnIgnoredListClearOnClick()));
    connect(btnIgnoredListRemote, SIGNAL(clicked()), this, SLOT(btnIgnoredListRemoteOnClick()));
}

void TargetFileHandler::btnPathOnClick()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Укажите путь к папке"), tr("C://"));
    qDebug() << path;
}

void TargetFileHandler::btnOkOnClick()
{
    qDebug() << "btnOkOnClick";
}

void TargetFileHandler::btnIgnoredListAddOnClick()
{
    qDebug() << "btnIgnoredListAddOnClick";
}

void TargetFileHandler::btnIgnoredListClearOnClick()
{
    qDebug() << "btnIgnoredListClearOnClick";
}

void TargetFileHandler::btnIgnoredListRemoteOnClick()
{
    qDebug() << "btnIgnoredListRemoteOnClick";
}
