#include "Ball_BrickGame.h"
#include <iostream>
Ball_BrickGame::Ball_BrickGame(DiemSo* d)
{
	// đặt vận tốc ban đầu
	this->speed.x = 1.5;
	this->speed.y = 1.5;
	// ban đầu có 4 mạng
	lives = 4; 
	Load("ball.png"); 
	diem = d; 
	// load âm thanh
	buffer = new SoundBuffer(); 
	buffer->loadFromFile("Sounds/bounce.wav"); 
	this->sound = new Sound(*this->buffer); 
	this->setOrigin(Vector2f(getTexture()->getSize().x * 0.5, getTexture()->getSize().y * 0.5)); // đặt tâm text ở giữa
}

void Ball_BrickGame::CapNhat(sf::RenderWindow* window, DiemSo*& point, ThanhNguoiChoi_Brick* player, vector<Heart_BrickGame*>& hearts)
{
	// kiểm tra va chạm với thanh
	sf::Vector2u playerSize = Vector2u(player->getGlobalBounds().width, player->getGlobalBounds().height); 
	if (getPosition().x >= player->getPosition().x - playerSize.x/2 -5  &&
		getPosition().x <= player->getPosition().x + playerSize.x /2 + 5)
	{
		if (getPosition().y >= player->getPosition().y - playerSize.y/2)
		{
			// set lại hướng tuỳ theo vị trí chạm thanh, tăng vận tốc 10%
			double curSpeed = sqrt(speed.x * speed.x + speed.y * speed.y); 
			curSpeed *= 1.1;
			Vector2f ballPos = this->getPosition();
			Vector2f PaddlePos = player->getPosition();
			double P = (PaddlePos.x - ballPos.x) / (player->getGlobalBounds().width / 4);
			speed.y = - sqrt((curSpeed * curSpeed) / (P * P + 1));
			speed.x = speed.y * P;
			sound->play();
		}
    }
	// chạm tường trên
	if (getPosition().y < 0 )
	{
		speed.y *= -1; 
		sound->play();
	}
	// chạm tường dưới
	if (getPosition().y > player->getPosition().y - player->getGlobalBounds().height / 2 + 2)
	{
		lives--; // giảm mạng còn lại 
		reset(window, player);   
	}
	// chạm tường trái phải
	if (getPosition().x < 0 || getPosition().x + getGlobalBounds().width >= window->getSize().x)
	{
		speed.x *= -1; 
		sound->play();
	}

	VatThe::CapNhat(); // di chuyển theo vector vận tốc hiện thời
}
// reset khi không hứng dược bóng
void Ball_BrickGame::reset(sf::RenderWindow* window, ThanhNguoiChoi_Brick*& player)
{
	this->speed.x = ((rand() % 2) == 0) ? 1.2 : -1.2; //Random hướng của bóng theo x với vận tốc 1.2f
	this->speed.y = -1.2; 
	this->setPosition(window->getSize().x / 2, window->getSize().y - 60); 
	player->setScale(1.0, 1.0); 
}

//void Ball_BrickGame::setPlayer(Thanh* _player)
//{
//	player = _player; 
//}

Ball_BrickGame::~Ball_BrickGame()
{
	delete sound; 
	delete buffer;
}
