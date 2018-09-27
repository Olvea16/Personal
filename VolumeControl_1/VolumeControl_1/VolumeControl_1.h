#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VolumeControl_1.h"

class VolumeControl_1 : public QMainWindow
{
	Q_OBJECT

public:
	VolumeControl_1(QWidget *parent = Q_NULLPTR);

private:
	Ui::VolumeControl_1Class ui;
};
