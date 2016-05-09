#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->dial, SIGNAL(valueChanged(int)), ui->lcdNumber_pan, SLOT(display(int)));
    filesModel = new QStringListModel;
    filesModel->setStringList(filesList);
    ui->infoWindow->setModel(filesModel);
    ui->infoWindow->setEditTriggers(QAbstractItemView::NoEditTriggers);
    currModel = 0;

    devicesModel = new QStringListModel;
    devicesModel->setStringList(devicesList);

    ui->dial->setValue(50);
    ui->verticalSlider->setValue(100);

    ui->comboBox->addItem("Files");
    ui->comboBox->addItem("Devices");
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
    workspace->files.insert(std::pair<std::string, Audio::Audiofile*>(fileName, newbie));
}

void MainWindow::on_unloadFile_btn_clicked()
{
    if(currModel == 1)
        return;

    if(filesList.size() == 0)
        return;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Unload file", "Do you really want to unload file from the project?",
                          QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No)
        return;
    int index = ui->fileList->currentIndex().row();
    QString qStrToDelete = filesList[index];
    std::string strToDelete = qStrToDelete.toStdString();
    workspace->files.erase(strToDelete);
    filesList.removeAt(index);
    filesModel->setStringList(filesList);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    adjustComboBox(arg1);
}

void MainWindow::adjustComboBox(const QString &name)
{
    if(name == "Files")
    {
        currModel = 0;
        ui->infoWindow->setModel(filesModel);
    }
    if(name == "Devices")
    {
        currModel = 1;
        ui->infoWindow->setModel(devicesModel);
    }
}
