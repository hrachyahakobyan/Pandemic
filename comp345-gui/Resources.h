#pragma once
#include <core\Cards.h>

class Resources
{
public:
	Resources();
	~Resources();
	static QPixmap pixmapForRegion(pan::RegionIndex r);
	static QPixmap infectionPixmap();
	static QPixmap outbreakPixmap();
	static QPixmap stationPixmap();
	static QPixmap stationPawnPixmap();
	static QPixmap pawnForRole(pan::Roles r);
	static QPixmap cardForRole(pan::Roles r);
	static QPixmap avatarForRole(pan::Roles r);
	static QPixmap diseaseIcon(pan::DiseaseType d);
	static QPixmap diseaseVialCured(pan::DiseaseType d);
	static QPixmap diseaseVialEradicated(pan::DiseaseType d);
	static QPixmap pixmapForCard(const pan::CardBase& c);
	static QPixmap getInfectionCardBack();
	static QPixmap getPlayerCardBack();
	static QPixmap getPixmapForAction(pan::ActionType);
	static QPixmap getCityIconForRegion(pan::RegionIndex);
	static QPixmap getAvatarBlank();
private:
	static QMap<pan::RegionIndex, QPixmap> regionPixmaps;
	static QMap<pan::Roles, QPixmap> pawnPixmaps;
	static QMap<pan::Roles, QPixmap> roleCardPixmaps;
	static QMap<pan::Roles, QPixmap> avatarPixmaps;
	static QMap<pan::DiseaseType, QPixmap> diseaseIcons;
	static QMap<pan::DiseaseType, QPixmap> diseaseVialsCured;
	static QMap<pan::DiseaseType, QPixmap> diseaseVialsEradicated;
	static QMap<pan::CityIndex, QPixmap> cityCardsMap;
	static QMap<pan::CityIndex, QPixmap> infectionCardsMap;
	static QMap<pan::EventType, QPixmap> eventCardsMap;
	static QMap<pan::ActionType, QPixmap> actionMap;
	static QMap<pan::RegionIndex, QPixmap> cityMap;
	static std::unique_ptr<QPixmap> pandemicCard;
	static std::unique_ptr<QPixmap> infection;
	static std::unique_ptr<QPixmap> outbreak;
	static std::unique_ptr<QPixmap> station;
	static std::unique_ptr<QPixmap> stationPawn;
	static std::unique_ptr<QPixmap> playerCardBack;
	static std::unique_ptr<QPixmap> infectionCardBack;
	static std::unique_ptr<QPixmap> avatarBlank;
};

