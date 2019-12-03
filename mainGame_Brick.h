#pragma once
#include "TrangThaiGame.h"
#include "ThanhNguoiChoi_Brick.h"
#include "DiemSo.h"
#include "Ball_BrickGame.h"
#include "Menu.h"
#include"Brick_BrickGame.h"
#include "Brick_Prize.h"
class mainGame_Brick : public TrangThai
{
public: 
	void KhoiTao(RenderWindow* window);
	void CapNhat(RenderWindow* window);
	void Xuat(RenderWindow* window);
	void Destroy(RenderWindow* window);
	void LoadBrick();
private: 
	vector<Brick_BrickGame*> brick;
	vector<Brick_Prize*> prize; 
	ThanhNguoiChoi_Brick* player; 
	Ball_BrickGame* ball; 
	DiemSo* point; 
	Text* pausedText;
	Font* font; 
	Text* win; 
	Text* lose; 
	bool paused, enterKey; 
	bool endGame; 
};

