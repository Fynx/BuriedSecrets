#pragma once

#include "Mind/Mind.hpp"
#include "UserInterface/UserInterface.hpp"

class Graphics {
public:
	Graphics(Mind *mind, UserInterface *userInterface);

private:
	Mind *mind;
	UserInterface *userInterface;
};