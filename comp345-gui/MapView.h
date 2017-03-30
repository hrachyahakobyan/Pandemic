#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "ui_MapView.h"
#include "CityItem.h"

class MapView : public QWidget
{
	Q_OBJECT

public:
	MapView(QWidget *parent = 0);
	~MapView();

	void update(const pan::Map& map);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
public Q_SLOTS:
	void on_cityItemSelected(pan::CityIndex);
Q_SIGNALS:
	void cityItemSelected(pan::CityIndex index);
private:
	Ui::MapView ui;
	QGraphicsScene* mapScene;
	QImage mapImage;
	std::size_t currentCity;
	QMap<pan::CityIndex, CityItem*> cityItems;
	QMap<pan::CityIndex, QVector<QGraphicsLineItem*>> cityConnections;
	pan::CityIndex selectedCityIndex;
};

#endif // MAPVIEW_H
