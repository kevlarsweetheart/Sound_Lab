#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

void MainWindow::closeWindow(QCloseEvent *event)
{
    workspace->close_openal();
    event->accept();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->dial, SIGNAL(valueChanged(int)), ui->lcdNumber_pan, SLOT(display(int)));

    workspace = new Audio::Workspace(this);

    filesModel = new QStringListModel;
    filesModel->setStringList(filesList);

    ui->infoWindow->setModel(filesModel);
    ui->infoWindow->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->infoWindow->setSelectionMode(QAbstractItemView::SingleSelection);
    AdjuctDragNDrop(true);
    currModel = 0;

    devicesModel = new QStringListModel;
    devicesList = workspace->list_capture_devices();
    devicesModel->setStringList(devicesList);

    ui->dial->setValue(50);
    ui->verticalSlider->setValue(100);

    ui->comboBox->addItem("Files");
    setTimeNull();
    ui->comboBox->addItem("Devices");
    InitHotkeys();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTime(double value)
{
    ui->lcdNumber->display(value);
    /*int newTime = int(1000.0f * value);
    int timeDiff = newTime - currTime.msec();
    //qDebug() << timeDiff;
    currTime = currTime.addMSecs(timeDiff);
    //qDebug() << currTime;
    ui->timeEdit->setTime(currTime);
    ui->timeEdit->show();*/
}

void MainWindow::setTimeNull()
{
    //QTime newTime(0, 0, 0, 0);
    //currTime = newTime;
    ui->lcdNumber->display(0);
}


void MainWindow::on_loadFile_btn_clicked()
{
    loadFile();
}

void MainWindow::on_unloadFile_btn_clicked()
{
    if(currModel == 1)
        return;

    if(filesList.size() == 0)
        return;
    if(!ui->infoWindow->currentIndex().isValid())
        return;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Unload file", "Do you really want to unload file from the project?",
                          QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No)
        return;
    int index = ui->infoWindow->currentIndex().row();
    QString qStrToDelete = filesList[index];
    std::string strToDelete = qStrToDelete.toStdString();
    workspace->files.erase(strToDelete);
    filesList.removeAt(index);
    filesModel->setStringList(filesList);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    AdjustComboBox(arg1);
}

void MainWindow::AdjuctDragNDrop(bool flag)
{
    //not finished yet
    ui->infoWindow->setDragEnabled(flag);
    ui->infoWindow->setAcceptDrops(flag);
    ui->infoWindow->setDropIndicatorShown(flag);
}

void MainWindow::InitHotkeys()
{
    addFile = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this);
    connect(addFile, SIGNAL(activated()), this, SLOT(loadFile()));
}

void MainWindow::AdjustComboBox(const QString &name)
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


void MainWindow::on_addTrack_btn_clicked()
{
    workspace->add_track();
    ui->statusBar->showMessage("Added track " + QString::number(workspace->tracks_cnt()), 3000);
}


void MainWindow::on_play_btn_clicked()
{
    play();
}

void MainWindow::on_stop_btn_clicked()
{
    stop();
}


void MainWindow::on_addSound2Track_btn_clicked()
{
    if(currModel == 1)
        return;
    if(filesList.size() == 0)
        return;
    if(!ui->infoWindow->currentIndex().isValid())
        return;

    int index = ui->infoWindow->currentIndex().row();
    QString qFilePartName = filesList[index];
    std::string filePartName = qFilePartName.toStdString();
    qFilePartName += "_brick";
    workspace->tracks[workspace->tracks_cnt() - 1]->push_brick  (workspace->files[filePartName], qFilePartName);
}

void MainWindow::loadFile()
{
    FileManager fileManager;
    fileManager.setModal(true);
    fileManager.exec();

    std::string fullPath = fileManager.ReturnPath();

    if(fullPath == "/cancel/")
        return;

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
    newbie->load_data(fullPath);
    workspace->files.insert(std::pair<std::string, Audio::Audiofile*>(fileName, newbie));
}

void MainWindow::play()
{
    if(!(ui->play_btn->isChecked()))
    {
        workspace->pause();
        qDebug() << "Pausing";
    }
    else
    {
        workspace->play();
        qDebug() << "Playing";
    }
}

void MainWindow::stop()
{
    workspace->stop();
    setTimeNull();
    ui->play_btn->setChecked(false);
}
