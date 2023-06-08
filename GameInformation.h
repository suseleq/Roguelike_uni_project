#pragma once
#include "GUI.h"

class GameInformation : public GUI
{
private:
	//Initialize functions
	void initText();
	
public:
	//Constructors / Destructors
	GameInformation(int life, int points, int level);
	~GameInformation();
	
	//Public functions
	void update(int life, int points, int level);
};

