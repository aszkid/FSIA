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

int random_range(int d, int u);

struct State {
	std::array<double, 3> sensors;
	bool dead;
};

class Experience {

	enum action {
		RIGHT,
		LEFT,
		NOTHING
	};

	std::array<double, 3> _state;
	uint _action;
};

static const auto spawnpos = sf::Vector2f(525.f, 84.f);
double dec2rad(double dec);

struct Car {
	Car()
		: shape(sf::Vector2f(96, 65))
	{}
	
	sf::RectangleShape shape;
	
	std::array<sf::Vector2f, 6> punts();
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
	
	bool moved;

	Car car;
	
	std::array<sf::VertexArray, 3> srs;
	
};
