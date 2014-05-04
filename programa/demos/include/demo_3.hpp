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

double veclen(sf::Vector2f a, sf::Vector2f ap);

std::string translatesensortostr(uint s);
uint translatesensor(int s);

struct State {
	enum Sensor {
		CLOSE,
		MIDCLOSE,
		MIDFAR,
		FAR
	};

	std::array<uint, 3> _sensor;
	bool _dead;
};

struct Experience {

	enum Action {
		RIGHT,
		LEFT,
		NOTHING
	};

	State _state;
	uint _action;
	int _reward;
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
	Demo_3();
private:
	sf::RenderWindow win;
	sf::Event eve;
	sf::FloatRect scoreRect;
	
	sf::Clock frameClock;
	float frameTime;
	
	bool selfdrive;
	
	std::default_random_engine gen;
	std::uniform_int_distribution<int> dist;

	Car car;
	
	std::array<sf::VertexArray, 3> srs;
	
	std::array<std::array<std::array<std::array<double, 3>, 4>, 4>, 4> Q;
	
	double alphaQL;
	
};
