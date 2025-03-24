#include "widget.h"
#include <QApplication>
#include "Eigen/Dense"
#include <unsupported/Eigen/FFT>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    Eigen::FFT<double> fft;

    return a.exec();
}
