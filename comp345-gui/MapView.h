#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "ui_MapView.h"
#include "CityItemGroup.h"

class CityDetailsView;

/**
*	@class A widget to display the game map
*	@author Hrachya Hakobyan
*/
class MapView : public QWidget
{
	Q_OBJECT

public:
	MapView(QWidget *parent = 0);
	~MapView();

	void update(const pan::Map& map);
	void update(const pan::City& city, pan::CityIndex index);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
public Q_SLOTS:
	void on_cityItemSelected(pan::CityIndex);
	void on_cityDetailsSelected(pan::CityIndex);
Q_SIGNALS:
	void cityItemSelected(pan::CityIndex index);
private:
	Ui::MapView ui;
	QGraphicsScene* mapScene;
	QImage mapImage;
	std::size_t currentCity;
	QMap<pan::CityIndex, CityItemGroup*> cityItems;
	QMap<pan::CityIndex, QVector<std::shared_ptr<QGraphicsLineItem>>> cityConnections;
	pan::CityIndex selectedCityIndex;
	CityDetailsView* cityDetailsView;
	void deselectCity();
	void addItem(const pan::City& c, pan::CityIndex index);
};

#endif // MAPVIEW_H
