#pragma once

#include "base.hpp"

#include <fstream>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>
#include <fann.h>
#include <fann_cpp.h>

class Demo_2 : public Demo {
public:
	bool prepare();
	void run();
private:
	sf::RenderWindow win;
	sf::Event eve;
	
	sf::Clock frameClock;
	float frameTime;
	
	std::vector<int> getImage(int n);
	std::array<sf::RectangleShape, 28*28> board; 
	
	std::vector<unsigned char> data;
	std::ifstream file;
	
	FANN::neural_net nn;
	
};
