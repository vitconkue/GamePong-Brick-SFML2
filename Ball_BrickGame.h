#pragma once
#include <SFML\Audio.hpp>
#include "VatThe.h"
#include "Thanh.h"
#include "DiemSo.h"
#include"ThanhNguoiChoi_Brick.h"
#include "Heart_BrickGame.h"

class Ball_BrickGame : public VatThe
{
private: 
	DiemSo* diem; 
	int lives;
	Thanh* player; 
	sf::SoundBuffer* buffer; 
	sf::Sound* sound; 
public: 
	Ball_BrickGame(DiemSo* d, Thanh* p); 
	void CapNhat(sf::RenderWindow* window, DiemSo*& point, ThanhNguoiChoi_Brick* player, vector<Heart_BrickGame*> &hearts); 
	void reset(sf::RenderWindow* window); 
	void setPlayer(Thanh* _player); 
	int getLive() { return lives; }
	~Ball_BrickGame(); 

};

