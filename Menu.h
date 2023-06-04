#pragma once
#include "GUI.h"

class Menu : public GUI
{
private:
	float delayTime;
	bool changeOption;
	int currentOption;
	
	void initText(bool mainMenu);

public:
	Menu(bool mainMenu);
	~Menu();

	void moveUp();
	void moveDown();

	void update(const float& dt);

	int getOption();
};

