#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //Главная функция создающая объект описанного окна, а также отображающая его
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Весы");
    w.show();
    return a.exec();
}
