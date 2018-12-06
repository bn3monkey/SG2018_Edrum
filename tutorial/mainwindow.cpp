#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    QString ID = ui->ID->text();
    QString PW = ui->PW->text();
    ui->DEBUG_RESULT->setText("Your ID : " + ID + "\n" + "Your PW : " + PW);
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_toolButton_3_clicked()
{
    QString ID = ui->ID_new->text();
    QString PW = ui->PW_new->text();
    ui->DEBUG_RESULT_IS_SUCCEED->setText("New ID : " + ID + "\n" + "Your PW : " + PW);
}

void MainWindow::on_pushButton_2_clicked()
{
    //ui->tab_2->activateWindow();
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_toolButton_4_clicked()
{
    QString ARTIST = ui->ARTIST->text();
    QString SONG_NAME = ui->SONG_NAME->text();
    ui->DEBUG_REGISTER->setText("Artist : " + ARTIST + "\n" + "Song name : " + SONG_NAME);

}
