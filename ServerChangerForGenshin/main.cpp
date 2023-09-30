#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <qmovie.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //启动
    QMovie movie;
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + "/start.gif";
    QString filePath2 = ":/gif/C:/Users/Soggy/Desktop/G/start.gif";
    movie.setFileName(filePath2);
    QLabel label;
    label.setGeometry(700, 300, 1440, 840);
    label.setMovie(&movie);
    label.setScaledContents(true);          //自适应窗口
    label.setWindowFlags(Qt::FramelessWindowHint);//去除边框

    movie.start();
    label.show();

    QFile file("in.txt");
    int b = 4800;
    bool ok=0;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) { // 打开文件
        QTextStream in(&file);
        QString dur = in.readLine(); // 读取第一行文本，即文件完整路径
        b = dur.toInt(&ok);
        file.close(); // 关闭文件
    }
    if (ok)
        ;
    else
        b=4800;

    QTime t;
    t.start();
    while (t.elapsed()<b)
    {
        QApplication::processEvents();
    }


    MainWindow w;
    w.show();

    label.close();
    return a.exec();
}
