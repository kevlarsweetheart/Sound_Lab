#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <string>
#include <QStringList>
#include <QStringListModel>
#include <QMessageBox>
#include "filemanager/filemanager.h"
#include "core/audio.h"

namespace Audio
{
    class Workspace;
    class Track;
    class Audiofile;
    class FilePart;
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadFile_btn_clicked();

    void on_unloadFile_btn_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_addTrack_btn_clicked();

    void on_play_btn_clicked();

    void on_stop_btn_clicked();

    void on_addSound2Truck_btn_clicked();

private:

    void AdjustComboBox(const QString &name);
    void AdjuctDragNDrop(bool flag); //true when filesModel, false when deviceModel;


    Ui::MainWindow *ui;
    Audio::Workspace *workspace;

    QStringListModel *filesModel;
    QStringListModel *devicesModel;
    QStringList filesList;
    QStringList devicesList;
    int currModel; //0 - files, 1 - devices
};

#endif // MAINWINDOW_H
