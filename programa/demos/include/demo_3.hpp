#pragma once

#define _USE_MATH_DEFINES

#include "base.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
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

extern const int Reward[];

#define VECLEN(i) veclen(srs.at(i)[0].position, srs.at(i)[1].position)
#define TRANS(i) translatesensor(VECLEN(i))

#define QAT(s) Q.at(s[0]).at(s[1]).at(s[2])
#define QELE(s, a) Q.at(s[0]).at(s[1]).at(s[2]).at(a)

#define STATEUP(sta) sta[0] = TRANS(0); \
	sta[1] = TRANS(1); \
	sta[2] = TRANS(2); \
	
#define REWARD(s) Reward[s[0]] + Reward[s[1]] + Reward[s[2]]

typedef std::array<uint, 3> State;


#define ALPHAQL 0.7
#define LAMBDAQL 1.0

#define TIMESCALE 0.25


double veclen(sf::Vector2f a, sf::Vector2f ap);

uint translatesensor(int s);
const char* translateaction(uint a);

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
	~Demo_3();
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
	
	uint action;
	
	void handle_tick(int rew = 9999);
	
	sf::Clock tickClock;
	sf::Color color;
	
	bool collided;
	
	State s;
	State sp;
	
};
