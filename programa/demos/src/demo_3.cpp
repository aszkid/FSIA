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
	win.create(sf::VideoMode(1280, 720), "DEMO 3");
	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);
	scoreRect = car.shape.getLocalBounds();
	car.shape.setOrigin(scoreRect.left + scoreRect.width / 2.f, scoreRect.top + 		scoreRect.height / 2.f);
	car.shape.scale(0.8f, 0.8f);
	
	//int size = 1;
	car.shape.setPosition(spawnpos);	

	for(auto& s : srs)
	{
		s = sf::VertexArray(sf::Lines, 2);
		for(size_t i = 0; i < 2; i++)
			s[i].color = sf::Color::Red;
	}
	
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
		const auto cs = car.shape.getSize();
		
		static const double L = 1;
		static const double sa_ang = dec2rad(25);
		
		srs[0][0].position = sf::Vector2f(cp.x + L * cos(angle2), cp.y + L * sin(angle2));
		srs[0][1].position = ps[0];
		
		auto srp = srs[0][0].position;
		
		if(srp.x < 0)
			srp.x = 0;
		if(srp.y < 0)
			srp.y = 0;
		
		int inc = 1;
		
		while(true)
		{
			if(image.getPixel(srp.x, srp.y) == sf::Color::White)
			{
				LOGI("WALL!");
				break;
			}
			/*if(inc > 200)
				break;*/
		
			srs[0][0].position.x = cp.x + (L+inc) * cos(angle2);
			srs[0][0].position.y = cp.y + (L+inc) * sin(angle2);
			srp = srs[0][0].position;
			
			LOGI("checking (" << srs[0][0].position.x << ", " << srs[0][0].position.y << ")");
			
			
			inc += 10;
		}
		
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
		
		/*for(auto& sr : srs)
		{			
			auto ap = sr[0].position;
			auto a = sr[1].position;
			if(ap.x < 0)
				ap.x = 0;
			if(ap.y < 0)
				ap.y = 0;
				
			sf::Color c(image.getPixel(ap.x, ap.y));
			
			if (c == sf::Color::White)
			{
				sr[0].color = sf::Color::Red;
				sr[1].color = sf::Color::Red;
			}
			else
			{
				sr[0].color = sf::Color::White;
				sr[1].color = sf::Color::White;
			}
		}*/
		
		win.clear(sf::Color(20, 20, 20));
		
		win.draw(circuit);
		win.draw(car.shape);
		
		for(auto& sr : srs)
			win.draw(sr);
		
		win.display();
	}

	
}


