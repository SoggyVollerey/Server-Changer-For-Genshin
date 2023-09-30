#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <qgridlayout.h>
#include <QImage >
#include "ui_MainWindow.h"
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMenuBar* menuBar ;
    QMenu* settingsMenu ;
    QAction* saveAction ;
    QAction* timeAction;
    QPushButton* btn1;
    QPushButton* btn2 ;
    QPushButton* btn3 ;
    QPushButton* btn4 ;
    QPushButton* btn5;
    QLabel* imageLabel;
    QGridLayout* mainLayout;
    QImage img;


    QString filePath1;
    QString filePath2;
    QString filePath3;
    QString filePath4;

    //涉及文件的几个变量
    QString filePath = "input.txt"; // input.txt文件的路径
    QString fileFullPath; // 用于保存文件的完整路径
    QString directoryPath; // 用于保存目录路径的变量

    bool checkFileExist(const QString& folderPath, const QString& fileName);
    void showQuestionMsg();

private:
    Ui::MainWindowClass ui;

private slots:
    void showSettingsDialog();
    void setStartDuration();
};
