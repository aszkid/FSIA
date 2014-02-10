#pragma once

#include "base.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <random>
/*#include <fann.h>
#include <fann_cpp.h>*/

struct Car {
	Car()
		: shape(sf::Vector2f(120, 50))
	{}
	
	sf::RectangleShape shape;
};

class Demo_3 : public Demo {
public:
	bool prepare();
	void run();
private:
	sf::RenderWindow win;
	sf::Event eve;
	
	sf::Clock frameClock;
	float frameTime;

	Car car;
	
};
