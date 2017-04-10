#include "stdafx.h"
#include "MapView.h"
#include "CityDetailsView.h"

MapView::MapView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setMouseTracking(true);
	mapScene = new QGraphicsScene();
	mapImage = QImage("Resources\\map.png");
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(mapImage));
	mapScene->addItem(item);
	ui.mapGraphicsView->setScene(mapScene);
	ui.mapGraphicsView->scale(0.5, 0.5);
	selectedCityIndex = 0;
	cityDetailsView = new CityDetailsView(this);
	cityDetailsView->hide();
}

MapView::~MapView()
{
}

void MapView::mouseMoveEvent(QMouseEvent *event)
{

}

void MapView::mousePressEvent(QMouseEvent *event)
{
	deselectCity();
}


void MapView::update(const pan::Map& map)
{
	using namespace pan;
	for (auto item : cityItems){
		mapScene->removeItem(item);
		delete item;
	}
	for (auto lines : cityConnections){
		for (auto line : lines){
			mapScene->removeItem(line.get());
		}
	}
	cityConnections.clear();
	cityItems.clear();
	Map::CityIndexIterator ai, ai_end;
	for (boost::tie(ai, ai_end) = map.cities(); ai != ai_end; ++ai){
		const City& c = map[*ai];
		addItem(c, *ai);
	}

	Map::ConnectionIterator ei, ei_end;
	for (boost::tie(ei, ei_end) = map.connections(); ei != ei_end; ++ei){
		CityIndex sourceIndex = map.source(ei);
		CityIndex targetIndex = map.target(ei);
		CityItemGroup* sourceItem = cityItems[sourceIndex];
		CityItemGroup* targetItem = cityItems[targetIndex];
		QLineF line(sourceItem->center(), targetItem->center());
		std::shared_ptr<QGraphicsLineItem> lineItem(new QGraphicsLineItem(line));
		lineItem->setPen(QPen(QBrush(Qt::gray), 3.0));
		mapScene->addItem(lineItem.get());
		cityConnections[sourceIndex].push_back(lineItem);
		cityConnections[targetIndex].push_back(lineItem);
	}
	mapScene->update();
}

void MapView::update(const pan::City& city, pan::CityIndex index)
{
	auto oldItem = cityItems.find(index);
	if (oldItem == cityItems.end()){
		addItem(city, index); 
	}
	else{
		oldItem.value()->update(city);
		oldItem.value()->setIndex(index);
	}
	mapScene->update();
}

void MapView::addItem(const pan::City& city, pan::CityIndex index)
{
	CityItemGroup* item = new CityItemGroup();
	item->setIndex(index);
	mapScene->addItem(item);
	cityItems[index] = item;
	item->update(city);
	item->setPos(mapImage.size().width() * city.getXpos(), mapImage.size().height() * city.getYpos());
	connect(item, SIGNAL(cityItemSelected(pan::CityIndex)), this, SLOT(on_cityItemSelected(pan::CityIndex)));
	connect(item, SIGNAL(cityDetailsSelected(pan::CityIndex)), this, SLOT(on_cityDetailsSelected(pan::CityIndex)));
}

void MapView::deselectCity()
{
	for (auto line : cityConnections[selectedCityIndex]){
		line->setPen(QPen(QBrush(Qt::gray), 3.0));
	}
	cityDetailsView->hide();
}

void MapView::on_cityItemSelected(pan::CityIndex index)
{
	qDebug() << "Selected " << index;
	deselectCity();
	selectedCityIndex = index;
	for (auto line : cityConnections[selectedCityIndex]){
		line->setPen(QPen(QBrush(Qt::green), 8.0));
	}
	Q_EMIT cityItemSelected(index);
}

void MapView::on_cityDetailsSelected(pan::CityIndex index)
{
	cityDetailsView->update(cityItems[index]->getCity());
	cityDetailsView->setWindowFlags(Qt::WindowStaysOnTopHint);
	cityDetailsView->show();
}

