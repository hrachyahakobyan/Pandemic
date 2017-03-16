#include "Pandemic.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Pandemic w;
	w.show();
	return a.exec();
}
