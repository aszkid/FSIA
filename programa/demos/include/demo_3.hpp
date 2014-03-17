#pragma once

#include "base.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <random>
#include <array>
/*#include <fann.h>
#include <fann_cpp.h>*/

struct Car {
	Car()
		: shape(sf::Vector2f(96, 65))
	{}
	
	sf::RectangleShape shape;
	
	sf::Vector2f punt(double h, double w, double ang);
	std::array<sf::Vector2f, 4> punts();
};

class Demo_3 : public Demo {
public:
	bool prepare();
	void run();
private:
	sf::RenderWindow win;
	sf::Event eve;
	sf::FloatRect scoreRect;
	
	sf::Clock frameClock;
	float frameTime;

	Car car;
	
};
