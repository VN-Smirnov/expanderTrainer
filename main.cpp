#include "mytrainer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTrainer w;
    w.show();
    return a.exec();
}
