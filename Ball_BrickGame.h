﻿#pragma once
#include <SFML\Audio.hpp>
#include "VatThe.h"
#include "DiemSo.h"
#include"ThanhNguoiChoi_Brick.h"
#include "Heart_BrickGame.h"

class Ball_BrickGame : public VatThe
{
private: 
	DiemSo* diem; // điểm
	int lives; // mạng 
	sf::SoundBuffer* buffer; // biến buffer âm thanh
	sf::SoundBuffer* buffer2;
	sf::Sound* sound; // âm thanh
public: 
	Ball_BrickGame(DiemSo* d); // constructor 
	void CapNhat(sf::RenderWindow* window, DiemSo*& point, ThanhNguoiChoi_Brick* player, vector<Heart_BrickGame*> &hearts); // cập nhật các yếu tố liên quan
	void reset(sf::RenderWindow* window, ThanhNguoiChoi_Brick* &player); // reset(khi không đỡ được thanh) 
	//void setPlayer(Thanh* _player);  // setter player
	void setLive(int a) { lives = a; }//set Live
	int getLive() { return lives; } // getter lấy số mạng còn lại hiện tại
	void  increaseLive() { lives += 1;  } // tăng mạng (khi ăn vật phẩm) 
	~Ball_BrickGame(); 

};

