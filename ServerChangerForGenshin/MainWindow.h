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

    //�漰�ļ��ļ�������
    QString filePath = "input.txt"; // input.txt�ļ���·��
    QString fileFullPath; // ���ڱ����ļ�������·��
    QString directoryPath; // ���ڱ���Ŀ¼·���ı���

    bool checkFileExist(const QString& folderPath, const QString& fileName);
    void showQuestionMsg();

private:
    Ui::MainWindowClass ui;

private slots:
    void showSettingsDialog();
    void setStartDuration();
};
