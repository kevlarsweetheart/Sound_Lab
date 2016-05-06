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

private:
    Ui::MainWindow *ui;
    QStringListModel *filesModel;
    QStringList filesList;
};

#endif // MAINWINDOW_H
