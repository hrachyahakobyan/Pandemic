#pragma once
class Resources
{
public:
	Resources();
	~Resources();

	static QPixmap pixmapForRegion(pan::RegionIndex r);
	static QPixmap infectionPixmap();
	static QPixmap outbreakPixmap();
	static QPixmap stationPixmap();
	static QPixmap pawnForRole(pan::Roles r);
private:
	static QMap<pan::RegionIndex, QPixmap> regionPixmaps;
	static QMap<pan::Roles, QPixmap> pawnPixmaps;
	static std::unique_ptr<QPixmap> infection;
	static std::unique_ptr<QPixmap> outbreak;
	static std::unique_ptr<QPixmap> station;
};

