#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class DiemSo : public Text
{
public:
	DiemSo(Font& font, unsigned int size);
	void TangDan();
	void TangThem(int x); 
	void GiamXuong(int x); 
	void CapNhat();
	int GetDiem();
	void setDiem(int num) { GiaTri = num; }
private:
	int GiaTri;
};

