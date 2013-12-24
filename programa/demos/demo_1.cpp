#include "demo_1.hpp"

bool Demo_1::prepare()
{
	frameTime = 0;
	win.create(sf::VideoMode::getDesktopMode(), "DEMO 1", sf::Style::Fullscreen);
	win.setFramerateLimit(60);
	
	rectangle_1.setSize(sf::Vector2f(40, win.getSize().y / 4));
	rectangle_1.setPosition(sf::Vector2f(0,0));
	rectangle_2.setSize(sf::Vector2f(40, win.getSize().y / 4));
	rectangle_2.setPosition(sf::Vector2f(win.getSize().x - rectangle_2.getSize().x, 0));
	
	return true;
}
void Demo_1::run()
{
	LOGI("Window size is: " << win.getSize().x << "x" << win.getSize().y);

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
		
		frameTime = frameClock.restart().asSeconds();
		
		const float spd = win.getSize().y / 2;
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if(rectangle_1.getPosition().y + rectangle_1.getSize().y < win.getSize().y)
				rectangle_1.setPosition(rectangle_1.getPosition() + sf::Vector2f(0, spd * frameTime));
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if(rectangle_1.getPosition().y > 0)
				rectangle_1.setPosition(rectangle_1.getPosition() + sf::Vector2f(0, -spd * frameTime));
		}
		
		win.clear(sf::Color::Black);
		
		win.draw(rectangle_1);
		win.draw(rectangle_2);
		
		win.display();
	}
}
