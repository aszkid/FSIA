#include "demo_1.hpp"

bool Demo_1::prepare()
{
	enemypoints = 0;
	playerpoints = 0;

	if(!font.loadFromFile(file_rel("Minecraftia.ttf")))
	{
		LOGE("Couldn't load font from file!");
		return false;
	}

	if(!bouncebuff.loadFromFile(file_rel("paddlehit.wav")))
	{
		LOGE("Couldn't load sound from file!");
		return false;
	}
	if(!bounce2buff.loadFromFile(file_rel("paddlehit_2.wav")))
	{
		LOGE("Couldn't load sound2 from file!");
		return false;
	}
	if(!bounce3buff.loadFromFile(file_rel("paddlehit_3.wav")))
	{
		LOGE("Couldn't load sound3 from file!");
		return false;
	}

	bounce.setBuffer(bouncebuff);
	bounce2.setBuffer(bounce2buff);
	bounce3.setBuffer(bounce3buff);

	frameTime = 0;
	win.create(sf::VideoMode::getDesktopMode(), "DEMO 1", sf::Style::Fullscreen);
	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);
	
	score.setFont(font);
	score.setCharacterSize(70);
	score.setColor(sf::Color::White);
	score.setString("0 | 0");

	sf::FloatRect scoreRect = score.getLocalBounds();
	score.setOrigin(scoreRect.left + scoreRect.width / 2.f, 0);
	score.setPosition(sf::Vector2f(win.getSize().x / 2.f, 20.f));
	
	rectangle_1.setSize(sf::Vector2f(rectwidth, win.getSize().y / 4));
	rectangle_1.setPosition(sf::Vector2f(0,0));
	rectangle_2.setSize(sf::Vector2f(rectwidth, win.getSize().y / 4));
	rectangle_2.setPosition(sf::Vector2f(win.getSize().x - rectangle_2.getSize().x, 0));
	
	ball.shape.setRadius(ballradius);
	ball.shape.setFillColor(sf::Color::White);
	ball.shape.setPosition(sf::Vector2f(win.getSize().x / 2, win.getSize().y / 2));
	ball.v = sf::Vector2f(0.f, 0.f);
	
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-(int) win.getSize().y / 2, (int) win.getSize().y / 2);

	ball.v = sf::Vector2f(win.getSize().x / 2, dis(gen));

	return true;
}
void Demo_1::run()
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
		
		//frameTime = frameClock.restart().asMilliseconds() * 1000.f;
		frameTime = frameClock.restart().asSeconds();
		
		const float spd = win.getSize().y / 2;
		
		// rectangles collision detection
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
		
		// ball collision detection
		sf::Vector2f nextpos = ball.shape.getPosition() + (sf::Vector2f(ball.v.x * frameTime, ball.v.y * frameTime));
		bool wall = false;

		// collide horizontal
		if((nextpos.x + ball.shape.getRadius() + 15 >= win.getSize().x) || (nextpos.x <= 0))
		{
			ball.v.x *= -1;
			bounce3.play();
			wall = true;
		}
		// collide vertical
		if((nextpos.y + ball.shape.getRadius() + 15 >= win.getSize().y) || (nextpos.y <= 0))
		{
			ball.v.y *= -1;
			bounce2.play();
		}

		sf::FloatRect ballRect = ball.shape.getGlobalBounds();
		sf::FloatRect playerRect = rectangle_1.getGlobalBounds();
		sf::FloatRect enemyRect = rectangle_2.getGlobalBounds();

		if(ballRect.intersects(playerRect))
		{
			ball.v.x *= -1;
			bounce.play();
		}
		else if(ballRect.intersects(enemyRect))
		{
			ball.v.x *= -1;
			bounce.play();
		}

		if(wall)
		{
			if(ball.shape.getPosition().x < win.getSize().x / 2)
			{
				score.setString(STREAM(playerpoints << " | " << ++enemypoints));
			}
			else
			{
				score.setString(STREAM(++playerpoints << " | " << enemypoints));
			}
			
			ball.shape.setPosition(sf::Vector2f(win.getSize().x / 2, win.getSize().y / 2));
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(-(int) win.getSize().y / 2, (int) win.getSize().y / 2);
			
			ball.v = sf::Vector2f(win.getSize().x / 2, dis(gen));
		}
		else
		{
			ball.shape.setPosition(ball.shape.getPosition() + (sf::Vector2f(ball.v.x * frameTime, ball.v.y * frameTime)));
		}

		win.clear(sf::Color::Black);
		
		win.draw(rectangle_1);
		win.draw(rectangle_2);
		win.draw(ball.shape);
		win.draw(score);
		
		win.display();
	}
}
