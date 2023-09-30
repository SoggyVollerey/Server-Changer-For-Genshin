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
        return false; // �ļ��в�����
    }

    QString filePath = folderDir.absoluteFilePath(fileName);
    QFile file(filePath);
    return file.exists(); // ����ļ��Ƿ����
}
void MainWindow::setStartDuration() {
    QDialog setTimeDialog(this);
    setTimeDialog.setWindowTitle("����");
    QVBoxLayout layout(&setTimeDialog);
    QLineEdit inputTextEdit(&setTimeDialog);
    QPushButton saveButton("����", &setTimeDialog);
    layout.addWidget(&inputTextEdit);
    layout.addWidget(&saveButton);

    QMessageBox::information(this, "Information", "ȡ����������������0������ʱ������0��5000����λ���롣��������Ĭ��Ϊ4800");

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
                QMessageBox::information(this, "Saved", "����ɹ�!������Ӧ�ú���ִ����������");
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
    settingsDialog.setWindowTitle("����");
    QVBoxLayout layout(&settingsDialog);
    QLineEdit inputTextEdit(&settingsDialog);
    QPushButton saveButton("����", &settingsDialog);
    QPushButton locateButton("��λ", &settingsDialog);

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
                QMessageBox::information(this, "Saved", "����ɹ�!������Ӧ�ú���ִ����������");
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

    switch (QMessageBox::question(this, tr("Question��Ϣ��"),
        tr("���Ҫ�˳���"),
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
    setWindowTitle("ԭ�񻻷���");
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


    //������
    menuBar = new QMenuBar(this);
    settingsMenu = menuBar->addMenu("����");
    saveAction = settingsMenu->addAction("����ԭ��������·��");
    timeAction = settingsMenu->addAction("������������ʱ��");
    connect(saveAction, &QAction::triggered, this, &MainWindow::showSettingsDialog);
    connect(timeAction, &QAction::triggered, this, &MainWindow::setStartDuration);

    setMenuBar(menuBar);

    btn1 = new QPushButton("��鵱ǰ���", this);
    btn1->move(450, 100);
    btn1->resize(200, 80);
    btn1->setStyleSheet("font-family:'Microsoft YaHei';background-color:#c0ffe5;");
    btn2 = new QPushButton("�ٷ�תB��", this);
    btn2->move(450, 250);
    btn2->resize(200, 80);
    btn2->setStyleSheet("font-family:'Microsoft YaHei';background-color:#c0ffe5;");
    btn3 = new QPushButton("B��ת�ٷ�", this);
    btn3->move(450, 400);
    btn3->resize(200, 80);
    btn3->setStyleSheet("font-family:'Microsoft YaHei';background-color:#c0ffe5;");
    btn4 = new QPushButton("�˳�", this);
    btn4->move(450, 550);
    btn4->resize(200, 80);
    btn4->setStyleSheet("font-family:'Microsoft YaHei';background-color:#c0ffe5;");
    btn5 = new QPushButton("��������", this);
    btn5->move(450, 700);
    btn5->resize(200, 80);
    btn5->setStyleSheet("font-family:'Microsoft YaHei';background-color:#c0ffe5;");

    imageLabel = new QLabel(this);
    imageLabel->move(1000, 300);
    imageLabel->setScaledContents(true);
    imageLabel->resize(300, 300);

    if (img.load(":/gif/C:/Users/Soggy/Desktop/G/ayaka.png"))
        imageLabel->setPixmap(QPixmap::fromImage(img));

    //��ȡ·��
    QFile file("input.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) { // ���ļ�
        QTextStream in(&file);
        fileFullPath = in.readLine(); // ��ȡ��һ���ı������ļ�����·��
        file.close(); // �ر��ļ�
        QFileInfo fileInfo(fileFullPath);
        directoryPath = fileInfo.dir().absolutePath(); // ��ȡ�ļ�����Ŀ¼�ľ���·��
    }
    else {
        // �����ļ���ʧ�ܵ����
        QMessageBox::information(this, tr("Information��Ϣ��"), tr("�ļ���ȡʧ��"));// "�ļ���ȡʧ��"
    }
    QDir Directory(directoryPath); // ����g�ļ��е�QDirʵ��
    QString subDirectoryPath1 = QDir(directoryPath).absoluteFilePath("Genshin Impact Game"); // g�ļ��е�·��
    QDir subDirectory1(subDirectoryPath1); // ����g�ļ��е�QDirʵ��
    QString subDirectoryPath2 = QDir(directoryPath).absoluteFilePath("Genshin Impact Game/YuanShen_Data/Plugins"); // p�ļ��е�·��
    QDir subDirectory2(subDirectoryPath2); // ����p�ļ��е�QDirʵ��

    filePath1 = Directory.filePath("config.ini"); // config.ini�ļ�������·��
    filePath2 = subDirectory1.filePath("config.ini"); // config.ini�ļ�������·��
    filePath3 = subDirectory2.filePath("PCGameSDK.dll");
    filePath4 = subDirectory2.filePath("PCGameSDK.dllsc");

    //�����湦��ʵ��
    connect(btn4, &QPushButton::clicked, [=]() {showQuestionMsg();});

    connect(btn1, &QPushButton::clicked, [=]() {
        if (checkFileExist(subDirectoryPath2, "PCGameSDK.dll")) {
            QMessageBox::information(this, tr("Information��Ϣ��"),
                tr("��ǰΪB��"));// �ļ�����
        }
        else if(checkFileExist(subDirectoryPath2, "license.txt")){
            QMessageBox::information(this, tr("Information��Ϣ��"),
                tr("��ǰΪ�ٷ�"));// �ļ�������
        }
        else
            QMessageBox::information(this, tr("Information��Ϣ��"),tr("δ��⵽Ӧ���ļ������鶨λ�Ƿ���ȷ"));// �ļ�������
        if (img.load(":/gif/C:/Users/Soggy/Desktop/G/kurumi.png"))
            imageLabel->setPixmap(QPixmap::fromImage(img));
        });

    connect(btn2, &QPushButton::clicked, [=]() {
        if (!checkFileExist(directoryPath, "config.ini")) {
            QMessageBox::warning(this, tr("Warning��Ϣ��"),
                tr("δ��⵽Ӧ���ļ������鶨λ�Ƿ���ȷ"));// �ļ�������
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
                QMessageBox::information(this, tr("Information��Ϣ��"),
                    tr("�ļ��޸ĳɹ�"));
            }
            else {
                QMessageBox::information(this, tr("Information��Ϣ��"),
                    tr("�ļ��޸�ʧ��"));
            }
        }
        });

    connect(btn3, &QPushButton::clicked, [=]() {
        if (!checkFileExist(directoryPath, "config.ini")) {
            QMessageBox::warning(this, tr("Warning��Ϣ��"),
                tr("δ��⵽Ӧ���ļ������鶨λ�Ƿ���ȷ"));// �ļ�������
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
                QMessageBox::information(this, tr("Information��Ϣ��"),
                    tr("�ļ��޸ĳɹ�"));
            }
            else {
                QMessageBox::information(this, tr("Information��Ϣ��"),
                    tr("�ļ��޸�ʧ��"));
            }
        }
        });
    connect(btn5, &QPushButton::clicked, [=]() {
        QPalette currentPalette = this->palette();
        if (currentPalette.window() == pa1.window()) {
            // ��ǰʹ�õĵ�ɫ��Ϊ pa1
            resize(1440, 810);
            this->setPalette(pa2);
        }
        else if (currentPalette.window() == pa2.window()) {
            // ��ǰʹ�õĵ�ɫ��Ϊ pa2
            resize(1490, 840);
            this->setPalette(pa1);
        }
        else {
            // δ֪�ĵ�ɫ��
            QMessageBox::warning(this, tr("Warning��Ϣ��"),
                tr("��ɫ����ô���"));
        }
        });

    //�����Ż�
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
