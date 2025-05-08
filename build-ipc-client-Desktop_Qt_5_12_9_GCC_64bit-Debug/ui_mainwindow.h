/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widgetTop;
    QWidget *widgetMiddle;
    QHBoxLayout *horizontalLayout;
    QWidget *widgetView;
    QWidget *widgetPTZ;
    QWidget *widgetBotton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QRadioButton *radioBtn1;
    QRadioButton *radioBtn4;
    QRadioButton *radioBtn9;
    QRadioButton *radioBtn16;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1114, 648);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widgetTop = new QWidget(centralwidget);
        widgetTop->setObjectName(QString::fromUtf8("widgetTop"));

        verticalLayout->addWidget(widgetTop);

        widgetMiddle = new QWidget(centralwidget);
        widgetMiddle->setObjectName(QString::fromUtf8("widgetMiddle"));
        horizontalLayout = new QHBoxLayout(widgetMiddle);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widgetView = new QWidget(widgetMiddle);
        widgetView->setObjectName(QString::fromUtf8("widgetView"));

        horizontalLayout->addWidget(widgetView);

        widgetPTZ = new QWidget(widgetMiddle);
        widgetPTZ->setObjectName(QString::fromUtf8("widgetPTZ"));

        horizontalLayout->addWidget(widgetPTZ);

        horizontalLayout->setStretch(0, 4);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addWidget(widgetMiddle);

        widgetBotton = new QWidget(centralwidget);
        widgetBotton->setObjectName(QString::fromUtf8("widgetBotton"));
        horizontalLayout_2 = new QHBoxLayout(widgetBotton);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(widgetBotton);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        radioBtn1 = new QRadioButton(widgetBotton);
        radioBtn1->setObjectName(QString::fromUtf8("radioBtn1"));

        horizontalLayout_2->addWidget(radioBtn1);

        radioBtn4 = new QRadioButton(widgetBotton);
        radioBtn4->setObjectName(QString::fromUtf8("radioBtn4"));

        horizontalLayout_2->addWidget(radioBtn4);

        radioBtn9 = new QRadioButton(widgetBotton);
        radioBtn9->setObjectName(QString::fromUtf8("radioBtn9"));

        horizontalLayout_2->addWidget(radioBtn9);

        radioBtn16 = new QRadioButton(widgetBotton);
        radioBtn16->setObjectName(QString::fromUtf8("radioBtn16"));

        horizontalLayout_2->addWidget(radioBtn16);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout_2->setStretch(0, 5);
        horizontalLayout_2->setStretch(1, 4);
        horizontalLayout_2->setStretch(2, 4);
        horizontalLayout_2->setStretch(3, 4);
        horizontalLayout_2->setStretch(4, 4);
        horizontalLayout_2->setStretch(5, 30);

        verticalLayout->addWidget(widgetBotton);

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(1, 25);
        verticalLayout->setStretch(2, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1114, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "view grid", nullptr));
        radioBtn1->setText(QApplication::translate("MainWindow", "1", nullptr));
        radioBtn4->setText(QApplication::translate("MainWindow", "4", nullptr));
        radioBtn9->setText(QApplication::translate("MainWindow", "9", nullptr));
        radioBtn16->setText(QApplication::translate("MainWindow", "16", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
