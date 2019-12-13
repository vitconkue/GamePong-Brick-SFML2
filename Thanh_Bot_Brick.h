#pragma once
#include "ThanhNguoiChoi_Brick.h"
#include "Ball_BrickGame.h"
class Thanh_Bot_Brick : public ThanhNguoiChoi_Brick
{
private :
public:
	void CapNhat(RenderWindow* window, Ball_BrickGame* _ball);
	Thanh_Bot_Brick(); 
};

