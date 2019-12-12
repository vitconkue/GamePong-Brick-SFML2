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
	this->setOrigin(Vector2f(getTexture()->getSize().x * 0.5, getTexture()->getSize().y * 0.5));
}

void Ball_BrickGame::CapNhat(sf::RenderWindow* window, DiemSo*& point, ThanhNguoiChoi_Brick* player, vector<Heart_BrickGame*>& hearts)
{
	// kiem tra va cham voi thanh
	sf::Vector2u playerSize = Vector2u(player->getGlobalBounds().width, player->getGlobalBounds().height); 
	if (getPosition().x >= player->getPosition().x - playerSize.x/2 -5  &&
		getPosition().x <= player->getPosition().x + playerSize.x /2 + 5)
	{
		if (getPosition().y >= player->getPosition().y - playerSize.y/2)
		{
			double speed = sqrt(VanToc.x * VanToc.x + VanToc.y * VanToc.y);
			speed *= 1.1;
			Vector2f ballPos = this->getPosition();
			Vector2f PaddlePos = player->getPosition();
			double P = (PaddlePos.x - ballPos.x) / (player->getGlobalBounds().width / 4);
			VanToc.y = - sqrt((speed * speed) / (P * P + 1));
			VanToc.x = VanToc.y * P;
			sound->play();
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
		hearts.resize(lives); 
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
	player->setScale(1.0, 1.0); 
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
