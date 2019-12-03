#include "Ball_BrickGame.h"
#include <iostream>
Ball_BrickGame::Ball_BrickGame(DiemSo* d, Thanh* p)
{
	this->VanToc.x = 1;
	this->VanToc.y = 1;
	lives = 4; 
	Load("ball.png"); 
	diem = d; 
	player = p; 
	buffer = new SoundBuffer(); 
	buffer->loadFromFile("Sounds/bounce.wav"); 
	this->sound = new Sound(*this->buffer);

}

void Ball_BrickGame::CapNhat(sf::RenderWindow* window)
{
	// kiem tra va cham voi thanh
	if (KiemTraVaCham(player))
	{
		VanToc.y = -VanToc.y; 
		VanToc.y * 1.1;  
		VanToc.x *= 1.1; 
    }
	// cham tuong tren
	if (getPosition().y < 0 )
	{
		VanToc.y *= -1; 
	}
	// cham tuong duoi
	if (this->getPosition().y + this->getGlobalBounds().height >= window->getSize().y)
	{
		lives--;
		std::cout << lives << std::endl; 
		reset(window); 
	}
	// tuong trai phai
	if (getPosition().x < 0 || getPosition().x + getGlobalBounds().width >= window->getSize().x)
	{
		VanToc.x *= -1; 
	}

	VatThe::CapNhat(); 
}

void Ball_BrickGame::reset(sf::RenderWindow* window)
{
	this->VanToc.x = ((rand() % 2) == 0) ? 1.2 : -1.2; //Random hướng của bóng theo x với vận tốc 1.2f
	this->VanToc.y = -1.2; 
	player->setPosition(window->getSize().x / 2, window->getSize().y - 20); 
	this->setPosition(window->getSize().x / 2, window->getSize().y - 60); 
	
}

Ball_BrickGame::~Ball_BrickGame()
{
	delete sound; 
	delete buffer;
}
