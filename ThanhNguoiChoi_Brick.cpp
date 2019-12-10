#include "ThanhNguoiChoi_Brick.h"


//  Ham cap nhat thanh nguoi choi

void ThanhNguoiChoi_Brick::CapNhat(RenderWindow* window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (getPosition().x - getGlobalBounds().width / 2 >= 0) // khong bi ket ben trai
		{
			move(-8.0f, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (getPosition().x + getGlobalBounds().width / 2  < window->getSize().x ) // khong bi ket ben phai
		{
			move(8.0f, 0);
		}
	}
}

ThanhNguoiChoi_Brick::ThanhNguoiChoi_Brick()
{
	Load("paddle.png"); 
	this->setOrigin(Vector2f(getTexture()->getSize().x * 0.5, getTexture()->getSize().y*0.5));
}
