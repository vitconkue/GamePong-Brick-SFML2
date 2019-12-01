#pragma once
#include <SFML/Audio.hpp>
#include "DiemSo.h"
#include "Thanh.h"
using namespace sf;
class Bong : public VatThe
{
private:
	DiemSo* diem1;
	DiemSo* diem2;
	Thanh* player1;
	Thanh* player2;
	SoundBuffer* buffer;//Biến lấy âm thanh
	Sound* sound;
public:
	void CapNhat(RenderWindow* window);
	void Reset(RenderWindow* window);
	Bong(DiemSo* d1, DiemSo* d2, Thanh* p1, Thanh* p2);
	~Bong();
};
