#pragma once
#include <iostream>
#include "TrangThaiGame.h"
#include "DiemSo.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "mainGame_Brick.h"
class HighScoreScreen : public TrangThai
{
private: 
	Text* introduce; 
	std::vector<Text*> names; 
	std::vector<DiemSo*> highscores; 
	Font* font;
public: 
	void KhoiTao(RenderWindow* window);
	void CapNhat(RenderWindow* window);
	void Xuat(RenderWindow* window);
	void Destroy(RenderWindow* window);
	void Sort(); 
};

