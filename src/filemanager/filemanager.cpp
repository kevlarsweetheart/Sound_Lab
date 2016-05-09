#include "filemanager.h"
#include "ui_filemanager.h"
#include <QSortFilterProxyModel>

FileManager::FileManager(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::FileManager)
{
    ui->setupUi(this);
    dirModel = new QFileSystemModel(this);
    fileModel = new QFileSystemModel(this);

    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(QDir::currentPath());

    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    fileModel->setRootPath(QDir::currentPath());

    ui->treeView->setSortingEnabled(true);
    ui->treeView->setModel(dirModel);
    ui->listView->setModel(fileModel);
}

FileManager::~FileManager()
{
    delete ui;
}

void FileManager::on_treeView_clicked(const QModelIndex &index)
{
    QString currPath = dirModel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(fileModel->setRootPath(currPath));
}

void FileManager::on_cancel_btn_clicked()
{
    this->fullPath = "/cancel/";
    this->close();
}

void FileManager::on_listView_clicked(const QModelIndex &index)
{
    ui->label->setText(fileModel->fileInfo(index).absoluteFilePath());
}

void FileManager::on_listView_doubleClicked(const QModelIndex &index)
{
    std::string fileName = fileModel->fileInfo(index).absoluteFilePath().toStdString();
    std::size_t foundDot = fileName.find_last_of(".") + 1;
    if(foundDot <= fileName.length())
    {
        std::string format = fileName.substr(foundDot);
        if(format == "wav")
        {
           this->fullPath = fileName;
           this->close();
        }
    }
    ui->label->setText("Wrong format");
}

void FileManager::on_load_btn_clicked()
{
    this->on_listView_doubleClicked(ui->listView->currentIndex());
}


std::string FileManager::ReturnPath()
{
    return this->fullPath;
}
