/********************************************************************************
** Form generated from reading UI file 'pandemic.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANDEMIC_H
#define UI_PANDEMIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "MapView.h"

QT_BEGIN_NAMESPACE

class Ui_PandemicClass
{
public:
    QWidget *centralWidget;
    MapView *widget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PandemicClass)
    {
        if (PandemicClass->objectName().isEmpty())
            PandemicClass->setObjectName(QStringLiteral("PandemicClass"));
        PandemicClass->resize(1330, 779);
        centralWidget = new QWidget(PandemicClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new MapView(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 20, 1200, 675));
        PandemicClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PandemicClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PandemicClass->setStatusBar(statusBar);

        retranslateUi(PandemicClass);

        QMetaObject::connectSlotsByName(PandemicClass);
    } // setupUi

    void retranslateUi(QMainWindow *PandemicClass)
    {
        PandemicClass->setWindowTitle(QApplication::translate("PandemicClass", "Pandemic", 0));
    } // retranslateUi

};

namespace Ui {
    class PandemicClass: public Ui_PandemicClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANDEMIC_H
