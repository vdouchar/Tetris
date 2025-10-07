#include <QApplication>

#include "configwindow.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    ConfigWindow myWindow {};

    myWindow.show();

    return application.exec();
}
