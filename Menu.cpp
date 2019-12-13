
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
	this->font->loadFromFile("Graphics/font3.ttf");
	//Tên game
	this->tengame = new Text("PingPong & Brick Game", *this->font, 110U);
	this->tengame->setOrigin(this->tengame->getGlobalBounds().width / 2, this->tengame->getGlobalBounds().height / 2);
	this->tengame->setPosition(window->getSize().x / 2, window->getSize().y / 8);
	//Nút bắt đầu
	this->choi = new Text("Start Pong", *this->font, 90U);
	this->choi->setOrigin(this->choi->getGlobalBounds().width / 2, this->choi->getGlobalBounds().height / 2);
	this->choi->setPosition(window->getSize().x / 2, window->getSize().y / 3);
	// Nút bắt đầu chế độ brick
	this->choi2 = new Text("Start Brick", *font, 90U);
	this->choi2->setOrigin(choi2->getGlobalBounds().width / 2, choi2->getGlobalBounds().height / 2); 
	this->choi2->setPosition(window->getSize().x / 2, window->getSize().y / 3 + 80); 
	// Nút vào highscore
	this->highscore_menu = new Text("High Scores", *font, 90U);
	this->highscore_menu->setOrigin(highscore_menu->getGlobalBounds().width / 2, highscore_menu->getGlobalBounds().height / 2);
	this->highscore_menu->setPosition(window->getSize().x / 2, window->getSize().y / 3 + 160); 
	//Nút thoát
	this->thoat = new Text("Quit Game", *this->font, 128U);
	this->thoat->setOrigin(this->thoat->getGlobalBounds().width / 2, this->thoat->getGlobalBounds().height / 2);
	this->thoat->setPosition(window->getSize().x / 2, window->getSize().y / 3 + this->choi->getGlobalBounds().height + 240);
	//background
	background.loadFromFile("Graphics/sprites/InGameBackGround.png");
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
	if (this->luachon > 3)
	{
		this->luachon = 0;
	}
	if (this->luachon < 0)
	{
		this->luachon = 3;
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
			coreState.SetTrangThai(new mainGame_Brick()); 
			break; 
		case 2:
			coreState.SetTrangThai(new HighScoreScreen()); 
			break; 
		case 3:
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

	this->choi->setFillColor(Color::Black);
	this->thoat->setFillColor(Color::Black);
	switch (this->luachon)
	{
	case 0:
		this->choi->setFillColor(Color::Blue);
		this->choi2->setFillColor(Color::White);
		this->thoat->setFillColor(Color::White); 
		this->highscore_menu->setFillColor(Color::White);
		break;
	case 1: 
		this->choi2->setFillColor(Color::Blue); 
		this->thoat->setFillColor(Color::White);
		this->choi->setFillColor(Color::White);
		this->highscore_menu->setFillColor(Color::White);
		break; 
	case 2: 
		this->highscore_menu->setFillColor(Color::Blue); 
		this->choi->setFillColor(Color::White);
		this->choi2->setFillColor(Color::White);
		this->thoat->setFillColor(Color::White);
		break; 
		
	case 3:
		this->choi->setFillColor(Color::White);
		this->choi2->setFillColor(Color::White);
		this->thoat->setFillColor(Color::Red);
		this->highscore_menu->setFillColor(Color::White);
	}
	//Xuất background
	Sprite sp(background);
	window->draw(sp);
	window->draw(*this->tengame);
	window->draw(*this->choi);
	window->draw(*this->choi2);
	window->draw(*this->highscore_menu);
	window->draw(*this->thoat);
}
void Menu::Destroy(RenderWindow* window)
{
	delete this->font;
	delete this->tengame;
	delete this->choi;
	delete this->choi2; 
	delete this->thoat;
}