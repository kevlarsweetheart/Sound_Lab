#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->dial, SIGNAL(valueChanged(int)), ui->lcdNumber_pan, SLOT(display(int)));
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
}

void MainWindow::on_unloadFile_btn_clicked()
{

}
