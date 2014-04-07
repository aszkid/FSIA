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

class Demo_4 : public Demo {
public:
	bool prepare();
	void run();
private:
	sf::RenderWindow win;
	sf::Event eve;
	
	sf::Clock frameClock;
	float frameTime;
	
	std::array<sf::RectangleShape, 16> grid;
	
	
	sf::Text ndos;
	sf::Font font;
	
	sf::Vector2u size;
	static const int w = 100;

};

