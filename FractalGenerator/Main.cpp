#include <SFML/Graphics.hpp>
#include <iostream>
#include<windows.h>
#include <chrono>
#include <algorithm>

int main() {

		int screenWidth = 750;
		int screenHeight = 750;
		sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight, 32), "Julia Set");
		int Width = 750;
		int Height = 750;
		
		double cRe, cIm;           
		double newRe, newIm, oldRe, oldIm;
		double zoom = 0.9, moveX = 0, moveY = 0;
		sf::Color color;
		int maxIterations = 255; 
		sf::Uint8* pixels = new sf::Uint8[Width * Height * 4];
		sf::Texture texture;
		texture.create(Width, Height);
		sf::Sprite sprite;
		
		
		cRe = -0.86f;
		cIm = 0.26f;

		

		while (window.isOpen()) {
			for (int y = 0; y < Height; y++) {
				for (int x = 0; x < Width; x++)
				{
					newRe = 1.5 * (x - Width / 2) / (0.5 * zoom * Width) + moveX;
					newIm = (y - Height / 2) / (0.5 * zoom * Height) + moveY;
					int i;
					for (i = 0; i < maxIterations; i++)
					{
						oldRe = newRe;
						oldIm = newIm;
						newRe = oldRe * oldRe - oldIm * oldIm + cRe;
						newIm = 2 * oldRe * oldIm + cIm;
						if ((newRe * newRe + newIm * newIm) > 4) break;
					}
					
					int location = (x * 4) + (y * Width * 4);
					int color = float(i) / maxIterations * 255;

					pixels[location] = color; // R?
					pixels[location + 1] = color; // G?
					pixels[location + 2] = color; // B?
					pixels[location + 3] = 255; // A?
					
				}
			}
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				moveX += -0.005f * 3 / zoom;

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				moveX += 0.005f * 3 / zoom;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				moveY += -0.004f * 3/ zoom;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				moveY += 0.004f * 3/ zoom;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				zoom *= 1.025;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				zoom *= 0.975;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				cRe += 0.0001;
			}			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				cIm += 0.0001;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				cRe += -0.0001;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				cIm += -0.0001;
			}
			if (zoom < 0.9) {
				zoom = 0.9;
			}
			if (moveY > 1) {
				moveY = 1;
			} 
			if (moveY < -1) {
				moveY = -1;
			}
			if (moveX > 2) {
				moveX = 2;
			}
			if (moveX < -2) {
				moveX = -2;
			}
			std::cout << "MoveX: " << moveX << " MoveY: " << moveY << " Zoom: " << zoom	<< "\n";
			window.clear();
			texture.update(pixels);
			sprite.setTexture(texture);
			window.draw(sprite);
			window.display();
		}
		return 0;
}