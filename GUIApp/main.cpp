#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if(w.checkPassword())
    {
        if(true)
        {
         w.show();
        return a.exec();
        }
        else
        {
            return false;
        }

    }

    return 0;
}
