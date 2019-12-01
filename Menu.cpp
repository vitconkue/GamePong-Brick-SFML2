
#include <iostream>
#include "Menu.h"
#include "mainGame.h"
using namespace sf;
//Hàm khởi tạo Menu
void Menu::KhoiTao(RenderWindow* window)
{
	this->luachon = 0;
	//lấy font chữ
	this->font = new Font();
	this->font->loadFromFile("Graphics/font.ttf");
	//Tên game
	this->tengame = new Text("PingPong Game", *this->font, 128U);
	this->tengame->setOrigin(this->tengame->getGlobalBounds().width / 2, this->tengame->getGlobalBounds().height / 2);
	this->tengame->setPosition(window->getSize().x / 2, window->getSize().y / 8);
	//Nút bắt đầu
	this->choi = new Text("Bat dau", *this->font, 128U);
	this->choi->setOrigin(this->choi->getGlobalBounds().width / 2, this->choi->getGlobalBounds().height / 2);
	this->choi->setPosition(window->getSize().x / 2, window->getSize().y / 3);
	//Nút thoát
	this->thoat = new Text("Thoat", *this->font, 128U);
	this->thoat->setOrigin(this->thoat->getGlobalBounds().width / 2, this->thoat->getGlobalBounds().height / 2);
	this->thoat->setPosition(window->getSize().x / 2, window->getSize().y / 3 + this->choi->getGlobalBounds().height + 50);

	this->madeby = new Text("Made by 18120164 - 18120174", *this->font, 30U);
	this->madeby->setOrigin(this->madeby->getGlobalBounds().width / 2, this->madeby->getGlobalBounds().height / 2);
	this->madeby->setPosition(3 * window->getSize().x / 4, window->getSize().y / 2 + this->thoat->getGlobalBounds().height + this->choi->getGlobalBounds().height);
}
//Hàm cập nhật Menu
void Menu::CapNhat(RenderWindow* window)
{
	//Khi sử dụng mũi tên xuống, giá trị lựa chọn sẽ -1
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !this->upKey)
	{
		this->luachon -= 1;
	}
	//Khi sử dụng mũi tên lên, giá trị lựa chọn sẽ +1
	if (Keyboard::isKeyPressed(Keyboard::Key::Down) && !this->downKey)
	{
		this->luachon += 1;
	}
	//Nếu lựa chọn >1 hoặc <1 trả về 0
	if (this->luachon > 1)
	{
		this->luachon = 0;
	}
	if (this->luachon < 0)
	{
		this->luachon = 1;
	}
	//Bấm Enter để lựa chọn
	if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
	{
		switch (this->luachon)
		{
		case 0:
			coreState.SetTrangThai(new mainGame());
			break;
		case 1:
			quitGame = true;
			break;
		}
	}
	this->upKey = Keyboard::isKeyPressed(Keyboard::Key::Up);
	this->downKey = Keyboard::isKeyPressed(Keyboard::Key::Down);
}
//Hàm xuất ra Menu
void Menu::Xuat(sf::RenderWindow* window)
{
	this->choi->setFillColor(Color::White);
	this->thoat->setFillColor(Color::White);
	switch (this->luachon)
	{
	case 0:
		this->choi->setFillColor(Color::Green);
		break;
	case 1:
		this->thoat->setFillColor(Color::Green);
		break;
	}
	window->draw(*this->tengame);
	window->draw(*this->choi);
	window->draw(*this->thoat);
	window->draw(*this->madeby);
}
void Menu::Destroy(RenderWindow* window)
{
	delete this->font;
	delete this->tengame;
	delete this->choi;
	delete this->thoat;
	delete this->madeby;
}