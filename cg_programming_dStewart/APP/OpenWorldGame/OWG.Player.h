// OWG.Player.h
/////////////////////////////////////////////////////////

#pragma once
#include "../../Application.h"
#include "../../CORE/CORE.GameObject.h"

class Player : GameObject {
public:
	Player();
	Player(vec3 position);
	void RunPlayerControls();
};