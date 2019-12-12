#pragma once
#include "TrangThaiGame.h"
#include "ThanhNguoiChoi_Brick.h"
#include "DiemSo.h"
#include "Ball_BrickGame.h"
#include "Menu.h"
#include"Brick_BrickGame.h"
#include "Heart_BrickGame.h"
#include "Brick_Prize.h"
#include "SupportFunction.h"
#include <fstream>

class mainGame_Brick : public TrangThai
{
public: 
	void KhoiTao(RenderWindow* window);
	void CapNhat(RenderWindow* window);
	void Xuat(RenderWindow* window);
	void Destroy(RenderWindow* window);
	void InputName(RenderWindow* window);
	void LoadBrick(string filename);
	void SaveGame(string filename);
	void LoadGame(string filename);
private: 
	vector<Heart_BrickGame*> hearts;
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

