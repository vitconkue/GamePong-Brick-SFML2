#pragma once
#include "ThanhNguoiChoi_Brick.h"
#include "Ball_BrickGame.h"

// thanh trượt tự chạy, kế thừa từ thanh trượt thường
class Thanh_Bot_Brick : public ThanhNguoiChoi_Brick
{
private :
public:
	void CapNhat(RenderWindow* window, Ball_BrickGame* _ball); // cập nhất các yếu tố liên quan
	Thanh_Bot_Brick(); // constructor
};

