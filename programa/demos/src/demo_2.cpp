#include "demo_2.hpp"

bool Demo_2::prepare()
{
	converted = learned = false;

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
	//win.create(sf::VideoMode::getDesktopMode(), "DEMO 2", sf::Style::Fullscreen);
	win.create(sf::VideoMode(1280, 720), "DEMO 2");
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
							learn();
							break;

						case sf::Keyboard::C:
							convert();
							break;

						case sf::Keyboard::T:
							test();
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
void Demo_2::setImage(std::vector<int> img)
{
	for(size_t i = 0; i < board.size(); i++)
	{
		auto& box = board[i];
		int pixelcolor = img[i];
		
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
		static const char space = ' ';
	
		size_t file = 0;
		size_t image = 0;
		size_t index = 0;
		size_t off = 0;
		const size_t width = 28;
	
		size_t perfile = 750;
	
		std::ofstream out("learn2.dat");
		out << perfile*10 << space << width*width << space << 10 << std::endl << std::endl;
		
		while(fileCheckIndex(file))
		{
			loadFile(file);
		
			for(image = 0; image < perfile; image++)
			{
				off = image*width*width;
				
				for(index = off; index < off+width*width; index++)
				{
					out << static_cast<double>(1.0 * (data.at(index)) / 255.0) << space;
				}
				out << std::endl;
				
				for(size_t outi = 0; outi < 10; outi++)
				{
					if(outi == file)
						out << 1 << space;
					else
						out << 0 << space;
				}
				out << std::endl;
			}
			
			file++;
		}

		converted = true;
	}
}

void Demo_2::learn()
{
	fann* ann = fann_create_standard(3, 28*28, int((28*28)/2.0), 10);
	
	fann_train_on_file(ann, "learn2.dat", 1000, 25, 0.009);
	fann_save(ann, "nn2.net");
	
	fann_destroy(ann);
}

void Demo_2::test()
{
	fann_type* out;
	fann_type input[28*28];
	std::vector<int> input_v(28*28);
	
	fann* ann = fann_create_from_file("nn2.net");
	
	LOGI("Testing image #" << imageindex-1 << " of set #" << fileindex);
	
	for(size_t i = 0; i < 28*28; i++)
	{
		input[i] = static_cast<double>(1.0 * (data.at(i + (imageindex-1)*28*28)) / 255.0);
		input_v[i] = data.at(i + (imageindex-1)*28*28);
	}
	
	setImage(input_v);
	
	out = fann_run(ann, input);
	
	for(size_t i = 0; i < 10; i++)
	{
		LOGI(i << " - " << out[i]);
	}
	
	fann_destroy(ann);
}
