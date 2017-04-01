#include <QtWidgets>
#define DISABLE_TESTS
#include <core\Core.hpp>

#define RegionDiseaseBlue 0
#define RegionDiseaseYellow 1
#define RegionDiseaseBlack 2
#define RegionDiseaseRed 3

static const QMap<pan::RegionIndex, Qt::GlobalColor> RegionColors{
	{ 0, Qt::blue },
	{ 1, Qt::yellow },
	{ 2, Qt::black },
	{ 3, Qt::red }
};