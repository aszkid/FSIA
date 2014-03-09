#pragma once

#include "base.hpp"

#include <fstream>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>
#include "doublefann.h"

class Demo_2 : public Demo {
public:
	bool prepare();
	void run();
private:
	void convert();
	bool converted;
	void learn();
	bool learned;
	void test();

	sf::RenderWindow win;
	sf::Event eve;
	
	sf::Clock frameClock;
	float frameTime;
	
	void loadFile(int n);
	void setImage(int n);
	void setImage(std::vector<int> img);
	
	bool imageCheckIndex(size_t n);
	bool fileCheckIndex(int n);
	void updateInfoText();
	
	static const int xoff = 20;
	static const int yoff = 20;
	static const int boxsize = 5;
	
	std::array<sf::RectangleShape, 28*28> board;
	sf::VertexArray surround;
	int imageindex;
	int fileindex;
	std::vector<unsigned char> data;
	std::ifstream file;
	
	sf::Font font;
	sf::Text imageinfo;
	
	//FANN::neural_net nn;
	
};
