#include "stdafx.h"
#include "Resources.h"

QMap<pan::RegionIndex, QPixmap> Resources::regionPixmaps;
QMap<pan::Roles, QPixmap> Resources::pawnPixmaps;
QMap<pan::Roles, QPixmap> Resources::avatarPixmaps;
QMap<pan::Roles, QPixmap> Resources::roleCardPixmaps;
QMap<pan::DiseaseType, QPixmap> Resources::diseaseIcons;
QMap<pan::DiseaseType, QPixmap> Resources::diseaseVialsCured;
QMap<pan::DiseaseType, QPixmap> Resources::diseaseVialsEradicated;
std::unique_ptr<QPixmap> Resources::infection;
std::unique_ptr<QPixmap> Resources::outbreak;
std::unique_ptr<QPixmap> Resources::station;


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
		auto pixMap = QPixmap("Resources\\region_black.png");
		regionPixmaps[c] = pixMap;
		return pixMap;
	}
	else if (c == Qt::blue){
		auto pixMap = QPixmap("Resources\\region_blue.png");
		regionPixmaps[c] = pixMap;
		return pixMap;
	}
	else if (c == Qt::yellow){
		auto pixMap = QPixmap("Resources\\region_yellow.png");
		regionPixmaps[c] = pixMap;
		return pixMap;
	}
	else {
		auto pixMap = QPixmap("Resources\\region_red.png");
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
		fileName = "Resources\\cplanner_pawn.png";
		break;
	case Roles::Dispatcher:
		fileName = "Resources\\dispatcher_pawn.png";
		break;
	case Roles::OperationsExpert:
		fileName = "Resources\\opexpert_pawn.png";
		break;
	case Roles::Scientist:
		fileName = "Resources\\scientist_pawn.png";
		break;
	case Roles::Medic:
		fileName = "Resources\\medic_pawn.png";
		break;
	case Roles::QSpecialist:
		fileName = "Resources\\qspecialist_pawn.png";
		break;
	default:
		fileName = "Resources\\researcher_pawn.png";
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
		fileName = "Resources\\cplanner_card.png";
		break;
	case Roles::Dispatcher:
		fileName = "Resources\\dispatcher_card.png";
		break;
	case Roles::OperationsExpert:
		fileName = "Resources\\opexpert_card.png";
		break;
	case Roles::Scientist:
		fileName = "Resources\\scientist_card.png";
		break;
	case Roles::Medic:
		fileName = "Resources\\medic_card.png";
		break;
	case Roles::QSpecialist:
		fileName = "Resources\\qspecialist_card.png";
		break;
	default:
		fileName = "Resources\\researcher_card.png";
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
		fileName = "Resources\\cplanner_ava.png";
		break;
	case Roles::Dispatcher:
		fileName = "Resources\\dispatcher_ava.png";
		break;
	case Roles::OperationsExpert:
		fileName = "Resources\\opexpert_ava.png";
		break;
	case Roles::Scientist:
		fileName = "Resources\\scientist_ava.png";
		break;
	case Roles::Medic:
		fileName = "Resources\\medic_ava.png";
		break;
	case Roles::QSpecialist:
		fileName = "Resources\\qspecialist_ava.png";
		break;
	default:
		fileName = "Resources\\researcher_ava.png";
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
		fileName = "Resources\\disease_black.png";
		break;
	case RegionDiseaseYellow:
		fileName = "Resources\\disease_yellow.png";
		break;
	case RegionDiseaseRed:
		fileName = "Resources\\disease_red.png";
		break;
	default:
		fileName = "Resources\\disease_blue.png";
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
		fileName = "Resources\\disease_black_vial_cured.png";
		break;
	case RegionDiseaseYellow:
		fileName = "Resources\\disease_yellow_vial_cured.png";
		break;
	case RegionDiseaseRed:
		fileName = "Resources\\disease_red_vial_cured.png";
		break;
	default:
		fileName = "Resources\\disease_blue_vial_cured.png";
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
		fileName = "Resources\\disease_black_vial_eradicated.png";
		break;
	case RegionDiseaseYellow:
		fileName = "Resources\\disease_yellow_vial_eradicated.png";
		break;
	case RegionDiseaseRed:
		fileName = "Resources\\disease_red_vial_eradicated.png";
		break;
	default:
		fileName = "Resources\\disease_blue_vial_eradicated.png";
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