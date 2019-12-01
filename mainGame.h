#pragma once

#include "TrangThaiGame.h"
#include "ThanhNguoiChoi.h"
#include "Bong.h"
#include "DiemSo.h"
using namespace sf;
class mainGame : public TrangThai
{
public:
	void KhoiTao(RenderWindow* window);
	void CapNhat(RenderWindow* window);
	void Xuat(RenderWindow* window);
	void Destroy(RenderWindow* window);
private:
	ThanhNguoiChoi* player1, * player2;
	Bong* bong;
	DiemSo* diem1;
	DiemSo* diem2;
	Text* pausedText;
	Text* win1;
	Text* win2;
	Font* font;

	bool paused, enterKey;
	bool endgame;
};


