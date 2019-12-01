#pragma once
#include <SFML\Audio.hpp>
#include "VatThe.h"
#include "Thanh.h"
#include "DiemSo.h"
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
	void CapNhat(sf::RenderWindow* window); 
	void reset(sf::RenderWindow* window); 
	int getLive() { return lives; }
	~Ball_BrickGame(); 
};

