#include "demo_3.hpp"

const int Reward[] = {
	-100,
	-50,
	-10,
	-5,
	0,
	1,
	2,
	3,
	4,
	5
};

uint translatesensor(int s)
{
	// if this doesnt work, try this:
	// (log(x) / max(log(x))) * 9

	if(s < 20)
		return 0;
	else if(s < 30)
		return 1;
	else if(s < 40)
		return 2;
	else if(s < 50)
		return 3;
	else if(s < 75)
		return 4;
	else if(s < 90)
		return 5;
	else if(s < 115)
		return 6;
	else if(s < 150)
		return 7;
	else if(s < 200)
		return 8;
	else if(s > 200)
		return 9;
	else
		return 0;
}


double veclen(sf::Vector2f a, sf::Vector2f ap)
{
	return sqrt(pow(ap.x - a.x, 2) + pow(ap.y - a.y, 2));
}


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

Demo_3::Demo_3()
	: dist(1,3), frameTime(0), selfdrive(false), collided(false)
{}

bool Demo_3::prepare()
{
	win.create(sf::VideoMode(1280, 720), "DEMO 3");
	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);
	scoreRect = car.shape.getLocalBounds();
	car.shape.setOrigin(scoreRect.left + scoreRect.width / 2.f, scoreRect.top + 		scoreRect.height / 2.f);
	car.shape.scale(0.8f, 0.8f);
	
	car.shape.setPosition(spawnpos);	

	for(auto& s : srs)
	{
		s = sf::VertexArray(sf::Lines, 2);
		for(size_t i = 0; i < 2; i++)
			s[i].color = sf::Color::Red;
	}
	
	
	
	for(auto& s1 : Q)
		for(auto& s2 : s1)
			for(auto& s3 : s2)
				for(auto& a : s3)
					a = 0;
		
	action = Action::RIGHT;
	
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
						case sf::Keyboard::D:
							selfdrive = false;
							break;
						case sf::Keyboard::A:
							selfdrive = true;
							break;
						default:
							break;
					}
					break;
				default:
					break;
				
			}
		}


		steerang = 180.0 * frameClock.getElapsedTime().asSeconds();
		accelspd = 250.0 * frameClock.getElapsedTime().asSeconds();
		frameClock.restart();
		
		double angle2 = dec2rad(car.shape.getRotation());
		
		if(selfdrive)
		{
			sf::Vector2f final2(cos(angle2) * accelspd, sin(angle2) * accelspd);
			car.shape.move(final2);
		
			int movement = dist(gen);
			switch(movement)
			{
			case 1:
				// move right
			
				car.shape.setRotation(car.shape.getRotation()+steerang);
			
				break;
			case 2:
				// move left
			
				car.shape.setRotation(car.shape.getRotation()-steerang);
			
				break;
			default:
				// keep straight
			
		
				break;
			}
		}
		else
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				car.shape.setRotation(car.shape.getRotation()+steerang);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				car.shape.setRotation(car.shape.getRotation()-steerang);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				sf::Vector2f final2(cos(angle2) * accelspd, sin(angle2) * accelspd);
				car.shape.move(final2);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				sf::Vector2f final2(-cos(angle2) * 2.f, -sin(angle2) * 2.f);
				car.shape.move(final2);
			}
		}
		
		std::array<sf::Vector2f, 6> ps(car.punts());
		
		const auto cp = car.shape.getPosition();
		const auto cso = car.shape.getSize();
		const auto cs = sf::Vector2f((cso.x/2.0)*60.0/100.0, (cso.y/2.0)*60.0/100.0);
		
		srs[0][1].position = ps[0];
		srs[1][1].position = ps[1];
		srs[2][1].position = ps[2];
		
		int inc1 = 1;
		int inc2 = 1;
		int inc3 = 1;
		
		while(true)
		{
			srs[0][0].position = sf::Vector2f(cp.x + (inc1) * cos(angle2), cp.y + (inc1) * sin(angle2));
		
			if(image.getPixel(srs[0][0].position.x, srs[0][0].position.y) == sf::Color::White)
			{
				break;
			}
		
			inc1 += 10;
		}
		while(true)
		{
		
			double offang = angle2 + dec2rad(15);
		
			srs[1][0].position = sf::Vector2f(cp.x + inc2 * cos(offang) - sin(offang) * cs.y, cp.y + inc2 * sin(offang) + cos(offang) * cs.y);
			
			if(image.getPixel(srs[1][0].position.x, srs[1][0].position.y) == sf::Color::White)
			{
				break;
			}
		
			inc2 += 10;
		}
		while(true)
		{
		
			double offang = angle2 - dec2rad(15);
		
			srs[2][0].position = sf::Vector2f(cp.x + inc3 * cos(offang) + sin(offang) * cs.y, cp.y + inc3 * sin(offang) - cos(offang) * cs.y);
			
			if(image.getPixel(srs[2][0].position.x, srs[2][0].position.y) == sf::Color::White)
			{
				break;
			}
		
			inc3 += 10;
		}

		for(size_t i = 0; i < ps.size(); i++)
		{
			color = image.getPixel(ps[i].x, ps[i].y);
			if (color == sf::Color::White)
			{
				if(selfdrive)
				{
					collided = true;
				
					LOGI("Handling tick (collision)");
					handle_tick();
				}
			
				car.shape.setPosition(spawnpos);
				car.shape.setRotation(0);
			}
		}
		
		if(!collided)
		{
			if(tickClock.getElapsedTime().asSeconds() >= 1.0)
			{
				LOGI("Handling tick (timestep)");
				handle_tick();
				
				tickClock.restart();
			}
		}
		else
			collided = false;
		
		win.clear(sf::Color(20, 20, 20));
		
		win.draw(circuit);
		win.draw(car.shape);
		
		for(auto& sr : srs)
		{
			win.draw(sr);
		}
		
		win.display();

	}

	
}

void Demo_3::handle_tick()
{
	STATEUP(sp)

	//LOGI("s  = (" << s1 << ", " << s2 << ", " << s3 << ")");
	LOGI("(discretized) s' = (" << sp[0] << ", " << sp[1] << ", " << sp[2] << ")");
	
	LOGI(" Q[s', a] = " << QELE(sp, action));
	
	LOGI("r = " << REWARD(sp));
}

