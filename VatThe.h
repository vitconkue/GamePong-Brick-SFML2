#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;
//class Vật thể là class cha để class Bóng và Thanh kế thừa 
class VatThe : public Sprite
{
private:
	Texture* texture;
public:
	Vector2f VanToc; //vận tốc của vật sử dụng vector2f trong Sprite
	//Hàm đọc thông tin từ file.
	void Load(string filename)
	{
		this->texture->loadFromFile("Graphics/sprites/" + filename);
		this->setTexture(*this->texture);
	}
	//Hàm cập nhật vận tốc 
	virtual void CapNhat()
	{
		this->move(this->VanToc);
	}
	//Hàm kiểm tra va chạm
	bool KiemTraVaCham(VatThe* thucthe)
	{
		return this->getGlobalBounds().intersects(thucthe->getGlobalBounds());
	}

	VatThe()
	{
		this->texture = new Texture();
	}
	~VatThe()
	{
		delete this->texture;
	}
};
