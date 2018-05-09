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
    btnOk = new QPushButton(tr("OK"));
    btnIgnoredListClear = new QPushButton(tr("Очитить"));
    btnIgnoredListRemote = new QPushButton(tr("Удалить"));
    btnIgnoredListAdd = new QPushButton(tr("Добавить"));
    lstvIgnored = new QListView;

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
    layout->addWidget(btnEsc, 5, 1);
    layout->addWidget(btnOk, 5, 2);


    setLayout(layout);

    setWindowTitle(tr("Новая цель"));
    setMinimumSize(200, 200);
    resize(470, 210);
}
