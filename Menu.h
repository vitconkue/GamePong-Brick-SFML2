#pragma once
#include "TrangThaiGame.h"
using namespace sf;
class Menu : public TrangThai
{
public:
	void KhoiTao(RenderWindow* window);
	void CapNhat(RenderWindow* window);
	void Xuat(RenderWindow* window);
	void Destroy(RenderWindow* window);
private:
	Font* font;
	Text* tengame;
	Text* choi;
	Text* thoat;
	Text* madeby;

	int luachon;

	bool upKey, downKey;
};

