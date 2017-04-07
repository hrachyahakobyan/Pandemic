#pragma once

#include <QObject>

class CityItemGroup : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
public:
	CityItemGroup();
	~CityItemGroup();
	QRectF boundingRect() const;
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
	void update(const pan::City& city);
	void setIndex(pan::CityIndex index);
	const pan::City& getCity() const { return city; }
	const pan::CityIndex getIndex() const { return index; }
	QPointF center() const;
Q_SIGNALS:
	void cityItemSelected(pan::CityIndex index);
	void cityDetailsSelected(pan::CityIndex index);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
	pan::CityIndex index;
	pan::City city;
	QPainterPath circle(QPointF center, int radius) const;
	QVector<QPainterPath> diseaseCircles;
	QVector<QGraphicsPixmapItem*> playerPawns;
	QGraphicsPixmapItem* stationItem;
	void clearAll();
};
