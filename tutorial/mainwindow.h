#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_toolButton_4_clicked();

private:
    Ui::MainWindow *ui;
    int dataint;
    double datadou;
    bool databoo;
    QString datastr;
    int data;
};

#endif // MAINWINDOW_H
