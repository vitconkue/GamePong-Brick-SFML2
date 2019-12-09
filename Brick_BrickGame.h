#pragma once
#include"VatThe.h"
#include"Ball_BrickGame.h"
#include "Brick_Prize.h"
#include <vector>

class Brick_BrickGame: public VatThe
{
protected:
	int Shield;
	string BrickColor;
public:
	int getShieldNumber();
	void setShieldNumber(int number);
	Brick_BrickGame();
	void CapNhat(Ball_BrickGame*& m_ball, DiemSo*& point);
	void TaoTexture();
};

