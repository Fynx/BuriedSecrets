#pragma once

#include "Mind/Mind.h"
#include "UserInterface/UserInterface.h"

class Graphics {
public:
	Graphics(Mind *mind, UserInterface *userInterface);

private:
	Mind *mind;
	UserInterface *userInterface;
};