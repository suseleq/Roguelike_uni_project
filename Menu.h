#pragma once
#include "GUI.h"

class Menu : public GUI
{
private:
	//Variables
	float delayTime;
	bool changeOption;
	int currentOption;
	
	//Initialize functions
	void initText(bool mainMenu);
	void initVariables();

public:
	//Constructors / Destructors
	Menu(bool mainMenu);
	~Menu();

	//Public functions
	void moveUp();
	void moveDown();

	void update(const float& dt);

	int getOption();
};

