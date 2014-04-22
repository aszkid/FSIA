#include "demo_3.hpp"

double dec2rad(double dec)
{
	return (dec*M_PI/180.0);
}

	
sf::Vector2f Car::punt()
{	
	double ang = shape.getRotation();	
	ang = dec2rad(ang);
	
	double sina = sin(ang);
	double cosa = cos(ang);
	
	sf::Vector2f size = shape.getSize();
	
	return sf::Vector2f(
		(cosa*size.x + sina*size.y)/(2), (cosa*size.y - sina*size.x)/(2)
	);
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
	car.shape.setPosition(100.f,100.f);
	
	p1.setSize(sf::Vector2f(size, size));
	p2.setSize(sf::Vector2f(size, size));
	//p3.setSize(sf::Vector2f(size, size));
	
    	return true;
}	
void Demo_3::run()
{	
	/*double rot= car.shape.getRotation();
	rot = transform_rot(rot);
	LOGI("rotació: " << rot);*/
	
	sf::Texture car_t;
	sf::Texture background;
	sf::Sprite circuit;
	
	if(!car_t.loadFromFile("car2.png"))
		std::cout << "Error could not load car image" << std::endl;
	
	
	if(!background.loadFromFile("2.png"))
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
		
		auto p = car.shape.getPosition();
		auto s = car.shape.getSize();
		double sx = (s.x/2.0) * 60 / 100;
		double sy = (s.y/2.0) * 60 / 100;
		
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
		
		
		//sf::Vector2f p4()
		
		std::array<sf::RectangleShape, 7> rs;
		
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
				car.shape.setPosition(100.f,100.f);
			}
		
		}
		//win.draw(car.shape);
		
		for(auto& rsi : rs)
		{
			win.draw(rsi);
		}
		
		win.clear(sf::Color(20, 20, 20));
		win.draw(circuit);
		win.draw(car.shape);
		win.display();
	}

	
}

