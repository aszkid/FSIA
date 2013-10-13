#include <unistd.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//#include <sfMidi.h>

const int SW = 1920;
const int SH = 1080;
const sf::Color QWHITE = sf::Color(215, 215, 215);

float offset = -100;

const int RH = 30;

#define LOG(x) std::cout << "-> LOG: " << x << std::endl;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SW, SH), "MIDI Reader?", sf::Style::Fullscreen);
	
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(SW/2, 0), QWHITE),
		sf::Vertex(sf::Vector2f(SW/2, SH), QWHITE),
	};
	sf::Vertex line2[] = {
		sf::Vertex(sf::Vector2f(0, SH/2), QWHITE),
		sf::Vertex(sf::Vector2f(SW, SH/2), QWHITE),
	};
	
	sf::RectangleShape rect1(sf::Vector2f(150, RH));
	rect1.setPosition(SW/2, SH/2 - RH/2);
	rect1.setFillColor(sf::Color::Red);
	
	sf::RectangleShape rect2(sf::Vector2f(230, RH));
	rect2.setPosition(SW/2 + 150, SH/2 - RH/2 - RH);
	rect2.setFillColor(sf::Color::Blue);
	
	sf::RectangleShape rect3(sf::Vector2f(100, RH));
	rect3.setPosition(SW/2 - 100, SH/2 - RH/2 + RH);
	rect3.setFillColor(sf::Color::Green);
	
	sf::Music s;
	s.openFromFile("trio.flac");
	s.play();
	
	/*sfmidi::Midi testMidi("GUFSV144.sf2", "symph5mvt1.mid");
	testMidi.setGain(1.0);
	testMidi.play();*/
	
	LOG("PID: " << getpid());
	
	sf::Font font;
	font.loadFromFile("fonts/opensans/OpenSans-Regular.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("JS Bach - French Suite No. 2, I. Allemande");
	text.setCharacterSize(20);
	text.setColor(QWHITE);
	text.setPosition(10, 10);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}
		
		offset += 3.5;
		
		rect1.setPosition(SW/2 - offset, SH/2 - RH/2);
		rect2.setPosition(SW/2 + 150 - offset, SH/2 - RH/2 - RH);
		rect3.setPosition(SW/2 - 100 - offset, SH/2 - RH/2 + RH);

		window.clear(sf::Color(25, 25, 25));
		window.draw(line, 2, sf::Lines);
		window.draw(line2, 2, sf::Lines);
		window.draw(text);
		
		window.draw(rect1);
		window.draw(rect2);
		window.draw(rect3);
		
		window.display();
	}

	return 0;
}
