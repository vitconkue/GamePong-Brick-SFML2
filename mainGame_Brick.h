#pragma once
#include "TrangThaiGame.h"
#include "ThanhNguoiChoi_Brick.h"
#include "DiemSo.h"
#include "Ball_BrickGame.h"
#include "Menu.h"
#include"Brick_BrickGame.h"
#include "Brick_Prize.h"
#include <fstream>
class mainGame_Brick : public TrangThai
{
public: 
	void KhoiTao(RenderWindow* window);
	void CapNhat(RenderWindow* window);
	void Xuat(RenderWindow* window);
	void Destroy(RenderWindow* window);
	void InputName(); 
	void InputName2(RenderWindow* window);
	void LoadBrick(string filename);
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
	int Effect;
	bool paused, enterKey; 
	bool endGame; 
};

