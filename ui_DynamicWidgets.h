/********************************************************************************
** Form generated from reading UI file 'DynamicWidgets.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DYNAMICWIDGETS_H
#define UI_DYNAMICWIDGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DynamicWidgetsClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *addWidget_button;
    QFrame *widgets_frame;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DynamicWidgetsClass)
    {
        if (DynamicWidgetsClass->objectName().isEmpty())
            DynamicWidgetsClass->setObjectName(QString::fromUtf8("DynamicWidgetsClass"));
        DynamicWidgetsClass->resize(307, 400);
        centralWidget = new QWidget(DynamicWidgetsClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addWidget_button = new QPushButton(centralWidget);
        addWidget_button->setObjectName(QString::fromUtf8("addWidget_button"));
        QFont font;
        font.setPointSize(12);
        addWidget_button->setFont(font);

        verticalLayout->addWidget(addWidget_button);

        widgets_frame = new QFrame(centralWidget);
        widgets_frame->setObjectName(QString::fromUtf8("widgets_frame"));
        widgets_frame->setFrameShape(QFrame::StyledPanel);
        widgets_frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(widgets_frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 264, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout->addWidget(widgets_frame);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        DynamicWidgetsClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DynamicWidgetsClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 307, 21));
        DynamicWidgetsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DynamicWidgetsClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DynamicWidgetsClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DynamicWidgetsClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DynamicWidgetsClass->setStatusBar(statusBar);

        retranslateUi(DynamicWidgetsClass);

        QMetaObject::connectSlotsByName(DynamicWidgetsClass);
    } // setupUi

    void retranslateUi(QMainWindow *DynamicWidgetsClass)
    {
        DynamicWidgetsClass->setWindowTitle(QCoreApplication::translate("DynamicWidgetsClass", "DynamicWidgets", nullptr));
        addWidget_button->setText(QCoreApplication::translate("DynamicWidgetsClass", "Click to Add Widget!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DynamicWidgetsClass: public Ui_DynamicWidgetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DYNAMICWIDGETS_H
