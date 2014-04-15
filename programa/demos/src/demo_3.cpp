#include "demo_3.hpp"
	
float transform_rot(float ang)
{
	if(ang < 90 && ang > 0){ang = ang + 270;}
	else if(ang == 90){ang = ang + 180;}
	else if(ang < 180 && ang > 90){ang = ang + 90;}
	else if(ang < 270 && ang > 180){ang = ang -90;}
	else if(ang == 270){ang = ang -180;}
	else if(ang > 270) {ang = ang - 270;}
	
	if(ang < 90 && ang > 0){ang = 90 - ang;}
	else if(ang > 90 && ang < 180){ang = 270 - ang;}
	else if(ang > 180 && ang < 270){ang = 450 - ang;}
	else if(ang > 270 && ang < 360){ang = 630 - ang;}	
	return ang;
}

	
sf::Vector2f Car::punt()
{	
	double ang = shape.getRotation();	
	ang = ang*M_PI/180;
	ang = transform_rot(ang);
	
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
		
	
		float angle2 = car.shape.getRotation()*M_PI/180;
		//LOGI("rotació: " << transform_rot(car.shape.getRotation()));
				
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
		
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
		double a = transform_rot(car.shape.getRotation());
		
		auto s = car.shape.getSize();
		
		double sx = (s.x/2.0);
		double sy = (s.y/2.0);
		
		sf::Vector2f p2(
			p.x + cos(a) * sx, p.y + sin(a) * sx
		);
		sf::Vector2f p3(
			p2.x - sin(a) * sy, p2.y + cos(a) * sy
		);
		
		LOGI(a << ':' << p2.x << ':' << p2.y);
		
		sf::RectangleShape r(sf::Vector2f(1, 1));
		sf::RectangleShape r2(sf::Vector2f(1, 1));
		sf::RectangleShape r3(sf::Vector2f(1, 1));
		r.setPosition(p);
		r2.setPosition(p2);
		r3.setPosition(p3);
		win.draw(r);
		win.draw(r2);
		win.draw(r3);
		
		/*
		sf::Vector2f p2_d = car.punt();
		
		p1.setPosition(car.shape.getPosition());
		p2.setPosition(p1.getPosition() + p2_d);
		p3.setPosition(p2.getPosition().x, -p2.getPosition().y);
		
		sf::Vector2f posp2 = p2.getPosition();
		
		std::array<sf::Vector2f, 4> punts = car.punts();
		for(int i = 0; i < 4; i++)
		{
		LOGI("Punt " << i << ":" << punts[i].x << "," << punts[i].y << 			std::endl);
		}
		
		sf::Color color = image.getPixel(posp2.x, posp2.y);
				
		if (color == sf::Color::White)
		{
			car.shape.setPosition(100.f,100.f);
		}
		
		win.clear(sf::Color(20, 20, 20));
		win.draw(circuit);
		win.draw(car.shape);
		win.draw(p1);
		win.draw(p2);
		win.draw(p3);
		*/
		
		win.display();
	}

	
}

