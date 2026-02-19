/********************************************************************************
** Form generated from reading UI file 'arenaWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARENAWINDOW_H
#define UI_ARENAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ArenaWindow
{
public:
    QWidget *centralwidget;
    QLabel *VVal_label;
    QFrame *widgets_frame;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QWidget *gridLayoutWidget;
    QGridLayout *gridRender;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ArenaWindow)
    {
        if (ArenaWindow->objectName().isEmpty())
            ArenaWindow->setObjectName(QString::fromUtf8("ArenaWindow"));
        ArenaWindow->setWindowModality(Qt::NonModal);
        ArenaWindow->resize(1900, 1200);
        ArenaWindow->setMouseTracking(true);
        ArenaWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        centralwidget = new QWidget(ArenaWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMouseTracking(true);
        VVal_label = new QLabel(centralwidget);
        VVal_label->setObjectName(QString::fromUtf8("VVal_label"));
        VVal_label->setGeometry(QRect(490, -10, 67, 19));
        VVal_label->setStyleSheet(QString::fromUtf8("background-color: rgb(115, 210, 22);\n"
"color: rgb(0, 0, 0);"));
        widgets_frame = new QFrame(centralwidget);
        widgets_frame->setObjectName(QString::fromUtf8("widgets_frame"));
        widgets_frame->setGeometry(QRect(30, 20, 1001, 651));
        widgets_frame->setFrameShape(QFrame::StyledPanel);
        widgets_frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(widgets_frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 264, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(2, 0, 1881, 1179));
        gridRender = new QGridLayout(gridLayoutWidget);
        gridRender->setObjectName(QString::fromUtf8("gridRender"));
        gridRender->setContentsMargins(0, 0, 0, 0);
        ArenaWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ArenaWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1900, 23));
        ArenaWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ArenaWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ArenaWindow->setStatusBar(statusbar);

        retranslateUi(ArenaWindow);

        QMetaObject::connectSlotsByName(ArenaWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ArenaWindow)
    {
        ArenaWindow->setWindowTitle(QCoreApplication::translate("ArenaWindow", "ArenaWindow", nullptr));
        VVal_label->setText(QCoreApplication::translate("ArenaWindow", "V value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ArenaWindow: public Ui_ArenaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARENAWINDOW_H
