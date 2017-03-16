/********************************************************************************
** Form generated from reading UI file 'MapView.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPVIEW_H
#define UI_MAPVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapView
{
public:
    QHBoxLayout *horizontalLayout;
    QGraphicsView *mapView;

    void setupUi(QWidget *MapView)
    {
        if (MapView->objectName().isEmpty())
            MapView->setObjectName(QStringLiteral("MapView"));
        MapView->resize(888, 701);
        horizontalLayout = new QHBoxLayout(MapView);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        mapView = new QGraphicsView(MapView);
        mapView->setObjectName(QStringLiteral("mapView"));

        horizontalLayout->addWidget(mapView);


        retranslateUi(MapView);

        QMetaObject::connectSlotsByName(MapView);
    } // setupUi

    void retranslateUi(QWidget *MapView)
    {
        MapView->setWindowTitle(QApplication::translate("MapView", "MapView", 0));
    } // retranslateUi

};

namespace Ui {
    class MapView: public Ui_MapView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPVIEW_H
