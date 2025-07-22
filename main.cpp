#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("SCIoI");
    QCoreApplication::setOrganizationDomain("www.scioi.de");
    QCoreApplication::setApplicationName("LARS ver2.2");

    QApplication a(argc, argv);

    std::cout << "*** © Science of Intelligence, Project 27, Mohsen Raoufi ***" << std::endl;
    std::cout << "***** Light Augmented Reality for Swarm Systems (LARS) *****" << std::endl;
    std::cout << "*********************** Version: 2.2 ***********************" << std::endl;

    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette p;
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Base, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(50, 153, 168));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    p.setColor(QPalette::Foreground, QColor(255,255,255));
    p.setColor(QPalette::Text, QColor(255,255,255));
    a.setPalette(p);

//    a.setWindowIcon(QIcon(""));
//    a.setWindowIcon(QIcon("Files/LARS_Logo.png")); // KilobotHeter.png"));
    a.setWindowIcon(QIcon(":/Files/LARS_Logo.png")); // /KilobotHeter.png"));          // To set the icon of the application

    MainWindow w;

    w.show();

    return a.exec();
}
