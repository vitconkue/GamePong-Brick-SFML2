#pragma once
#include "TrangThaiGame.h"
#include "mainGame_Brick.h"
class mainGame_Findway : public mainGame_Brick
{
public:
	void KhoiTao(RenderWindow* window);
	void CapNhat(RenderWindow* window); // cập nhật các yếu tố có trong trò chơi
	void Xuat(RenderWindow* window); // Xuất ra màn hình
	void Destroy(RenderWindow* window); // Hàm huỷ
	bool ballMove;//Cho phép bóng di chuyển
	Vector2f TaoGoc(int angle);
	void AngleUp(int& angle);
	void AngleDown(int& angle);
	void LoadWay();
private:
	int angle;
	Brick_BrickGame *winBrick;
	Text* win;
	bool endgame;
};

