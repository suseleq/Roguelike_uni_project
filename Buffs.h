#pragma once
#include "GUI.h"

class Buffs : public GUI
{
private:
	//Initialize functions
	void initSprites(const std::vector<int>& drawnBuffs);
	void initVariables();

public:
	//Constructors / Destructors
	Buffs(const std::vector<int>& drawnBuffs);
	~Buffs();

	//Public functions
	void moveRight();
	void moveLeft();

	int getOption() const;
	void update(const float& dt);

	void render(sf::RenderTarget& target);
};

