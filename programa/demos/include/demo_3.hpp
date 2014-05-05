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
#include <algorithm>

/*#include <fann.h>
#include <fann_cpp.h>*/

enum Action {
	LEFT = 0,
	RIGHT = 1,
	NONE = 2
};

#define VECLEN(i) veclen(srs.at(i)[0].position, srs.at(i)[1].position)
#define TRANS(i) translatesensor(VECLEN(i))

#define QELE(s, a) Q.at(s[0]).at(s[1]).at(s[2]).at(a)

#define STATEUP(s) s[0] = TRANS(0); \
	s[1] = TRANS(1); \
	s[2] = TRANS(2); \

typedef std::array<uint, 3> State;


double veclen(sf::Vector2f a, sf::Vector2f ap);

uint translatesensor(int s);

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

	double steerang;
	double accelspd;
	
	std::default_random_engine gen;
	std::uniform_int_distribution<int> dist;

	Car car;
	
	std::array<sf::VertexArray, 3> srs;
	
	std::array<std::array<std::array<std::array<double, 3>, 10>, 10>, 10> Q;
	
	double alphaQL;
	
	uint action;
	
	void handle_tick();
	
	sf::Clock tickClock;
	sf::Color color;
	
	State s;
	State sp;
	
};
