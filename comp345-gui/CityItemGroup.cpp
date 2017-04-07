#include "stdafx.h"
#include "CityItemGroup.h"
#include "Resources.h"
#include <math.h>


CityItemGroup::CityItemGroup() :
stationItem(NULL)
{
}

CityItemGroup::~CityItemGroup()
{
	clearAll();
}

void CityItemGroup::clearAll()
{
	for (auto item : playerPawns){
		this->removeFromGroup(item);
		delete item;
	}
	playerPawns.clear();
	if (stationItem){
		delete stationItem;
		stationItem = NULL;
	}
}

QRectF CityItemGroup::boundingRect() const
{
	return QRectF(0, 0, 75, 75);
}

void CityItemGroup::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QRectF rect = boundingRect();
	QBrush brush(RegionColors[city.getRegion()]);
	QRectF bRect = boundingRect();
	QPointF center = bRect.center();
	QPainterPath ellipsePath = circle(center, bRect.width() / 2);
	painter->fillPath(ellipsePath, QBrush(RegionColors[city.getRegion()]));
	painter->drawEllipse(center, bRect.width() / 2, bRect.height() / 2);
	for (const auto& c : diseaseCircles){
		painter->fillPath(c, QBrush(RegionColors[city.getRegion()]));
	}
}


void CityItemGroup::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
		Q_EMIT cityItemSelected(index);
	else if (event->button() == Qt::RightButton)
		Q_EMIT cityDetailsSelected(index);
}

void CityItemGroup::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
}

void CityItemGroup::update(const pan::City& city)
{
	clearAll();
	this->city = city;
	diseaseCircles.clear();
	std::size_t cubes = city.getCubes(city.getRegion());
	QRectF bRect = boundingRect();
	QPointF center = bRect.center();
	double angle = 0.0;
	double increment = M_PI * 2 / cubes;
	for (std::size_t i = 0; i < cubes; i++){
		QPointF pos = center;
		pos.setX(pos.x() + 3 * bRect.width() / 4 * std::cos(angle));
		pos.setY(pos.y() + 3 * bRect.width() / 4 * std::sin(angle));
		diseaseCircles.push_back(circle(pos, bRect.width() / 4));
		angle += increment;
	}
	angle = 0.0;
	increment = M_PI * 2 / city.getPlayers().size();
	for (const auto& player : city.getPlayers()){
		QPixmap pawnPix = Resources::pawnForRole(player->getRole().role);
		QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pawnPix);
		this->addToGroup(item);
		QPointF p = center;
		p.setX(p.x() + bRect.width() / 4 * std::cos(angle));
		p.setY(p.y() + bRect.height() / 4 * std::sin(angle));
		playerPawns.push_back(item);
		item->setPos(p);
		angle += increment;
	}
	if (city.researchStation){
		if (stationItem == NULL){
			stationItem = new QGraphicsPixmapItem(Resources::stationPawnPixmap().scaled(bRect.width(), bRect.height(), Qt::KeepAspectRatio));
		}
		this->addToGroup(stationItem);
		stationItem->setPos(center);
	}
	else {
		if (stationItem){
			this->removeFromGroup(stationItem);
		}
	}
	QGraphicsItem::update();
}

void CityItemGroup::setIndex(pan::CityIndex index)
{
	this->index = index;
}

QPointF CityItemGroup::center() const
{
	QPointF pos = this->pos();
	pos.setX(pos.x() + this->boundingRect().width() / 2.0);
	pos.setY(pos.y() + this->boundingRect().height() / 2.0);
	return pos;
}

QPainterPath CityItemGroup::circle(QPointF center, int radius) const
{
	QPainterPath ellipsePath(QPoint(0, 0));
	ellipsePath.addEllipse(center, radius, radius);
	return ellipsePath;
}
