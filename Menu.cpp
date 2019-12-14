
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
	this->title = new Text("PingPong & Brick Game", *this->font, 110U);
	this->title->setOrigin(this->title->getGlobalBounds().width / 2, this->title->getGlobalBounds().height / 2);
	this->title->setPosition(window->getSize().x / 2, window->getSize().y / 8);
	//Nút bắt đầu
	this->pongGame = new Text("Start Pong", *this->font, 90U);
	this->pongGame->setOrigin(this->pongGame->getGlobalBounds().width / 2, this->pongGame->getGlobalBounds().height / 2);
	this->pongGame->setPosition(window->getSize().x / 2, window->getSize().y / 3);
	// Nút bắt đầu chế độ brick
	this->brickGame = new Text("Start Brick", *font, 90U);
	this->brickGame->setOrigin(brickGame->getGlobalBounds().width / 2, brickGame->getGlobalBounds().height / 2); 
	this->brickGame->setPosition(window->getSize().x / 2, window->getSize().y / 3 + 80); 
	// Nút bắt đầu chế độ với bot
	this->brickBotGame = new Text("Start Bot", *font, 90U); 
	this->brickBotGame->setOrigin(brickBotGame->getGlobalBounds().width / 2, brickBotGame->getGlobalBounds().height / 2);
	this->brickBotGame->setPosition(window->getSize().x / 2, window->getSize().y / 3 + 160); 
	// Nút vào highscore
	this->highscore_menu = new Text("High Scores", *font, 90U);
	this->highscore_menu->setOrigin(highscore_menu->getGlobalBounds().width / 2, highscore_menu->getGlobalBounds().height / 2);
	this->highscore_menu->setPosition(window->getSize().x / 2, window->getSize().y / 3 + 240); 
	//Nút vào custom
	this->custom = new Text("Custom", *font, 90U);
	this->custom->setOrigin(custom->getGlobalBounds().width / 2, custom->getGlobalBounds().height / 2);
	this->custom->setPosition(window->getSize().x / 2, window->getSize().y / 3 + 320);
	//Nút vào chọn đường đi
	this->findway = new Text("Find way", *font, 90U);
	this->findway->setOrigin(findway->getGlobalBounds().width / 2, findway->getGlobalBounds().height / 2);
	this->findway->setPosition(window->getSize().x / 2, window->getSize().y / 3 + 400);
	//Nút thoát
	this->thoat = new Text("Quit Game", *this->font, 90U);
	this->thoat->setOrigin(this->thoat->getGlobalBounds().width / 2, this->thoat->getGlobalBounds().height / 2);
	this->thoat->setPosition(window->getSize().x / 2, window->getSize().y / 3 + 500);
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
	if (this->luachon > 6)
	{
		this->luachon = 0;
	}
	if (this->luachon < 0)
	{
		this->luachon = 6;
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
		case 2 :
			coreState.SetTrangThai(new mainGame_Bot()); 
			break; 
		case 3:
			coreState.SetTrangThai(new HighScoreScreen());
			break;
		case 4:
			coreState.SetTrangThai(new mainGame_Custom());
			break;
		case 5:
			coreState.SetTrangThai(new mainGame_Findway());
			break;
		case 6:
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

	this->pongGame->setFillColor(Color::Black);
	this->thoat->setFillColor(Color::Black);
	switch (this->luachon)
	{
	case 0:
		this->pongGame->setFillColor(Color::Blue);
		this->brickGame->setFillColor(Color::White);
		this->thoat->setFillColor(Color::White); 
		this->highscore_menu->setFillColor(Color::White);
		this->custom->setFillColor(Color::White);
		this->brickBotGame->setFillColor(Color::White);
		this->findway->setFillColor(Color::White);
		break;
	case 1: 
		this->brickGame->setFillColor(Color::Blue); 
		this->thoat->setFillColor(Color::White);
		this->pongGame->setFillColor(Color::White);
		this->highscore_menu->setFillColor(Color::White);
		this->custom->setFillColor(Color::White);
		this->brickBotGame->setFillColor(Color::White);
		this->findway->setFillColor(Color::White);
		break; 
	case 2: 
		this->highscore_menu->setFillColor(Color::White); 
		this->pongGame->setFillColor(Color::White);
		this->brickGame->setFillColor(Color::White);
		this->thoat->setFillColor(Color::White);
		this->custom->setFillColor(Color::White);
		this->brickBotGame->setFillColor(Color::Blue);
		this->findway->setFillColor(Color::White);
		break; 
		
	case 3:
		this->pongGame->setFillColor(Color::White);
		this->brickGame->setFillColor(Color::White);
		this->thoat->setFillColor(Color::White);
		this->highscore_menu->setFillColor(Color::Blue);
		this->brickBotGame->setFillColor(Color::White);
		this->custom->setFillColor(Color::White);
		this->findway->setFillColor(Color::White);
		break; 
	case 4: 
		this->pongGame->setFillColor(Color::White);
		this->brickGame->setFillColor(Color::White);
		this->thoat->setFillColor(Color::White);
		this->highscore_menu->setFillColor(Color::White);
		this->brickBotGame->setFillColor(Color::White);
		this->custom->setFillColor(Color::Blue);
		this->findway->setFillColor(Color::White);
		break;
	case 5:
		this->pongGame->setFillColor(Color::White);
		this->brickGame->setFillColor(Color::White);
		this->thoat->setFillColor(Color::White);
		this->highscore_menu->setFillColor(Color::White);
		this->brickBotGame->setFillColor(Color::White);
		this->custom->setFillColor(Color::White);
		this->findway->setFillColor(Color::Blue);
		break;
	case 6:
	{
		this->pongGame->setFillColor(Color::White);
		this->brickGame->setFillColor(Color::White);
		this->thoat->setFillColor(Color::Red);
		this->highscore_menu->setFillColor(Color::White);
		this->brickBotGame->setFillColor(Color::White);
		this->custom->setFillColor(Color::White);
		this->findway->setFillColor(Color::White);
		break;
	}
	}

	//Xuất background
	Sprite sp(background);
	window->draw(sp);
	window->draw(*this->title);
	window->draw(*this->pongGame);
	window->draw(*this->brickGame);
	window->draw(*this->brickBotGame); 
	window->draw(*this->highscore_menu);
	window->draw(*this->findway);
	window->draw(*this->custom);
	window->draw(*this->thoat);
}
void Menu::Destroy(RenderWindow* window)
{
	delete this->font;
	delete this->title;
	delete this->pongGame;
	delete this->brickGame; 
	delete this->thoat;
	delete this->findway;
}