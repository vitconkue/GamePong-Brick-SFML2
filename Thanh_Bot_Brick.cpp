#include "Thanh_Bot_Brick.h"

void Thanh_Bot_Brick::CapNhat(RenderWindow* window, Ball_BrickGame* _ball)
{
	Vector2f ballPos = _ball->getPosition(); 
	if (_ball->getSpeed().y > 0)
	{
		if (ballPos.x < getPosition().x + 40) // +40 để thanh bot không luôn đón bóng ở giữa mà đưa bóng sang bên trái
		{
			if (getPosition().x - getGlobalBounds().width / 2 >= 0) // không trượt ra ngoài màn hình chơi về bên trái
			{
				move(-10.f, 0); // di chuyển về bên trái
			}
		}
		if (ballPos.x > getPosition().x -20) // -20 để thanh bot không lên đón bóng ở giữa
		{
			if (getPosition().x + getGlobalBounds().width / 2 < window->getSize().x) // không trượt ra ngoài màn hình chơi về phía phải
			{
				move(10.f, 0); // di chuyển về bên phải
			}
		}
		
	} 
}
//  lấy constructor của chế độ chơi gốc
Thanh_Bot_Brick::Thanh_Bot_Brick()
{
	ThanhNguoiChoi_Brick::ThanhNguoiChoi_Brick();
}
