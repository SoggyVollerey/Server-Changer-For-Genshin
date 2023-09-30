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

    //����
    QMovie movie;
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + "/start.gif";
    QString filePath2 = ":/gif/C:/Users/Soggy/Desktop/G/start.gif";
    movie.setFileName(filePath2);
    QLabel label;
    label.setGeometry(700, 300, 1440, 840);
    label.setMovie(&movie);
    label.setScaledContents(true);          //����Ӧ����
    label.setWindowFlags(Qt::FramelessWindowHint);//ȥ���߿�

    movie.start();
    label.show();

    QFile file("in.txt");
    int b = 4800;
    bool ok=0;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) { // ���ļ�
        QTextStream in(&file);
        QString dur = in.readLine(); // ��ȡ��һ���ı������ļ�����·��
        b = dur.toInt(&ok);
        file.close(); // �ر��ļ�
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
