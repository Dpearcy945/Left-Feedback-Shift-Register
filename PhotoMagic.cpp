//Donovan Pearcy

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "LFSR.hpp"

using namespace std;
int main(int argc, char* argv[])
{
	
	sf::Image image1;
	if (!image1.loadFromFile(argv[1]))
		return -1;
	sf::Image image2;
	if (!image2.loadFromFile(argv[1]))
		return -1;
	// p will be used to change the color of each pixel in the image
	sf::Color p;

	//windows and size, why the fuzz about unsigned integers :{
	sf::Vector2u size = image1.getSize();
	int imagex = size.x;
	int imagey = size.y;
	sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "IN");
	sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "OUT");

	LFSR encryptdoo(argv[3], atoi(argv[4]));

	//goes down each column of the image and changes the color based on the integer
	//returned by the generate function
	for (int x = 0; x < imagex; x++) {
		for (int y = 0; y < imagey; y++) {
			p = image1.getPixel(x, y);
			
			p.r = p.r^encryptdoo.generate(8); //xors the stuff so that it can return to
			p.g = p.g^encryptdoo.generate(8); //to the original color
			p.b = p.b^encryptdoo.generate(8); //because xor undos another xor like 2 logical nots
			image1.setPixel(x, y, p);
		}
	}

	sf::Texture texture1;
	texture1.loadFromImage(image1);

	sf::Texture texture2;
	texture2.loadFromImage(image2);

	sf::Sprite sprite1;
	sprite1.setTexture(texture1);

	sf::Sprite sprite2;
	sprite2.setTexture(texture2);

	while (window1.isOpen()&& window2.isOpen())
	{
		sf::Event event;
		while (window1.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window1.close();
		}
		while (window2.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window2.close();
		}
		//print the original unedited image
		window1.clear();
		window1.draw(sprite2);
		window1.display();
		
		//show the encrypted image
		window2.clear();
    	window2.draw(sprite1);
    	window2.display();
	}

	
	//save it in the image file
	if (!image1.saveToFile(argv[2]))
		return -1;

	return 0;
}