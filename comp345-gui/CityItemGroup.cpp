#include "stdafx.h"
#include "CityItemGroup.h"
#include "Resources.h"
#include <math.h>


CityItemGroup::CityItemGroup() :
stationItem(NULL), nameItem(NULL), cityIcon(NULL)
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
	if (nameItem){
		delete nameItem;
		nameItem = NULL;
	}
	if (cityIcon){
		delete cityIcon;
		cityIcon = NULL;
	}
}

QRectF CityItemGroup::boundingRect() const
{
	return QRectF(0, 0, 75, 75);
}

void CityItemGroup::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QGraphicsItemGroup::paint(painter, option, widget);
	QRectF rect = boundingRect();
	QBrush brush(RegionColors[city.getRegion()]);
	QRectF bRect = boundingRect();
	QPointF center = bRect.center();

	int d0 = city.getCubes(0);
	int d1 = city.getCubes(1);
	int d2 = city.getCubes(2);
	int d3 = city.getCubes(3);

	int circles = std::max(std::max(d0, d1), std::max(d2, d3));

	for (int i = 0; i < circles; i++){
		std::vector<bool> diseases(4);
		if (d0 > 0) {
			diseases[0] = true;
			d0--;
		}
		if (d1 > 0){
			diseases[1] = true;
			d1--;
		}
		if (d2 > 0) {
			diseases[2] = true;
			d2--;
		}
		if (d3 > 0){
			diseases[3] = true;
			d3--;
		}
		drawPie(painter, diseaseCircleRects[i], diseases);
	}
}

void CityItemGroup::drawPie(QPainter* painter, QRect rect, std::vector<bool> diseases)
{
	int sum = 0;
	for (auto d : diseases){
		sum += int(d);
	}
	double jump = 360.0 / sum;
	double angle = 0.0;
	for (std::size_t i = 0; i < sum; i++){
		pan::DiseaseType current = 0;
		for (std::size_t j = 0; j < diseases.size(); j++){
			if (diseases[j]){
				current = static_cast<pan::DiseaseType>(j);
				diseases[j] = false;
				break;
			}
		}
		painter->setPen(QPen(RegionColors[current]));
		painter->setBrush(QBrush(RegionColors[current]));
		painter->drawPie(rect, int(angle) * 16, int(jump) * 16);
		angle += jump;
	}
}


void CityItemGroup::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		Q_EMIT cityItemSelected(index);
		Resources::playClick();
	}
	else if (event->button() == Qt::RightButton)
	{
		Q_EMIT cityDetailsSelected(index);
		Resources::playClick();
	}
}

void CityItemGroup::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
}

void CityItemGroup::update(const pan::City& city)
{
	clearAll();
	this->city = city;
	QRectF bRect = boundingRect();
	QPointF center = bRect.center();

	if (!cityIcon){
		cityIcon = new QGraphicsPixmapItem();
		this->addToGroup(cityIcon);
	}
	cityIcon->setPixmap(Resources::getCityIconForRegion(city.getRegion()).scaled(bRect.width(), bRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	cityIcon->setPos(bRect.topLeft());
	diseaseCircleRects.clear();
	std::size_t cubes0 = city.getCubes(0);
	std::size_t cubes1 = city.getCubes(1);
	std::size_t cubes2 = city.getCubes(2);
	std::size_t cubes3 = city.getCubes(3);
	std::size_t cubes = std::max(std::max(cubes0, cubes1), std::max(cubes2, cubes3));

	double angle = 0.0;
	double increment = M_PI * 2 / cubes;
	for (std::size_t i = 0; i < cubes; i++){
		QPoint pos(center.x(), center.y());
		pos.setX(pos.x() + 3 * bRect.width() / 4 * std::cos(angle) - bRect.width() / 4);
		pos.setY(pos.y() + 3 * bRect.width() / 4 * std::sin(angle) - bRect.width() / 4);
		diseaseCircleRects.push_back(QRect(pos, QSize(bRect.width() / 2, bRect.width() / 2)));
		angle += increment;
	}
	if (city.researchStation){
		if (stationItem == NULL){
			stationItem = new QGraphicsPixmapItem(Resources::stationPawnPixmap().scaled(bRect.width(), bRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
		}
		this->addToGroup(stationItem);
		stationItem->setPos(bRect.topLeft());
	}
	else {
		if (stationItem){
			this->removeFromGroup(stationItem);
		}
	}
	angle = 0.0;
	increment = M_PI * 2 / city.getPlayers().size();
	for (const auto& player : city.getPlayers()){
		QPixmap pawnPix = Resources::pawnForRole(player->getRole().role).scaled(bRect.width(), bRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
		QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pawnPix);
		this->addToGroup(item);
		QPointF p = center;
		p.setX(p.x() + bRect.width() / 4 * std::cos(angle));
		p.setY(p.y() + bRect.height() / 4 * std::sin(angle));
		playerPawns.push_back(item);
		item->setPos(QPointF(p.x() - bRect.width() / 2, p.y() - bRect.height() /2));
		angle += increment;
	}
	
	if (!nameItem){
		nameItem = new QGraphicsTextItem();
		this->addToGroup(nameItem);
		//nameItem->setTextWidth(bRect.width());
		nameItem->setFont(QFont("Times", 12, QFont::Bold));
		nameItem->setDefaultTextColor(QColor(255, 255, 255));
		nameItem->setPos(bRect.bottomLeft());
	}
	nameItem->setPlainText(QString::fromStdString(city.getName()));
	//QGraphicsItem::update();
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
