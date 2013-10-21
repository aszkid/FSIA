#pragma once

#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>

#include "types.hpp"

const sf::VideoMode VM = sf::VideoMode::getDesktopMode();
const int SW = VM.width;
const int SH = VM.height;
const sf::Color QWHITE = sf::Color(50, 50, 50);
const sf::Color DGREY = sf::Color(25, 25, 25);

class display
{
public:
	display();
	~display();

	bool run();

private:
	sf::Vertex lineH[2];
	sf::Vertex lineV[2];

	void _renderThread();
	sf::RenderWindow w;
};
