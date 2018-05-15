#ifndef NEWTARGETCREATIONWINDOW_H
#define NEWTARGETCREATIONWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QListView>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QDebug>
#include <QFileDialog>
#include <QStringList>
#include <QStringListModel>
#include <QMessageBox>
#include <QDir>
#include <QAbstractItemView>
#include <QList>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

class TargetFileHandler : public QDialog
{
    Q_OBJECT
public:

    enum class mode{
        create,
        edit
    };

    explicit TargetFileHandler(mode mode_, const QString& targetPath_ = "", QWidget *parent = nullptr);

signals:

public slots:
    void btnPath2TargetOnClick();
    void btnOkOnClick();
    void btnIgnoredListAddOnClick();
    void btnIgnoredListClearOnClick();
    void btnIgnoredListRemoteOnClick();
    void btnSourceDirOnClick();
    void btnOutputDirOnClick();

private:
    mode m_mode;
    QString m_targetPath;

    QLabel *lblPath2Target;
    QLabel *lblTargetName;

    QLabel *lblSourceDir;
    QLineEdit* leSourceDir;
    QPushButton* btnSourceDir;

    QLabel *lblOutputDir;
    QLineEdit* leOutputDir;
    QPushButton* btnOutputDir;

    QLabel *lblIgnored;
    QLineEdit *lePath2Target;
    QLineEdit *leTargetName;
    QPushButton* btnEsc;
    QPushButton* btnOk;
    QPushButton* btnPath2Target;
    QPushButton* btnIgnoredListClear;
    QPushButton* btnIgnoredListAdd;
    QPushButton* btnIgnoredListRemote;
    QListView *lstvIgnored;
    QStringListModel* ignoredListModel;
};

#endif // NEWTARGETCREATIONWINDOW_H
