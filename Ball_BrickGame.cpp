#include "Ball_BrickGame.h"
#include <iostream>
Ball_BrickGame::Ball_BrickGame(DiemSo* d, Thanh* p)
{
	this->VanToc.x = 1.5;
	this->VanToc.y = 1.5;
	lives = 4; 
	Load("ball.png"); 
	diem = d; 
	player = p; 
	buffer = new SoundBuffer(); 
	buffer->loadFromFile("Sounds/bounce.wav"); 
	this->sound = new Sound(*this->buffer);

}

void Ball_BrickGame::CapNhat(sf::RenderWindow* window, DiemSo*& point)
{
	// kiem tra va cham voi thanh
	if (getPosition().x >= player->getPosition().x - (player->getGlobalBounds().width)/2   &&
		getPosition().x <= player->getPosition().x + (player->getGlobalBounds().width)/2 )
	{
		if (getPosition().y >= player->getPosition().y - player->getGlobalBounds().height/2)
		{
			VanToc.y = -VanToc.y;
			VanToc.y * 1.1;
			VanToc.x *= 1.1;
			sound->play();
			point->TangThem(1);
		}
    }
	// cham tuong tren
	if (getPosition().y < 0 )
	{
		VanToc.y *= -1; 
		sound->play();
	}
	// cham tuong duoi
	if (getPosition().y > player->getPosition().y - player->getGlobalBounds().height / 2 + 2)
	{
		lives--;
		reset(window); 
	}
	// tuong trai phai
	if (getPosition().x < 0 || getPosition().x + getGlobalBounds().width >= window->getSize().x)
	{
		VanToc.x *= -1; 
		sound->play();
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

void Ball_BrickGame::setPlayer(Thanh* _player)
{
	player = _player; 
}

Ball_BrickGame::~Ball_BrickGame()
{
	delete sound; 
	delete buffer;
}
