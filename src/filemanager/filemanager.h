#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDialog>
#include <string>
#include <QFileSystemModel>

namespace Ui {
class FileManager;
}

class FileManager : public QDialog
{
    Q_OBJECT

public:
    explicit FileManager(QDialog *parent = 0);
    ~FileManager();
    std::string ReturnPath();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_cancel_btn_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_load_btn_clicked();

private:
    Ui::FileManager *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    std::string fullPath;
};

#endif // FILEMANAGER_H
