#include "MapView.h"

MapView::MapView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	mapImage.load("Resources/map.png");
	mapScene = new QGraphicsScene(this);
	mapScene->addPixmap(QPixmap::fromImage(mapImage));
	mapScene->setSceneRect(mapImage.rect());
	
	ui.mapView->setScene(mapScene);
	qreal scaleFactor = 1200.f / mapImage.size().width();
	ui.mapView->scale(scaleFactor, scaleFactor);
}

MapView::~MapView()
{

}
