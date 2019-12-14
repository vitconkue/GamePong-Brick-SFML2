#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include<iostream>
using namespace sf;
using namespace std;
//class Vật thể là class cha để class Bóng và Thanh kế thừa 
class VatThe : public Sprite
{
private:
	Texture* texture;
public:
	Vector2f speed; //vận tốc của vật sử dụng vector2f trong Sprite
	//Hàm đọc thông tin từ file.
	Vector2f getSpeed()
	{
		return speed;
	}
	void setSpeed(Vector2f a)
	{
		speed = a;
	}
	void Load(string filename)
	{
		this->texture->loadFromFile("Graphics/sprites/" + filename);
		this->setTexture(*this->texture);
	}
	//Hàm cập nhật vận tốc 
	virtual void CapNhat()
	{
		this->move(this->speed);
	}
	//Hàm kiểm tra va chạm
	bool KiemTraVaCham(VatThe* object)
	{
		return this->getGlobalBounds().intersects(object->getGlobalBounds());
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
