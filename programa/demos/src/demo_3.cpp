#include "demo_3.hpp"

bool Demo_3::prepare()
{
	
	
	frameTime = 0;
	win.create(sf::VideoMode::getDesktopMode(), "DEMO 1", sf::Style::Fullscreen);
	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);
	
	sf::FloatRect scoreRect = car.shape.getLocalBounds();
	car.shape.setOrigin(scoreRect.left + scoreRect.width / 2.f, scoreRect.top + scoreRect.height / 2.f);
	car.shape.setPosition(100, 100);
	
	car.shape.setRotation(45);
	
	return true;
}

void Demo_3::run()
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
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			car.shape.setRotation(car.shape.getRotation() + 1);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			car.shape.setRotation(car.shape.getRotation() -1);
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			car.shape.getRotation 
		}
		win.clear(sf::Color(20, 20, 20));
		win.draw(car.shape);
		win.display();
	}
}
