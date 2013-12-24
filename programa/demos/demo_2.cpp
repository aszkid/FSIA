#include "demo_2.hpp"

bool Demo_2::prepare()
{
	file.open("./bin/data1", std::ios::binary);
	
	std::streampos filesize;
	
	file.seekg(0, std::ios::end);
	filesize = file.tellg();
	file.seekg(0, std::ios::beg);
	
	data = std::vector<unsigned char>(filesize);
	
	file.read((char*)&data[0], filesize);
	
	/*unsigned int pixelcount = 0;
	unsigned int imagecount = 0;
	
	for(auto& byte : data)
	{
		pixelcount++;
		
		if(pixelcount >= 28*28)
		{
			imagecount++;
			pixelcount = 0;
		}
	}*/
	
	getImage(1000);
	
	for(sf::RectangleShape& r : board)
	{
		
	}

	frameTime = 0;
	win.create(sf::VideoMode::getDesktopMode(), "DEMO 2", sf::Style::Fullscreen);
	win.setFramerateLimit(60);
	
	return true;
}
void Demo_2::run()
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
		
		win.clear(sf::Color::Black);
		
		win.display();
	}
}

std::vector<int> Demo_2::getImage(int n)
{
	size_t index = 28*28*(n-1);
	
	std::vector<int> result(28*28);
	
	if((28*28+index > data.size()) || (index > data.size()))
		throw;
	
	for(size_t i = index; i < 28*28 + index; i++)
	{
		result.push_back(int(data[i]));
	}
	
	return result;
}
