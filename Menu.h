#pragma once

#include "HighScoreScreen.h"
#include "mainGame_Bot.h"
#include"mainGame_Custom.h"
#include"mainGame_Findway.h"

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
	Text* custom;
	Text* findway;
	Text* highscore_menu; 
	Text* thoat;
	int luachon;
    bool upKey, downKey;
	Texture background;
	//Âm thanh
	SoundBuffer* moveBuffer;
	SoundBuffer* selectBuffer;
	SoundBuffer* mainBuffer;
	Sound* mainsound;
	Sound* sound;
};

