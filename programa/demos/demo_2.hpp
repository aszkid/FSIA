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
	
	void loadFile(int n);
	void setImage(int n);
	bool imageCheckIndex(int n);
	bool fileCheckIndex(int n);
	void updateInfoText();
	
	const int xoff = 20;
	const int yoff = 20;
	const int boxsize = 5;
	
	std::array<sf::RectangleShape, 28*28> board;
	sf::VertexArray surround;
	int imageindex;
	int fileindex;
	std::vector<unsigned char> data;
	std::ifstream file;
	
	sf::Font font;
	sf::Text imageinfo;
	
	FANN::neural_net nn;
	
};
