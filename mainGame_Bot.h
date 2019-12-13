#pragma once

#include "TrangThaiGame.h"
#include "mainGame_Brick.h"
#include "Thanh_Bot_Brick.h"


class mainGame_Bot : public mainGame_Brick
{
public: 
	void KhoiTao(RenderWindow* window);
	void CapNhat(RenderWindow* window); // cập nhật các yếu tố có trong trò chơi
	void Xuat(RenderWindow* window); // Xuất ra màn hình
	void Destroy(RenderWindow* window); // Hàm huỷ
private:
	Thanh_Bot_Brick* botPlayer; 
};

