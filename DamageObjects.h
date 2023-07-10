#pragma once

#include "BaseObject.h"
#include "SFML/Graphics.hpp"

class Spikes : public BaseObject
{
protected:

	std::string side;

public:

	Spikes(std::string side);

	void setPosition(sf::Vector2f newPosition) override;
};

class SpikesTrap : public Spikes
{
private:

	double damageOnOpening = 2.0;
	double openTimer = 0.0;
	double openCoolDown = 0.65;
	bool isOpen = false;
	bool start = false;

public:

	SpikesTrap(std::string side);

	void update(double delta) override;
	void draw(sf::RenderWindow& window);
	void startProcess() override;
};

class KillZone : public BaseObject
{
public:

	KillZone();

	void draw(sf::RenderWindow& window) override;
};
