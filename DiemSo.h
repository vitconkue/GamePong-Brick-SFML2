#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class DiemSo : public Text
{
public:
	DiemSo(Font& font, unsigned int size);
	void TangDan();
	void CapNhat();
	int GetDiem();
private:
	int GiaTri;
};

