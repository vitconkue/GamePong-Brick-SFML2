#include "ThanhNguoiChoi.h"
//Hàm khởi tạo Thanh theo số thứ tự 0, 1
ThanhNguoiChoi::ThanhNguoiChoi(int so)
{
	this->So = so;
	switch (this->So)
	{
	case 0:
		this->Load("paddle1.png");
		break;
	default:
		this->Load("paddle2.png");
		break;
	}
}
//Hàm cập nhật Thanh người chơi
void ThanhNguoiChoi::CapNhat()
{
	switch (this->So)
	{
	case 0:
		//Thanh số 0 sẽ điều khiển lên xuống với nút S, W và với tốc độ 1.5f
		this->VanToc.y = Keyboard::isKeyPressed(Keyboard::Key::S) - Keyboard::isKeyPressed(Keyboard::Key::W);
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
		{
			this->move(0, 1.5);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::W))
		{
			this->move(0, -1.5);
		}
		break;
	default:
		//Thanh số 1 sẽ điều khiển lên xuống với nút mũi tên lên, xuống và với tốc độ 1.5f
		this->VanToc.y = Keyboard::isKeyPressed(Keyboard::Key::Down) - Keyboard::isKeyPressed(Keyboard::Key::Up);
		if (sf::Keyboard::isKeyPressed(Keyboard::Key::Down))
		{
			this->move(0, 1.5);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Up))
		{
			this->move(0, -1.5);
		}
		break;
	}
	VatThe::CapNhat();
	//Giới hạn di chuyển của thanh trong cửa sổ game
	if (this->getPosition().y < 0)
	{
		this->move(0, 2.0f);
	}
	if (this->getPosition().y + this->getGlobalBounds().height > 600)
	{
		this->move(0, -2.0f);
	}
}
