#pragma once
#include"VatThe.h"
#include"Ball_BrickGame.h"
#include "Brick_Prize.h"
#include <vector>

class Brick_BrickGame: public VatThe
{
protected:
	int Shield; // biến biểu diễn trạng thái của viên gạch, = 0 thì vỡ
	char BrickColor; // màu gạch
public:
	int getShieldNumber(); // getter shield
	void setShieldNumber(int number);// setter shield
	Brick_BrickGame(); // constructor
	void CapNhat(Ball_BrickGame*& m_ball, DiemSo*& point); // cập nhật các yếu tố liên quan
	void TaoTexture(); // tạo texture bằng cách load từ ảnh
	char getBrickColor(); // lấy màu gạch
	void setBrickColor(char a); // set màu gạch
};

