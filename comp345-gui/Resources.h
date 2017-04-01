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
	static QPixmap cardForRole(pan::Roles r);
	static QPixmap avatarForRole(pan::Roles r);
	static QPixmap diseaseIcon(pan::DiseaseType d);
	static QPixmap diseaseVialCured(pan::DiseaseType d);
	static QPixmap diseaseVialEradicated(pan::DiseaseType d);
private:
	static QMap<pan::RegionIndex, QPixmap> regionPixmaps;
	static QMap<pan::Roles, QPixmap> pawnPixmaps;
	static QMap<pan::Roles, QPixmap> roleCardPixmaps;
	static QMap<pan::Roles, QPixmap> avatarPixmaps;
	static QMap<pan::DiseaseType, QPixmap> diseaseIcons;
	static QMap<pan::DiseaseType, QPixmap> diseaseVialsCured;
	static QMap<pan::DiseaseType, QPixmap> diseaseVialsEradicated;
	static std::unique_ptr<QPixmap> infection;
	static std::unique_ptr<QPixmap> outbreak;
	static std::unique_ptr<QPixmap> station;
};

