#include "stdafx.h"
#include "Resources.h"

QMap<pan::RegionIndex, QPixmap> Resources::regionPixmaps;
QMap<pan::Roles, QPixmap> Resources::pawnPixmaps;
QMap<pan::Roles, QPixmap> Resources::avatarPixmaps;
QMap<pan::Roles, QPixmap> Resources::roleCardPixmaps;
QMap<pan::DiseaseType, QPixmap> Resources::diseaseIcons;
QMap<pan::DiseaseType, QPixmap> Resources::diseaseVialsCured;
QMap<pan::DiseaseType, QPixmap> Resources::diseaseVialsEradicated;
QMap<pan::CityIndex, QPixmap> Resources::cityCardsMap;
QMap<pan::CityIndex, QPixmap> Resources::infectionCardsMap;
QMap<pan::EventType, QPixmap> Resources::eventCardsMap;
QMap<pan::ActionType, QPixmap> Resources::actionMap;
QMap<pan::RegionIndex, QPixmap> Resources::cityMap;
std::unique_ptr<QPixmap> Resources::pandemicCard;
std::unique_ptr<QPixmap> Resources::infection;
std::unique_ptr<QPixmap> Resources::outbreak;
std::unique_ptr<QPixmap> Resources::station;
std::unique_ptr<QPixmap> Resources::stationPawn;
std::unique_ptr<QPixmap> Resources::playerCardBack;
std::unique_ptr<QPixmap> Resources::infectionCardBack;
std::unique_ptr<QPixmap> Resources::avatarBlank;
std::unique_ptr<QPixmap> Resources::victoryIcon;
std::unique_ptr<QPixmap> Resources::defeatIcon;
std::unique_ptr<QSound> Resources::soundtrack;


Resources::Resources()
{
}


Resources::~Resources()
{
}


QPixmap Resources::pixmapForRegion(pan::RegionIndex r)
{
	auto pix = regionPixmaps.find(r);
	if (pix != regionPixmaps.end())
		return *pix;
	Qt::GlobalColor c = RegionColors[r];
	if (c == Qt::black){
		auto pixMap = QPixmap("Resources\\Diseases\\disease_black.png");
		regionPixmaps[c] = pixMap;
		return pixMap;
	}
	else if (c == Qt::blue){
		auto pixMap = QPixmap("Resources\\Diseases\\disease_blue.png");
		regionPixmaps[c] = pixMap;
		return pixMap;
	}
	else if (c == Qt::yellow){
		auto pixMap = QPixmap("Resources\\Diseases\\disease_yellow.png");
		regionPixmaps[c] = pixMap;
		return pixMap;
	}
	else {
		auto pixMap = QPixmap("Resources\\Diseases\\disease_red.png");
		regionPixmaps[c] = pixMap;
		return pixMap;
	}
}

QPixmap Resources::pawnForRole(pan::Roles r)
{
	using pan::Roles;
	auto pix = pawnPixmaps.find(r);
	if (pix != pawnPixmaps.end())
		return *pix;
	std::string fileName;
	switch (r){
	case Roles::CPlanner:
		fileName = "Resources\\Pawns\\cplanner_pawn.png";
		break;
	case Roles::Dispatcher:
		fileName = "Resources\\Pawns\\dispatcher_pawn.png";
		break;
	case Roles::OperationsExpert:
		fileName = "Resources\\Pawns\\opexpert_pawn.png";
		break;
	case Roles::Scientist:
		fileName = "Resources\\Pawns\\scientist_pawn.png";
		break;
	case Roles::Medic:
		fileName = "Resources\\Pawns\\medic_pawn.png";
		break;
	case Roles::QSpecialist:
		fileName = "Resources\\Pawns\\qspecialist_pawn.png";
		break;
	default:
		fileName = "Resources\\Pawns\\researcher_pawn.png";
		break;
	}
	QPixmap p(fileName.c_str());
	pawnPixmaps[r] = p;
	return p;
}

QPixmap Resources::cardForRole(pan::Roles r)
{
	using pan::Roles;
	auto pix = roleCardPixmaps.find(r);
	if (pix != roleCardPixmaps.end())
		return *pix;
	std::string fileName;
	switch (r){
	case Roles::CPlanner:
		fileName = "Resources\\RoleCards\\cplanner_card.png";
		break;
	case Roles::Dispatcher:
		fileName = "Resources\\RoleCards\\dispatcher_card.png";
		break;
	case Roles::OperationsExpert:
		fileName = "Resources\\RoleCards\\opexpert_card.png";
		break;
	case Roles::Scientist:
		fileName = "Resources\\RoleCards\\scientist_card.png";
		break;
	case Roles::Medic:
		fileName = "Resources\\RoleCards\\medic_card.png";
		break;
	case Roles::QSpecialist:
		fileName = "Resources\\RoleCards\\qspecialist_card.png";
		break;
	default:
		fileName = "Resources\\RoleCards\\researcher_card.png";
		break;
	}
	QPixmap p(fileName.c_str());
	roleCardPixmaps[r] = p;
	return p;
}

QPixmap Resources::avatarForRole(pan::Roles r)
{
	using pan::Roles;
	auto pix = avatarPixmaps.find(r);
	if (pix != avatarPixmaps.end())
		return *pix;
	std::string fileName;
	switch (r){
	case Roles::CPlanner:
		fileName = "Resources\\Avatars\\cplanner_ava.png";
		break;
	case Roles::Dispatcher:
		fileName = "Resources\\Avatars\\dispatcher_ava.png";
		break;
	case Roles::OperationsExpert:
		fileName = "Resources\\Avatars\\opexpert_ava.png";
		break;
	case Roles::Scientist:
		fileName = "Resources\\Avatars\\scientist_ava.png";
		break;
	case Roles::Medic:
		fileName = "Resources\\Avatars\\medic_ava.png";
		break;
	case Roles::QSpecialist:
		fileName = "Resources\\Avatars\\qspecialist_ava.png";
		break;
	default:
		fileName = "Resources\\Avatars\\researcher_ava.png";
		break;
	}
	QPixmap p(fileName.c_str());
	avatarPixmaps[r] = p;
	return p;
}

QPixmap Resources::diseaseIcon(pan::DiseaseType d)
{
	using pan::DiseaseType;
	auto pix = diseaseIcons.find(d);
	if (pix != diseaseIcons.end())
		return *pix;
	std::string fileName;
	switch (d){
	case RegionDiseaseBlack:
		fileName = "Resources\\Diseases\\disease_black.png";
		break;
	case RegionDiseaseYellow:
		fileName = "Resources\\Diseases\\disease_yellow.png";
		break;
	case RegionDiseaseRed:
		fileName = "Resources\\Diseases\\disease_red.png";
		break;
	default:
		fileName = "Resources\\Diseases\\disease_blue.png";
		break;
	}
	QPixmap p(fileName.c_str());
	diseaseIcons[d] = p;
	return p;
}

QPixmap Resources::diseaseVialCured(pan::DiseaseType d)
{
	using pan::DiseaseType;
	auto pix = diseaseVialsCured.find(d);
	if (pix != diseaseVialsCured.end())
		return *pix;
	std::string fileName;
	switch (d){
	case RegionDiseaseBlack:
		fileName = "Resources\\Diseases\\disease_black_vial_cured.png";
		break;
	case RegionDiseaseYellow:
		fileName = "Resources\\Diseases\\disease_yellow_vial_cured.png";
		break;
	case RegionDiseaseRed:
		fileName = "Resources\\Diseases\\disease_red_vial_cured.png";
		break;
	default:
		fileName = "Resources\\Diseases\\disease_blue_vial_cured.png";
		break;
	}
	QPixmap p(fileName.c_str());
	diseaseVialsCured[d] = p;
	return p;
}

QPixmap Resources::diseaseVialEradicated(pan::DiseaseType d)
{
	using pan::DiseaseType;
	auto pix = diseaseVialsEradicated.find(d);
	if (pix != diseaseVialsEradicated.end())
		return *pix;
	std::string fileName;
	switch (d){
	case RegionDiseaseBlack:
		fileName = "Resources\\Diseases\\disease_black_vial_eradicated.png";
		break;
	case RegionDiseaseYellow:
		fileName = "Resources\\Diseases\\disease_yellow_vial_eradicated.png";
		break;
	case RegionDiseaseRed:
		fileName = "Resources\\Diseases\\disease_red_vial_eradicated.png";
		break;
	default:
		fileName = "Resources\\Diseases\\disease_blue_vial_eradicated.png";
		break;
	}
	QPixmap p(fileName.c_str());
	diseaseVialsEradicated[d] = p;
	return p;
}

QPixmap Resources::infectionPixmap()
{
	if (infection == nullptr){
		infection.reset(new QPixmap("Resources\\infection.png"));
	}
	return *infection.get();
}

QPixmap Resources::outbreakPixmap()
{
	if (outbreak == nullptr){
		outbreak.reset(new QPixmap("Resources\\outbreak.png"));
	}
	return *outbreak.get();
}

QPixmap Resources::stationPixmap()
{
	if (station == nullptr){
		station.reset(new QPixmap("Resources\\station.png"));
	}
	return *station.get();
}

QPixmap Resources::stationPawnPixmap()
{
	if (stationPawn == nullptr){
		stationPawn.reset(new QPixmap("Resources\\station_pawn.png"));
	}
	return *stationPawn.get();
}

QPixmap Resources::pixmapForCard(const pan::CardBase& c)
{
	using namespace pan;
	if (c.type == CardType::City){
		CityIndex index = static_cast<const CityCard&>(c).cityIndex;
		auto pix = cityCardsMap.find(index);
		if (pix != cityCardsMap.end())
			return *pix;
		std::string fileName = "Resources\\CityCards\\" + std::to_string(index) + ".png";
		QPixmap pixMap(fileName.c_str());
		cityCardsMap[index] = pixMap;
		return pixMap;
	}
	else if (c.type == CardType::Event){
		EventType type = static_cast<const EventCard&>(c).eventType;
		auto pix = eventCardsMap.find(type);
		if (pix != eventCardsMap.end())
			return *pix;
		int val = static_cast<std::underlying_type<pan::EventType>::type>(type);
		std::string fileName = "Resources\\EventCards\\" + std::to_string(val) + ".png";
		QPixmap pixMap(fileName.c_str());
		eventCardsMap[type] = pixMap;
		return pixMap;
	}
	else if (c.type == CardType::Infection){
		CityIndex index = static_cast<const InfectionCard&>(c).cityIndex;
		auto pix = infectionCardsMap.find(index);
		if (pix != infectionCardsMap.end())
			return *pix;
		std::string fileName = "Resources\\CityCards\\" + std::to_string(index) + ".png";
		QPixmap pixMap(fileName.c_str());
		infectionCardsMap[index] = pixMap;
		return pixMap;
	}
	else {
		if (pandemicCard != nullptr)
			return *pandemicCard.get();
		std::string fileName = "Resources\\pandemic_card.png";
		fileName = "Resources\\CARD.png";
		pandemicCard.reset(new QPixmap(fileName.c_str()));
		return *pandemicCard.get();
	}
}

QPixmap Resources::getInfectionCardBack()
{
	if (infectionCardBack == nullptr){
		infectionCardBack.reset(new QPixmap("Resources\\InfectionCards\\back.png"));
	}
	return *infectionCardBack.get();
}

QPixmap Resources::getPlayerCardBack()
{
	if (playerCardBack == nullptr){
		playerCardBack.reset(new QPixmap("Resources\\CityCards\\back.png"));
	}
	return *playerCardBack.get();
}


QPixmap Resources::getAvatarBlank()
{
	if (avatarBlank == nullptr){
		avatarBlank.reset(new QPixmap("Resources\\Avatars\\blank_ava.png"));
	}
	return *avatarBlank.get();
}

QPixmap Resources::getPixmapForAction(pan::ActionType a)
{
	using pan::ActionType;
	auto pix = actionMap.find(a);
	if (pix != actionMap.end())
		return *pix;
	std::string fileName;
	switch (a){
	case ActionType::BuildStation:
		fileName = "Resources\\Actions\\BuildStation.png";
		break;
	case ActionType::CharterFlight:
		fileName = "Resources\\Actions\\CharterFlight.png";
		break;
	case ActionType::DirectFlight:
		fileName = "Resources\\Actions\\DirectFlight.png";
		break;
	case ActionType::Discard:
		fileName = "Resources\\Actions\\DiscardCard.png";
		break;
	case ActionType::DiscoverCure:
		fileName = "Resources\\Actions\\DiscoverCure.png";
		break;
	case ActionType::Draw:
		fileName = "Resources\\Actions\\DrawCard.png";
		break;
	case ActionType::ShuttleFlight:
		fileName = "Resources\\Actions\\ShuttleFlight.png";
		break;
	case ActionType::Move:
		fileName = "Resources\\Actions\\Drive.png";
		break;
	case ActionType::TreatDisease:
		fileName = "Resources\\Actions\\TreatDisease.png";
		break;
	case ActionType::Infect:
		fileName = "Resources\\Actions\\Infect.png";
		break;
	default:
		fileName = "Resources\\Actions\\ShareKnowledge.png";
		break;
	}
	QPixmap p(fileName.c_str());
	actionMap[a] = p;
	return p;
}

QPixmap Resources::getCityIconForRegion(pan::RegionIndex r)
{
	auto pix = cityMap.find(r);
	if (pix != cityMap.end())
		return *pix;
	std::string fileName;
	switch (r){
	case RegionDiseaseBlack:
		fileName = "Resources\\city_marker_black.png";
		break;
	case RegionDiseaseYellow:
		fileName = "Resources\\city_marker_yellow.png";
		break;
	case RegionDiseaseRed:
		fileName = "Resources\\city_marker_red.png";
		break;
	default:
		fileName = "Resources\\city_marker_blue.png";
		break;
	}
	QPixmap p(fileName.c_str());
	cityMap[r] = p;
	return p;
}

QPixmap Resources::getVictoryIcon()
{
	if (victoryIcon == nullptr){
		victoryIcon.reset(new QPixmap("Resources\\victory.png"));
	}
	return *victoryIcon.get();
}

QPixmap Resources::getDefeatIcon()
{
	if (defeatIcon == nullptr){
		defeatIcon.reset(new QPixmap("Resources\\defeat.png"));
	}
	return *defeatIcon.get();
}

void Resources::playSoundtrack(){
	if (soundtrack == nullptr){
		soundtrack.reset(new QSound("Resources\\Audio\\music.wav"));
	}
	soundtrack->play();
	soundtrack->setLoops(QSound::Infinite);
}