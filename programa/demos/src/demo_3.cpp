#include "demo_3.hpp"

double dec2rad(double dec)
{
	return (dec*M_PI/180.0);
}

	
std::array<sf::Vector2f, 6> Car::punts()
{	
	const auto p = shape.getPosition();
	const auto s = shape.getSize();
	const double prop = 60.0;
	const double sx = (s.x/2.0)*prop/100.0;
	const double sy = (s.y/2.0)*prop/100.0;
	const double angle2 = dec2rad(shape.getRotation());
	const double angle3 = dec2rad(shape.getRotation() + 180);

	std::array<sf::Vector2f, 6> ps;
	ps[0] = sf::Vector2f(
		p.x + cos(angle2) * sx, p.y + sin(angle2) * sx
	);
	ps[1] = sf::Vector2f(
		ps[0].x - sin(angle2) * sy, ps[0].y + cos(angle2) * sy
	);
	ps[2] = sf::Vector2f(
		ps[0].x + sin(angle2) * sy, ps[0].y - cos(angle2) * sy
	);
	ps[3] = sf::Vector2f(
		p.x + cos(angle3) * sx, p.y + sin(angle3) * sx
	);
	ps[4] = sf::Vector2f(
		ps[3].x - sin(angle3) * sy, ps[3].y + cos(angle3) * sy
	);
	ps[5] = sf::Vector2f(
		ps[3].x + sin(angle3) * sy, ps[3].y - cos(angle3) * sy
	);
	
	return ps;
}

bool Demo_3::prepare()
{	
	frameTime = 0;
	win.create(sf::VideoMode::getDesktopMode(), "DEMO 3", sf::Style::Fullscreen);
	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);
	scoreRect = car.shape.getLocalBounds();
	car.shape.setOrigin(scoreRect.left + scoreRect.width / 2.f, scoreRect.top + 		scoreRect.height / 2.f);
	car.shape.scale(0.8f, 0.8f);
	
	int size = 1;
	car.shape.setPosition(spawnpos);
	p1.setSize(sf::Vector2f(size, size));
	p2.setSize(sf::Vector2f(size, size));
	//p3.setSize(sf::Vector2f(size, size));
	
    	return true;
}	
void Demo_3::run()
{
	
	sf::Texture car_t;
	sf::Texture background;
	sf::Sprite circuit;
	
	if(!car_t.loadFromFile("car2.png"))
		std::cout << "Error could not load car image" << std::endl;
	
	
	if(!background.loadFromFile("path2.png"))
		std::cout << "Error could not load circuit image" << std::endl;
	circuit.setTexture(background);
	sf::Image image = background.copyToImage();

	car.shape.setTexture(&car_t);
	
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
		
		double angle2 = dec2rad(car.shape.getRotation());
		double angle3 = dec2rad(car.shape.getRotation() + 180);
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			car.shape.setRotation(car.shape.getRotation()+2);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			car.shape.setRotation(car.shape.getRotation()-2);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sf::Vector2f final2(cos(angle2) * 4.f, sin(angle2) * 4.f);
			car.shape.move(final2);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sf::Vector2f final2(-cos(angle2) * 2.f, -sin(angle2) * 2.f);
			car.shape.move(final2);
		}
		
		std::array<sf::Vector2f, 6> ps(car.punts());
		std::array<sf::RectangleShape, 8> rs;
		
		const auto cp = car.shape.getPosition();
		const auto cs = car.shape.getSize();
		static const double L = 100;
		
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(cp.x + L * cos(angle2), cp.y + L * sin(angle2))),
			//sf::Vertex(sf::Vector2f(cp.x + cs.x * cos(angle2), cp.y + cs.y * sin(angle2)))
			sf::Vertex(sf::Vector2f(10, 10))
		};
		
		for(size_t i = 0; i < rs.size(); i++)
		{
			auto& rsi = rs[i];
			
			rsi = sf::RectangleShape(sf::Vector2f(1, 1));
			rsi.setPosition(ps[i]);
		}
		sf::Color color;
		
		for(size_t i = 0; i < rs.size(); i++)
		{
			color = image.getPixel(ps[i].x, ps[i].y);
			if (color == sf::Color::White)
			{
				car.shape.setPosition(spawnpos);
			}
		}
		
		win.clear(sf::Color(20, 20, 20));
		
		for(auto& rsi : rs)
		{
			win.draw(rsi);
		}
		
		win.draw(circuit);
		win.draw(car.shape);
		win.draw(line, 2, sf::Lines);
		
		win.display();
	}

	
}


