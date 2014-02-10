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
		
		float angle = car.shape.getRotation()*3.14/180;
		
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			car.shape.setRotation(car.shape.getRotation() + 2);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			car.shape.setRotation(car.shape.getRotation() -2);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sf::Vector2f final(cos(angle) * 4.f, sin(angle) * 4.f);
			car.shape.move(final);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sf::Vector2f final(-cos(angle) * 2.f, -sin(angle) * 2.f);
			car.shape.move(final);
		}
		win.clear(sf::Color(20, 20, 20));
		win.draw(car.shape);
		win.display();
	}
}

