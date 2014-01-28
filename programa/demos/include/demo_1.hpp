#pragma once

#include "base.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <random>
/*#include <fann.h>
#include <fann_cpp.h>*/

struct Ball {
	sf::CircleShape shape;
	sf::Vector2f v;
};

class Demo_1 : public Demo {
public:
	bool prepare();
	void run();
private:
	sf::RenderWindow win;
	sf::Event eve;
	
	sf::Clock frameClock;
	float frameTime;

	static const int rectwidth = 40;
	static const int ballradius = 20;

	int enemypoints;
	int playerpoints;
	
	sf::RectangleShape rectangle_1;
	sf::RectangleShape rectangle_2;
	Ball ball;
	
	sf::Font font;
	sf::Text score;

	sf::SoundBuffer bouncebuff;
	sf::SoundBuffer bounce2buff;
	sf::SoundBuffer bounce3buff;
	sf::Sound bounce;
	sf::Sound bounce2;
	sf::Sound bounce3;
	
	//FANN::neural_net nn;
	
};
