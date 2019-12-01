#include "mainGame_Brick.h"

void mainGame_Brick::KhoiTao(RenderWindow* window)
{
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");
	player = new ThanhNguoiChoi_Brick;
	point = new DiemSo(*font, 64U);
	ball = new Ball_BrickGame(point, player); 
	ball->reset(window); 
	this->pausedText = new Text("Tam dung. Nhan P de tiep tuc.\nNhan Esc de thoat.", *font, 64U);
	this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
	this->pausedText->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	//Chữ khi người 1 thắng
	this->win = new Text("Thang!\nNhan Enter de choi lai!\nNhan Esc de thoat!", *font, 64U);
	this->win->setOrigin(this->win->getGlobalBounds().width / 2, this->win->getGlobalBounds().height / 2);
	this->win->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	//Chữ khi người 2 thắng
	this->lose = new Text("Thua!\nNhan Enter de choi lai!\nNhan Esc de thoat!", *font, 64U);
	this->lose->setOrigin(this->lose->getGlobalBounds().width / 2, this->lose->getGlobalBounds().height / 2);
	this->lose->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	this->paused = false;
	this->enterKey = false;
	this->endGame = false;
}

void mainGame_Brick::CapNhat(RenderWindow* window)
{
	if (paused)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::P) && !enterKey)
		{
			paused = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			coreState.SetTrangThai(new Menu());
		}
	}
	else if(ball->getLive() == 0)
	{
		endGame = true; 
	}
	// con 1 truong hop thang nua
	else {
		ball->CapNhat(window);
		player->CapNhat(window);
		point->CapNhat();
		if (Keyboard::isKeyPressed(Keyboard::Key::P) && !enterKey) 
			paused = true;
		enterKey = Keyboard::isKeyPressed(Keyboard::Key::P);
		if (Keyboard::isKeyPressed(Keyboard::Key::Space))
			ball->reset(window); 
	}
	this->enterKey = Keyboard::isKeyPressed(Keyboard::Key::P);
}


void mainGame_Brick::Xuat(RenderWindow* window)
{
	window->draw(*ball); 
	window->draw(*player); 
	window->draw(*point); 
	if (paused)
	{
		window->draw(*pausedText); 
	}
	// xu li endgame o day
	if (endGame)
	{
		if (ball->getLive() == 0) // truong hop thua
		{
			window->draw(*win);
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
			{
				coreState.SetTrangThai(new mainGame_Brick());
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				coreState.SetTrangThai(new Menu());
			}
		}
		else // truong hop thang
		{
			window->draw(*lose);
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
			{
				coreState.SetTrangThai(new mainGame_Brick());
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				coreState.SetTrangThai(new Menu());
            }
		}
	}
}

void mainGame_Brick::Destroy(RenderWindow* window)
{
	delete player; 
	delete ball; 
	delete font; 
}
