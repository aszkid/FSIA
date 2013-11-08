#include "display.hpp"

display::display()
	: frames(0)
{
	lineH[0] = sf::Vertex(sf::Vector2f(0, SH/2), QWHITE);
	lineH[1] = sf::Vertex(sf::Vector2f(SW, SH/2), QWHITE);

	lineV[0] = sf::Vertex(sf::Vector2f(SW/2, 0), QWHITE);
	lineV[1] = sf::Vertex(sf::Vector2f(SW/2, SH), QWHITE);

}
display::~display()
{}

bool display::run()
{
	w.create(VM, "FSIA Machine Learning Software", sf::Style::Fullscreen);
	_renderThread();
	return true;
}
void display::_renderThread()
{
	sf::Event ev;
	float seconds;

	while(w.isOpen())
	{
	
		while(w.pollEvent(ev))
		{
			switch(ev.type)
			{
			case sf::Event::Closed:
				w.close();
				break;
			case sf::Event::KeyPressed:
				if(ev.key.code == sf::Keyboard::Escape)
				{
					w.close();
					break;
				}
			default:
				break;
			}
		}
		// LOGIC
		// --------
		seconds = c.getElapsedTime().asSeconds();
		if(seconds >= 1.0f)
		{
			LOG(L_INFO, frames << "FPS");
			c.restart();
			frames = 0;
		}
		else
			frames++;
		

		// ------
		// DRAWING
		w.clear(DGREY);
		// ------
		w.draw(lineH, 2, sf::Lines);
		w.draw(lineV, 2, sf::Lines);
		// ------
		w.display();
	}
}
