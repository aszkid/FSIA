#pragma once

#define _USE_MATH_DEFINES

#include "base.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <random>
#include <array>
#include <thread>
#include <chrono>
/*#include <fann.h>
#include <fann_cpp.h>*/

float transform_rot(float ang);
double dec2rad(double dec);

struct Car {
	Car()
		: shape(sf::Vector2f(96, 65))
	{}
	
	sf::RectangleShape shape;
	
	sf::Vector2f punt();
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
	
	sf::RectangleShape p1, p2, p3;

	Car car;
	
};
