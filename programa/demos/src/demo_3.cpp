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
	
/*std::array<sf::Vector2f, 4> Car::punts()
{	
	std::array<sf::Vector2f, 4> arr;
	sf::Vector2f pos = shape.getPosition();
	double angle = shape.getRotation()*3.1415/180;
	
	sf::Vector2f size = shape.getSize();
	for(int i = 0 ; i < 4 ; i++)
	{
		arr[i] = punt(size.x / 2, size.y / 2 , angle);
	}
		
		arr[0].x = arr[0].x * -1;	arr[0].y = arr[0].y * -1;
		arr[1].x = arr[1].x * -1;	arr[1].y = arr[1].y * 1;
		arr[2].x = arr[2].x * 1;	arr[2].y = arr[2].y * -1;
		arr[3].x = arr[3].x * 1;	arr[2].y = arr[2].y * 1;

	for(int i = 0 ; i < 4 ; i++)
	{
		arr[i].x = arr[i].x + pos.x;
		arr[i].y = arr[i].y + pos.y;	
	}
	
	return arr;
}
*/

bool Demo_3::prepare()
{
	
	
	frameTime = 0;
	win.create(sf::VideoMode::getDesktopMode(), "DEMO 3", sf::Style::Fullscreen);
	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);
	scoreRect = car.shape.getLocalBounds();
	car.shape.setOrigin(scoreRect.left + scoreRect.width / 2.f, scoreRect.top + 		scoreRect.height / 2.f);
	
	int size = 1;
	
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
		
		win.clear(sf::Color(20, 20, 20));
		
		auto p = car.shape.getPosition();
		auto s = car.shape.getSize();
		double sx = (s.x/2.0);
		double sy = (s.y/2.0);
		
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
		
		std::array<sf::RectangleShape, 8> rs;
		
		for(auto& rsi : rs)
		{
			rsi = sf::RectangleShape(sf::Vector2f(1, 1));
		}
		
		rs[0].setPosition(p);
		rs[1].setPosition(ps[0]);
		rs[2].setPosition(ps[1]);
		rs[3].setPosition(ps[2]);
		rs[4].setPosition(ps[2]);
		rs[5].setPosition(ps[3]);
		rs[6].setPosition(ps[4]);
		rs[7].setPosition(ps[5]);
		
		//win.draw(car.shape);
		
		for(auto& rsi : rs)
		{
			win.draw(rsi);
		}
		
		win.display();
	}

	
}

