#include "stdafx.h"
#include "Resources.h"

QMap<pan::RegionIndex, QPixmap> Resources::regionPixmaps;
QMap<pan::Roles, QPixmap> Resources::pawnPixmaps;
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