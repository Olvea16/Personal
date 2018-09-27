#include "VolumeControl_2.h"
#include <QtWidgets/QApplication>

void time_task(VolumeControl_2 *);

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VolumeControl_2 w;
	w.show();
	return a.exec();
}
