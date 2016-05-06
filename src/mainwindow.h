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

namespace Ui {
class MainWindow;
}

namespace Audio
{
    class Workspace;
    class Track;
    class Audiofile;
    class FilePart;
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

private:
    Ui::MainWindow *ui;
    Audio::Workspace *workspace;
    QStringListModel *filesModel;
    QStringList filesList;
};

#endif // MAINWINDOW_H
