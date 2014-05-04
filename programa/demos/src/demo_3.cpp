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
		//double angle3 = dec2rad(car.shape.getRotation() + 180);
		
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
		
		const auto cp = car.shape.getPosition();
		//const auto cs = car.shape.getSize();
		static const double L = 100;
		
		std::array<sf::VertexArray, 2> sensors;
		
		for(auto& s : sensors)
			s = sf::VertexArray(sf::Lines, 2);
		
		static const double sa_ang = dec2rad(25);
		
		sensors[0][0].position = sf::Vector2f(cp.x + L * cos(angle2), cp.y + L * sin(angle2));
		sensors[0][1].position = ps[0];
		
		sensors[1][0].position = sf::Vector2f(cp.x + L * cos(angle2 - sa_ang), ps[1].y);
		sensors[1][1].position = ps[1];
		
		sf::Color color;
		
		for(size_t i = 0; i < ps.size(); i++)
		{
			color = image.getPixel(ps[i].x, ps[i].y);
			if (color == sf::Color::White)
			{
				car.shape.setPosition(spawnpos);
				car.shape.setRotation(0);
			}
		}
		
		win.clear(sf::Color(20, 20, 20));
		
		win.draw(circuit);
		win.draw(car.shape);
		win.draw(sensors[0]);
		win.draw(sensors[1]);
		
		win.display();
	}

	
}


