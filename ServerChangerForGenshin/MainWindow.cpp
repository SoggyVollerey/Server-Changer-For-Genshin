#pragma execution_character_set("utf-8")

#include "MainWindow.h"
#include <QPushButton>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <QTextStream>
#include <QSettings>
#include <QLineEdit>



bool MainWindow::checkFileExist(const QString& folderPath, const QString& fileName)
{
    QDir folderDir(folderPath);
    if (!folderDir.exists()) {
        return false; // 文件夹不存在
    }

    QString filePath = folderDir.absoluteFilePath(fileName);
    QFile file(filePath);
    return file.exists(); // 检查文件是否存在
}
void MainWindow::setStartDuration() {
    QDialog setTimeDialog(this);
    setTimeDialog.setWindowTitle("设置");
    QVBoxLayout layout(&setTimeDialog);
    QLineEdit inputTextEdit(&setTimeDialog);
    QPushButton saveButton("保存", &setTimeDialog);
    layout.addWidget(&inputTextEdit);
    layout.addWidget(&saveButton);

    QMessageBox::information(this, "Information", "取消启动动画请输入0，设置时间输入0到5000，单位毫秒。其余输入默认为4800");

    connect(&saveButton, &QPushButton::clicked, [&]() {

        //QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "Text files (*.txt)");
        if (1) {
            QFile file("in.txt");
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&file);
                QString str= inputTextEdit.text();
                bool ok = 0;
                int k = str.toInt(&ok);
                if (ok && k >= 0 && k <= 5000)
                    ;
                else
                    str = "4800";
                stream << str;
                file.close();
                QMessageBox::information(this, "Saved", "保存成功!请重启应用后再执行其它操作");
            }
            else {
                QMessageBox::critical(this, "Error", "Failed to save file.");
            }
        }

        });

    setTimeDialog.exec();
}
void MainWindow::showSettingsDialog() {
    QDialog settingsDialog(this);
    settingsDialog.setWindowTitle("设置");
    QVBoxLayout layout(&settingsDialog);
    QLineEdit inputTextEdit(&settingsDialog);
    QPushButton saveButton("保存", &settingsDialog);
    QPushButton locateButton("定位", &settingsDialog);

    layout.addWidget(&inputTextEdit);
    layout.addWidget(&saveButton);
    layout.addWidget(&locateButton);

    connect(&locateButton, &QPushButton::clicked, [&]() {
        QString s = QFileDialog::getOpenFileName(
            this, "open file diolog", "/", "Executable Files(*.exe)"
        );
        inputTextEdit.setText(s);
        });
    connect(&saveButton, &QPushButton::clicked, [&]() {

        //QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "Text files (*.txt)");
        if (1) {
            QFile file("input.txt");
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&file);
                stream << inputTextEdit.text();
                file.close();
                QMessageBox::information(this, "Saved", "保存成功!请重启应用后再执行其它操作");
            }
            else {
                QMessageBox::critical(this, "Error", "Failed to save file.");
            }
        }

        });

    settingsDialog.exec();
}

void MainWindow::showQuestionMsg()
{

    switch (QMessageBox::question(this, tr("Question消息框"),
        tr("真的要退出吗？"),
        QMessageBox::Yes | QMessageBox::No))
    {
    case QMessageBox::Yes:
        this->close();
        break;
    case QMessageBox::No:

        break;
    default:
        break;
    }
    return;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    resize(1490, 840);
    setWindowTitle("原神换服器");
    QPalette pa1(this->palette());
    QPalette pa2(this->palette());
    QImage qimg1 = QImage(":/gif/C:/Users/Soggy/Desktop/G/nahida.jpeg");
    QImage qimg2 = QImage(":/gif/C:/Users/Soggy/Desktop/G/m.png");
    qimg1 = qimg1.scaled(this->size());
    qimg2 = qimg2.scaled(this->size());
    QBrush* pic1 = new QBrush(qimg1);
    pa1.setBrush(QPalette::Window, *pic1);
    QBrush* pic2 = new QBrush(qimg2);
    pa2.setBrush(QPalette::Window, *pic2);
    this->setPalette(pa1);


    //主界面
    menuBar = new QMenuBar(this);
    settingsMenu = menuBar->addMenu("设置");
    saveAction = settingsMenu->addAction("设置原神启动器路径");
    timeAction = settingsMenu->addAction("设置启动动画时长");
    connect(saveAction, &QAction::triggered, this, &MainWindow::showSettingsDialog);
    connect(timeAction, &QAction::triggered, this, &MainWindow::setStartDuration);

    setMenuBar(menuBar);

    btn1 = new QPushButton("检查当前情况", this);
    btn1->move(450, 100);
    btn1->resize(200, 80);
    btn1->setStyleSheet("font-family:'Microsoft YaHei';background-color:#c0ffe5;");
    btn2 = new QPushButton("官服转B服", this);
    btn2->move(450, 250);
    btn2->resize(200, 80);
    btn2->setStyleSheet("font-family:'Microsoft YaHei';background-color:#c0ffe5;");
    btn3 = new QPushButton("B服转官服", this);
    btn3->move(450, 400);
    btn3->resize(200, 80);
    btn3->setStyleSheet("font-family:'Microsoft YaHei';background-color:#c0ffe5;");
    btn4 = new QPushButton("退出", this);
    btn4->move(450, 550);
    btn4->resize(200, 80);
    btn4->setStyleSheet("font-family:'Microsoft YaHei';background-color:#c0ffe5;");
    btn5 = new QPushButton("更换背景", this);
    btn5->move(450, 700);
    btn5->resize(200, 80);
    btn5->setStyleSheet("font-family:'Microsoft YaHei';background-color:#c0ffe5;");

    imageLabel = new QLabel(this);
    imageLabel->move(1000, 300);
    imageLabel->setScaledContents(true);
    imageLabel->resize(300, 300);

    if (img.load(":/gif/C:/Users/Soggy/Desktop/G/ayaka.png"))
        imageLabel->setPixmap(QPixmap::fromImage(img));

    //读取路径
    QFile file("input.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) { // 打开文件
        QTextStream in(&file);
        fileFullPath = in.readLine(); // 读取第一行文本，即文件完整路径
        file.close(); // 关闭文件
        QFileInfo fileInfo(fileFullPath);
        directoryPath = fileInfo.dir().absolutePath(); // 获取文件所在目录的绝对路径
    }
    else {
        // 处理文件打开失败的情况
        QMessageBox::information(this, tr("Information消息框"), tr("文件读取失败"));// "文件读取失败"
    }
    QDir Directory(directoryPath); // 创建g文件夹的QDir实例
    QString subDirectoryPath1 = QDir(directoryPath).absoluteFilePath("Genshin Impact Game"); // g文件夹的路径
    QDir subDirectory1(subDirectoryPath1); // 创建g文件夹的QDir实例
    QString subDirectoryPath2 = QDir(directoryPath).absoluteFilePath("Genshin Impact Game/YuanShen_Data/Plugins"); // p文件夹的路径
    QDir subDirectory2(subDirectoryPath2); // 创建p文件夹的QDir实例

    filePath1 = Directory.filePath("config.ini"); // config.ini文件的完整路径
    filePath2 = subDirectory1.filePath("config.ini"); // config.ini文件的完整路径
    filePath3 = subDirectory2.filePath("PCGameSDK.dll");
    filePath4 = subDirectory2.filePath("PCGameSDK.dllsc");

    //主界面功能实现
    connect(btn4, &QPushButton::clicked, [=]() {showQuestionMsg();});

    connect(btn1, &QPushButton::clicked, [=]() {
        if (checkFileExist(subDirectoryPath2, "PCGameSDK.dll")) {
            QMessageBox::information(this, tr("Information消息框"),
                tr("当前为B服"));// 文件存在
        }
        else if(checkFileExist(subDirectoryPath2, "license.txt")){
            QMessageBox::information(this, tr("Information消息框"),
                tr("当前为官服"));// 文件不存在
        }
        else
            QMessageBox::information(this, tr("Information消息框"),tr("未检测到应有文件，请检查定位是否正确"));// 文件不存在
        if (img.load(":/gif/C:/Users/Soggy/Desktop/G/kurumi.png"))
            imageLabel->setPixmap(QPixmap::fromImage(img));
        });

    connect(btn2, &QPushButton::clicked, [=]() {
        if (!checkFileExist(directoryPath, "config.ini")) {
            QMessageBox::warning(this, tr("Warning消息框"),
                tr("未检测到应有文件，请检查定位是否正确"));// 文件不存在
        }
        else {
            QSettings settings(filePath2, QSettings::IniFormat);
            settings.setValue("cps", "bilibili");
            settings.setValue("channel", "14");
            settings.setValue("sub_channel", "0");
            settings.sync();

            QSettings settings2(filePath1, QSettings::IniFormat);
            settings2.beginGroup("launcher");
            settings2.setValue("cps", "bilibili");
            settings2.setValue("channel", "14");
            settings2.setValue("sub_channel", "0");
            settings2.endGroup();

            QString oldFileName = filePath4;
            QString newFileName = filePath3;
            if (QFile::rename(oldFileName, newFileName)) {
                QMessageBox::information(this, tr("Information消息框"),
                    tr("文件修改成功"));
            }
            else {
                QMessageBox::information(this, tr("Information消息框"),
                    tr("文件修改失败"));
            }
        }
        });

    connect(btn3, &QPushButton::clicked, [=]() {
        if (!checkFileExist(directoryPath, "config.ini")) {
            QMessageBox::warning(this, tr("Warning消息框"),
                tr("未检测到应有文件，请检查定位是否正确"));// 文件不存在
        }
        else {
            QSettings settings(filePath2, QSettings::IniFormat);
            settings.setValue("cps", "mihoyo");
            settings.setValue("channel", "1");
            settings.setValue("sub_channel", "1");
            settings.sync();

            QSettings settings2(filePath1, QSettings::IniFormat);
            settings2.beginGroup("launcher");
            settings2.setValue("cps", "mihoyo");
            settings2.setValue("channel", "1");
            settings2.setValue("sub_channel", "1");
            settings2.endGroup();

            QString oldFileName = filePath3;
            QString newFileName = filePath4;

            if (QFile::rename(oldFileName, newFileName)) {
                QMessageBox::information(this, tr("Information消息框"),
                    tr("文件修改成功"));
            }
            else {
                QMessageBox::information(this, tr("Information消息框"),
                    tr("文件修改失败"));
            }
        }
        });
    connect(btn5, &QPushButton::clicked, [=]() {
        QPalette currentPalette = this->palette();
        if (currentPalette.window() == pa1.window()) {
            // 当前使用的调色板为 pa1
            resize(1440, 810);
            this->setPalette(pa2);
        }
        else if (currentPalette.window() == pa2.window()) {
            // 当前使用的调色板为 pa2
            resize(1490, 840);
            this->setPalette(pa1);
        }
        else {
            // 未知的调色板
            QMessageBox::warning(this, tr("Warning消息框"),
                tr("调色板调用错误"));
        }
        });

    //界面优化
    connect(btn1, &QPushButton::pressed, [=]() {
        if (img.load(":/gif/C:/Users/Soggy/Desktop/G/kokusei.png"))
            imageLabel->setPixmap(QPixmap::fromImage(img));
        });
    connect(btn2, &QPushButton::pressed, [=]() {
        if (img.load(":/gif/C:/Users/Soggy/Desktop/G/klee.png"))
            imageLabel->setPixmap(QPixmap::fromImage(img));
        });
    connect(btn3, &QPushButton::pressed, [=]() {
        if (img.load(":/gif/C:/Users/Soggy/Desktop/G/shogun.png"))
            imageLabel->setPixmap(QPixmap::fromImage(img));
        });
    connect(btn4, &QPushButton::pressed, [=]() {
        if (img.load(":/gif/C:/Users/Soggy/Desktop/G/kokomi.png"))
            imageLabel->setPixmap(QPixmap::fromImage(img));
        });
}

MainWindow::~MainWindow()
{}
