#pragma once

#include "HighScoreScreen.h"
#include "mainGame_Bot.h"

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
	Text* title;
	Text* pongGame;
	Text* brickGame; 
	Text* brickBotGame; 
	Text* highscore_menu; 
	Text* thoat;
	int luachon;
    bool upKey, downKey;
	Texture background;
};

