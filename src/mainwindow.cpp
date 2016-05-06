#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->dial, SIGNAL(valueChanged(int)), ui->lcdNumber_pan, SLOT(display(int)));

    this->workspace = new Audio::Workspace(this);

    filesModel = new QStringListModel;
    filesModel->setStringList(filesList);
    ui->fileList->setModel(filesModel);
    ui->fileList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadFile_btn_clicked()
{
    FileManager fileManager;
    fileManager.setModal(true);
    fileManager.exec();

    std::string fullPath = fileManager.ReturnPath();
    std::string fileName;

    std::size_t found_pos = fullPath.find_last_of("/\\") + 1;
    if (found_pos <= fullPath.length())
        fileName = fullPath.substr(found_pos);
    else
        fileName = fullPath;

    QString qFileName;
    qFileName = qFileName.fromStdString(fileName);

    for(int i = 0; i < filesList.size(); i++)
    {
        if(qFileName == filesList[i])
        {
            QMessageBox::critical(this, "Could not load file", "File already loaded", QMessageBox::Ok);
            return;
        }
    }

    ui->statusBar->showMessage("Successfully loaded " + qFileName, 4000);

    filesList << qFileName;
    filesModel->setStringList(filesList);

    Audio::Audiofile *newbie = new Audio::Audiofile;
    newbie->file_name = fileName;
    newbie->loadData(fullPath);
    workspace->files.insert(fileName, newbie);
}

void MainWindow::on_unloadFile_btn_clicked()
{
    if(filesList.size() == 0)
        return;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Unload file", "Do you really want to unload file from the project?",
                          QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No)
        return;
    int index = ui->fileList->currentIndex().row();
    QString qStrToDelete = filesList[index];
    std::strToDelete = qStrToDelete.toStdString();
    workspace->files.erase(strToDelete);
    filesList.removeAt(index);
    filesModel->setStringList(filesList);
}
