#pragma once

#include "Mind/Mind.hpp"
#include "UserInterface/UserInterface.hpp"

class Graphics {
public:
	Graphics(Mind *mind);

	QWidget *getMapView();

private:
	Mind *mind;
};