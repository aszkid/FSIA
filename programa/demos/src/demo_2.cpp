#include "demo_2.hpp"

bool Demo_2::prepare()
{
	converted = false;

	if(!font.loadFromFile(file_rel("Minecraftia.ttf")))
	{
		LOGE("Couldn't load font from file!");
		return false;
	}
	
	imageinfo.setFont(font);
	imageinfo.setCharacterSize(15);
	imageinfo.setColor(sf::Color::White);
	imageinfo.setPosition(sf::Vector2f(xoff, yoff+28*boxsize+10));

	fileindex = 1;
	loadFile(fileindex);

	imageindex = 1;
	setImage(imageindex);
	
	updateInfoText();

	frameTime = 0;
	win.create(sf::VideoMode::getDesktopMode(), "DEMO 2", sf::Style::Fullscreen);
	win.setFramerateLimit(60);
	
	surround.append(sf::Vertex(sf::Vector2f(xoff, yoff)));
	surround.append(sf::Vertex(sf::Vector2f(xoff + 28*boxsize, yoff)));
	surround.append(sf::Vertex(sf::Vector2f(xoff + 28*boxsize, yoff + 28*boxsize)));
	surround.append(sf::Vertex(sf::Vector2f(xoff, yoff + 28*boxsize)));
	surround.append(sf::Vertex(sf::Vector2f(xoff, yoff)));
	surround.setPrimitiveType(sf::LinesStrip);
	
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
							
						case sf::Keyboard::Up:
							if(imageCheckIndex(imageindex+1))
							{
								setImage(++imageindex);
								updateInfoText();
							}
							break;
							
						case sf::Keyboard::Down:
							if(imageCheckIndex(imageindex-1))
							{
								setImage(--imageindex);
								updateInfoText();
							}
							break;
							
						case sf::Keyboard::Right:
							if(fileCheckIndex(fileindex+1))
							{
								loadFile(++fileindex);
								setImage(imageindex);
								updateInfoText();
							}
							break;
							
						case sf::Keyboard::Left:
							if(fileCheckIndex(fileindex-1))
							{
								loadFile(--fileindex);
								setImage(imageindex);
								updateInfoText();
							}
							break;
							
						case sf::Keyboard::L:
							LOGI("Learning!");
							break;

						case sf::Keyboard::C:
							convert();
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
		
		win.clear(sf::Color(20, 20, 20));
		
		for(auto& box : board)
			win.draw(box);
		win.draw(surround);
		
		win.draw(imageinfo);
		
		win.display();
	}
}

void Demo_2::setImage(int n)
{
	size_t index = 28*28*(n-1);
	
	std::vector<int> result(28*28);
	
	for(size_t i = index; i < 28*28 + index; i++)
	{
		result[i - index] = (int(data[i]));
	}
	
	for(size_t i = 0; i < board.size(); i++)
	{
		auto& box = board[i];
		int pixelcolor = result[i];
		
		box.setFillColor(sf::Color(pixelcolor, pixelcolor, pixelcolor));
		box.setSize(sf::Vector2f(boxsize, boxsize));
		
		int row = i / 28;
		int col = i - (row * 28);
		
		sf::Vector2f pos(xoff + (col*boxsize), yoff + (row*boxsize));
		
		box.setPosition(pos);
	}
}

void Demo_2::loadFile(int n)
{
	file.open(file_rel(STREAM("data" << n)), std::ios::binary);
	
	std::streampos filesize;
	
	file.seekg(0, std::ios::end);
	filesize = file.tellg();
	file.seekg(0, std::ios::beg);
	
	data.clear();
	data.resize(filesize);
	
	file.read((char*)&data[0], filesize);
	file.close();
}

bool Demo_2::imageCheckIndex(size_t n)
{
	if( (n <= 0) || ((28*28)*(n-1)+28*28 > data.size()) )
		return false;
	return true; 
}
	
bool Demo_2::fileCheckIndex(int n)
{
	if((n > 9) || (n < 0))
		return false;
	return true;
}

void Demo_2::updateInfoText()
{
	imageinfo.setString(STREAM("Image: " << imageindex << " | File: " << fileindex));
}

void Demo_2::convert()
{
	if(!converted)
	{
		size_t imgfile = 0;
		size_t imgind = 1;
		const size_t imgamount = data.size() / (28*28);

		static const size_t learning = 850;
		static const size_t testing = 150;
		
		size_t block = 0;
		
		std::ofstream fileln, filets;
		
		LOGI("Data size of " << data.size());
		
		while(fileCheckIndex(imgfile))
		{
			loadFile(imgfile);
		
			fileln.open(STREAM("learn" << imgfile));
			fileln << 28*28 << ' ' << static_cast<int>((28*28)/2) << ' ' << 10 << std::endl << std::endl;
			filets.open(STREAM("test" << imgfile));
			filets << 28*28 << ' ' << static_cast<int>((28*28)/2) << ' ' << 10 << std::endl << std::endl;
		
			for(imgind = 1; imgind < learning*28*28; imgind++)
			{
				if(block >= 28*28)
				{
					block = 0;
					fileln << std::endl << imgfile << std::endl;
					continue;
				}
				
				fileln << static_cast<int>(data.at(imgind-1)) << ' ';
				
				block++;
			}
			block = 0;
			for(imgind = learning*28*28; imgind < (testing+learning)*28*28; imgind++)
			{
				if(block >= 28*28)
				{
					block = 0;
					filets << std::endl << imgfile << std::endl;
					continue;
				}
				
				filets << static_cast<int>(data.at(imgind-1)) << ' ';
				
				block++;
			}
			
			fileln << std::endl << imgfile << std::endl;
			fileln.close();
			filets << std::endl << imgfile << std::endl;
			filets.close();
			
			imgfile++;
		}


		converted = true;
	}
}
