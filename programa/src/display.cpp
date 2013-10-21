#include "display.hpp"

display::display()
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
	std::thread t(&display::_renderThread, this);
	t.join();
	return true;
}
void display::_renderThread()
{
	sf::Event ev;

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
