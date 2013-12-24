#pragma once

#include "base.hpp"

#include <SFML/Graphics.hpp>
#include <fann.h>
#include <fann_cpp.h>

class Demo_1 : public Demo {
public:
	bool prepare();
	void run();
private:
	sf::RenderWindow win;
	sf::Event eve;
	
	sf::Clock frameClock;
	float frameTime;
	
	sf::RectangleShape rectangle_1;
	sf::RectangleShape rectangle_2;
	
	FANN::neural_net nn;
	
};