#include "mainwindow.h"
#include <QApplication>

/*!
 * \brief Entry point of the program. First function to execute.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
