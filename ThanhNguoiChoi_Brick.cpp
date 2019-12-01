#include "ThanhNguoiChoi_Brick.h"


//  Ham cap nhat thanh nguoi choi

void ThanhNguoiChoi_Brick::CapNhat(RenderWindow* window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (getPosition().x + getGlobalBounds().width / 2 >= 0)
		{
			move(-10.0f, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (getPosition().x + getGlobalBounds().width / 2 + 10 < window->getSize().x )
		{
			move(10.0f, 0);
		}
	}
}

ThanhNguoiChoi_Brick::ThanhNguoiChoi_Brick()
{
	Load("paddle.png"); 
}
