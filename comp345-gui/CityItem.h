#ifndef CITYITEM_H
#define CITYITEM_H

static const QMap<pan::RegionIndex, Qt::GlobalColor> RegionColors{
	{0, Qt::blue },
	{1, Qt::yellow },
	{2, Qt::black},
	{3, Qt::red}
};

class CityItem : public QGraphicsObject
{
	Q_OBJECT
public:
	QRectF boundingRect() const;
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
	void update(const pan::City& city);
	void setIndex(pan::CityIndex index);
	const pan::CityIndex getIndex() const { return index; }
	const pan::City& getCity() const { return city; }
	QPointF center() const;
Q_SIGNALS:
	void cityItemSelected(pan::CityIndex index);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
	pan::City city;
	pan::CityIndex index;
	QPainterPath circle(QPointF center, int radius) const;
};

#endif // CITYITEM_H
