#include "stdafx.h"
#include "CityItem.h"

QRectF CityItem::boundingRect() const
{
	return QRectF(0, 0, 75, 75);
}

void CityItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QRectF rect = boundingRect();
	QBrush brush(RegionColors[city.getRegion()]);
	//painter->fillRect(rect, brush);
	QRectF bRect = boundingRect();
	QPointF center = bRect.center();
	QPainterPath ellipsePath = circle(center, bRect.width() / 2);
	painter->fillPath(ellipsePath, QBrush(RegionColors[city.getRegion()]));
	painter->drawEllipse(center, bRect.width() / 2, bRect.height() / 2);
	std::size_t cubeCount = city.getCubes(city.getRegion());
	if (cubeCount >= 1){
		QPainterPath circlePath = circle(QPointF(center.x(), center.y() - 3 * bRect.width() / 4), bRect.width() / 4);
		painter->fillPath(circlePath, QBrush(RegionColors[city.getRegion()]));
	}
	if (cubeCount >= 2){
		QPainterPath circlePath = circle(QPointF(center.x() - 3 * bRect.width() / 4, center.y()), bRect.width() / 4);
		painter->fillPath(circlePath, QBrush(RegionColors[city.getRegion()]));
	}
	if (cubeCount >= 3){
		QPainterPath circlePath = circle(QPointF(center.x() + 3 * bRect.width() / 4, center.y()), bRect.width() / 4);
		painter->fillPath(circlePath, QBrush(RegionColors[city.getRegion()]));
	}
}


void CityItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	Q_EMIT cityItemSelected(index);
	QGraphicsItem::mousePressEvent(event);
}

void CityItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
}

void CityItem::update(const pan::City& city)
{
	this->city = city;
	QGraphicsItem::update();
}

void CityItem::setIndex(pan::CityIndex index)
{
	this->index = index;
}

QPointF CityItem::center() const
{
	QPointF pos = this->pos();
	pos.setX(pos.x() + this->boundingRect().width() / 2.0);
	pos.setY(pos.y() + this->boundingRect().height() / 2.0);
	return pos;
}

QPainterPath CityItem::circle(QPointF center, int radius) const
{
	QPainterPath ellipsePath(QPoint(0, 0));
	ellipsePath.addEllipse(center, radius, radius);
	return ellipsePath;
}