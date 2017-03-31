#include <QtWidgets>
#define DISABLE_TESTS
#include <core\Core.hpp>

static const QMap<pan::RegionIndex, Qt::GlobalColor> RegionColors{
	{ 0, Qt::blue },
	{ 1, Qt::yellow },
	{ 2, Qt::black },
	{ 3, Qt::red }
};