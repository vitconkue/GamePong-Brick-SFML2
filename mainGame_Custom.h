#pragma once

#include "TrangThaiGame.h"
#include "mainGame_Brick.h"
#include "Thanh_Bot_Brick.h"

class mainGame_Custom: public mainGame_Brick
{
public:
	void KhoiTao(RenderWindow* window);
	void CapNhat(RenderWindow* window); // cập nhật các yếu tố có trong trò chơi
	void Xuat(RenderWindow* window); // Xuất ra màn hình
	void Destroy(RenderWindow* window); // Hàm huỷ
private:
	Vector2f select;
	RectangleShape LuaChon;
	Brick_BrickGame* tam;
	int tex_ID;
	bool leftKey, rightKey, upKey, downKey, enterKey, backKey;
	Text tiltle1;
	Text tiltle2;
};

