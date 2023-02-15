#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include <stdlib.h>
#include <time.h>

int width = 800;
int scale = 20;
float size = (float)width / scale;

bool start = false;
bool gameover = false;

float speed = size;
float xspeed = 0.f;
float yspeed = 0.f;

sf::RectangleShape food(sf::Vector2f(size, size));

std::vector<sf::RectangleShape> snake;

void init(std::vector<sf::RectangleShape>& snake)
{
	xspeed = 0.f;
	yspeed = 0.f;

	snake.clear();
	snake.resize(3);
	////////////////////draw snake/////////////////////////////
	snake[0].setSize(sf::Vector2f(size, size));
	snake[0].setOutlineColor(sf::Color::Black);
	snake[0].setOutlineThickness(2);
	snake[0].setPosition(size * 9, size * 10);
	for (unsigned int i = 1; i < snake.size(); i++) {
		snake[i].setSize(sf::Vector2f(size, size));
		snake[i].setOutlineColor(sf::Color::Black);
		snake[i].setOutlineThickness(2);
		snake[i].setPosition(snake[i - 1].getPosition().x - size, snake[i - 1].getPosition().y);
	}
	//////////////////////////////////////////////////////////

	////////////////draw food/////////////////////////////////
	food.setFillColor(sf::Color::Red);
	food.setOutlineColor(sf::Color::Red);
	food.setOutlineThickness(1);
	food.setPosition(size * 13, size * 10);
	//////////////////////////////////////////////////////////
}

void setFoodPos()
{
	food.setFillColor(sf::Color::Red);
	food.setOutlineColor(sf::Color::Red);
	food.setOutlineThickness(1);

	int x = rand() % (int)scale;
	int y = rand() % (int)scale;

	food.setPosition((float)x*size, (float)y*size);
}

void eat()
{
	if (snake[0].getPosition() == food.getPosition()) {
		setFoodPos();

		sf::RectangleShape nou(sf::Vector2f(size, size));
		nou.setOutlineColor(sf::Color::Black);
		nou.setOutlineThickness(2);

		snake.push_back(nou);
	}
}

void die()
{
	int sx = (int)snake[0].getPosition().x;
	int sy = (int)snake[0].getPosition().y;
	if (sx < 0 || sx + size > width || sy < 0 || sy + size > width) {
		gameover = true;
	}
		
	for (unsigned int i = 1; i < snake.size(); i++) {
		if (snake[0].getPosition() == snake[i].getPosition()) {
			gameover = true;
		}
	}
}

int main()
{
	srand((int)time(NULL));
	sf::RenderWindow window(sf::VideoMode(width, width), "Snake", sf::Style::Close);

	init(snake);

	sf::Clock clock;
	float timer = 0.f, delay = 0.1f;
	
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				start = true;
			}
			if (gameover) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Space) {
						init(snake);
						gameover = false;
						start = false;
					}
				}
			}
		}

		if (start && !gameover) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && yspeed == 0) {
				xspeed = 0.f;
				yspeed = -speed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && xspeed == 0) {
				xspeed = speed;
				yspeed = 0.f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && yspeed == 0) {
				xspeed = 0.f;
				yspeed = speed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && xspeed == 0) {
				xspeed = -speed;
				yspeed = 0.f;
			}
			
			if (timer > delay) {
				timer = 0;

				eat();
				for (unsigned int i = snake.size() - 1; i > 0; i--)
					snake[i].setPosition(snake[i - 1].getPosition());
				snake[0].move(xspeed, yspeed);
				die();

			}

			for (unsigned int i = 0; i < snake.size(); i++)
				window.draw(snake[i]);

			window.draw(food);
		}
		else {
			for (unsigned int i = 0; i < snake.size(); i++)
				window.draw(snake[i]);

			window.draw(food);
		}
		
		window.display();
		window.clear();
	}
}



//////////////////////draw grid/////////////////////////////
//int nr = width / (int)size;
//std::vector<sf::RectangleShape> line_v(nr);
//std::vector<sf::RectangleShape> line_o(nr);
//for (int i = 1; i < nr; i++) {
//	line_v[i].setSize(sf::Vector2f(1.f, (float)width));
//	line_v[i].setPosition((float)i*size, 0.f);

//	line_o[i].setSize(sf::Vector2f((float)width, 1.f));
//	line_o[i].setPosition(0.f, (float)i*size);
//}
//
//for (unsigned int i = 0; i < line_v.size(); i++) {
//	window.draw(line_v[i]);
//	window.draw(line_o[i]);
//}
////////////////////////////////////////////////////////////
