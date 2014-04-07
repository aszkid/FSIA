#include "demo_4.hpp"

bool Demo_4::prepare()
{
	frameTime = 0;
	win.create(sf::VideoMode::getDesktopMode(), "DEMO 4", sf::Style::Fullscreen);
	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);
	
	
	font.loadFromFile("Minecraftia.ttf");
	
	size = win.getSize();
	
	for(size_t i = 0; i < grid.size(); i++)
	{	
		static const int mx = (size.x - 4*w) / 2;
		static const int my = (size.y - 4*w) / 2;
	
		grid[i].setSize(sf::Vector2f(w, w));
		grid[i].setFillColor(sf::Color::White);
		
		int row = i / 4;
		int col = i - (row * 4);
		
		int marginx = col * 5;
		int marginy = row * 5;
		
		sf::Vector2f pos(mx + (col*w) + marginx, my + (row*w) + marginy);
		
		grid[i].setPosition(pos);
	}
		ndos.setFont(font);
		ndos.setColor(sf::Color::Black);
		//ndos.setPosition(mx + row , my + col);
		
		auto gridpos = grid[0].getPosition();
		
		ndos.setPosition(gridpos.x + w/2.5, gridpos.y + w/2.5);
		ndos.setString('2');

	
	return true;
}

void Demo_4::run()
{
	 
	while(win.isOpen())
	{
		while(win.pollEvent(eve))
		{
			switch(eve.type)
			{
				case sf::Event::Closed:
					win.close();
					break;
				case sf::Event::KeyPressed:
					switch(eve.key.code)
					{
						/*case sf::Keyboard::Right:
							ndos.setPosition();
							break;
						case sf:Keyboard::Left:
							//ndos.setPosition();
							break;
						case sf::Keyboard::Up:
							//ndos.setPosition();
							break;
						case sf::Keyboard::Down:
							//ndos.setPosition();
							break;*/
						case sf::Keyboard::Escape:
							win.close();
							break;
						default:
							break;
					}
					break;
				default:
					break;
				
			}
		}
		
		win.clear(sf::Color(20, 20, 20));
		
		for(size_t i = 0; i < grid.size(); i++)
			win.draw(grid[i]);
		
		// dibuixar text
		win.draw(ndos);
		
		win.display();
	}
}

