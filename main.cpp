#include "mainwindow.h"
//#include "lines.h"
#include "optimizeLogic.h"
#include "dialogparameters.h"
#include <QApplication>
#include <qlocale.h>

int main(int argc, char *argv[])
{
    QLocale curLocale(QLocale("en_EN"));
    QLocale::setDefault(curLocale);
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    w.show();
//    return a.exec();

//    Lines window;

//   window.resize(WINDOW_WIDTH, WINDOW_HEIGHT);
//    window.setWindowTitle("Lines");
//    window.show();

    smoothFunction<double, vector<double>> f;

    return a.exec();
}
