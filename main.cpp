#include "MainWindow.hpp"
#include <QApplication>

#include <QtQml>
#include "Field.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qmlRegisterType<Field>("GameComponents", 1, 0, "Field");

    return a.exec();
}
