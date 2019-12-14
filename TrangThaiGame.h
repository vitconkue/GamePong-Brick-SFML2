#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
//class Trạng Thái trừu tượng có cơ chế đa hình 
class TrangThai
{
public:
	virtual void KhoiTao(RenderWindow* window)
	{
	}

	virtual void CapNhat(RenderWindow* window)
	{
	}

	virtual void Xuat(RenderWindow* window)
	{
	}

	virtual void Destroy(RenderWindow* window)
	{
	}
};

class TrangThaiGame
{
private:
	RenderWindow* window;
	TrangThai* trangthai;
public:
	TrangThaiGame()
	{
		this->trangthai = NULL;
	}

	void SetWindow(RenderWindow* window)
	{
		this->window = window;
	}
	//Hàm set trạng thái của cửa sổ game
	void SetTrangThai(TrangThai* state)
	{
		if (this->trangthai != NULL)
		{
			this->trangthai->Destroy(this->window);
		}
		this->trangthai = state;
		if (this->trangthai != NULL)
		{
			this->trangthai->KhoiTao(this->window);
		}
	}
	//Hàm cập nhật cửa sổ game
	void CapNhat()
	{
		if (this->trangthai != NULL)
		{
			this->trangthai->CapNhat(this->window);
		}
	}
	//Hàm xuất
	void Xuat()
	{
		if (this->trangthai != NULL)
		{
			this->trangthai->Xuat(this->window);
		}
	}
	//getBuffer
	~TrangThaiGame()
	{
		if (this->trangthai != NULL)
		{
			this->trangthai->Destroy(this->window);
		}
	}
};

extern TrangThaiGame coreState;
extern bool quitGame;

