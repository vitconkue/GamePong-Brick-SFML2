#include "Thanh_Bot_Brick.h"

void Thanh_Bot_Brick::CapNhat(RenderWindow* window, Ball_BrickGame* _ball)
{
	Vector2f ballPos = _ball->getPosition(); 
	if (_ball->getSpeed().y > 0)
	{
		if (ballPos.x < getPosition().x + 40) 
		{
			if (getPosition().x - getGlobalBounds().width / 2 >= 0)
			{
				move(-10.f, 0);
			}
		}
		if (ballPos.x > getPosition().x -20) 
		{
			if (getPosition().x + getGlobalBounds().width / 2 < window->getSize().x)
			{
				move(10.f, 0);
			}
		}
		
	} 
}

Thanh_Bot_Brick::Thanh_Bot_Brick()
{
	ThanhNguoiChoi_Brick::ThanhNguoiChoi_Brick();
}
