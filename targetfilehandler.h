#ifndef NEWTARGETCREATIONWINDOW_H
#define NEWTARGETCREATIONWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QListView>

class TargetFileHandler : public QDialog
{
    Q_OBJECT
public:

    enum class mode{
        create,
        edit
    };

    explicit TargetFileHandler(mode mode_, QWidget *parent = nullptr);

signals:

public slots:

private:
    QLabel *lblPath;
    QLabel *lblName;
    QLabel *lblIgnored;
    QLineEdit *lePath;
    QLineEdit *leName;
    QPushButton* btnEsc;
    QPushButton* btnOk;
    QPushButton* btnPath;
    QPushButton* btnIgnoredListClear;
    QPushButton* btnIgnoredListAdd;
    QPushButton* btnIgnoredListRemote;
    QListView *lstvIgnored;
};

#endif // NEWTARGETCREATIONWINDOW_H
