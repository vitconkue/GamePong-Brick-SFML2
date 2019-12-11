#include "mainGame_Brick.h"

void mainGame_Brick::KhoiTao(RenderWindow* window)
{
	window->setFramerateLimit(120);
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
	Effect = 1;
	LoadBrick();
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
	else if (ball->getLive() == 0)
	{
		endGame = true;
	}
	else if (brick.empty()) endGame = true; 
	else {
		ball->CapNhat(window, point);
		player->CapNhat(window);
		//Cap Nhap Brick
		for (int i = 0; i < brick.size(); i++)
		{
			brick[i]->CapNhat(ball, point);
		}
		for (int i = 0; i < brick.size(); i++)
		{
			if (brick[i]->getShieldNumber() == 0)
			{
				Brick_Prize* newPrize = new Brick_Prize; 
				newPrize->TaoTexture(); 
				newPrize->setPosition(brick[i]->getPosition()); 
				prize.push_back(newPrize);
				brick.erase(brick.begin() + i);
			}
		}
		// Cap nhat vat the
		   // cap nhat tung vat the
		for (int i = 0; i < prize.size(); i++)
		{
			prize[i]->CapNhat(player,point,ball); 
		}
		   // xoa vat the khoi man hinh
		for (int i = 0; i < prize.size(); i++)
		{
			if (prize[i]->getTouchedPlayer() || prize[i]->getTouchedFloor())
			{
				prize.erase(prize.begin() + i);
			}
		}
		point->CapNhat();
		if (Keyboard::isKeyPressed(Keyboard::Key::P) && !enterKey) 
			paused = true;
		enterKey = Keyboard::isKeyPressed(Keyboard::Key::P);
		if (Keyboard::isKeyPressed(Keyboard::Key::Space))
			ball->reset(window); 
	}
	this->enterKey = Keyboard::isKeyPressed(Keyboard::Key::P);
	//Cap nhật hiệu ứng Paddle
	Effect++;
	if (Effect == 61)
	{
		Effect == 1;
	}
	if (Effect < 20)
	{
		player->Load("BPaddle1.png");
		Effect++;
	}
	else if (Effect >= 20&&Effect <= 40)
	{
		player->Load("BPaddle2.png");
		Effect++;
	}
	else if(Effect > 40)
	{
		player->Load("BPaddle3.png");
		Effect = 1;
	}
}


void mainGame_Brick::Xuat(RenderWindow* window)
{
	window->draw(*ball); 
	window->draw(*player); 
	window->draw(*point); 
	for (int i = 0; i < brick.size(); i++)
	{
		window->draw(*brick[i]);
	}
	for (int i = 0; i < prize.size(); i++)
	{
		window->draw(*prize[i]); 
	}
	if (paused)
	{
		window->draw(*pausedText); 
	}
	// xu li endgame o day
	if (endGame)
	{
		if (ball->getLive() == 0) // truong hop thua
		{
			window->draw(*lose);
			InputName(); 
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
			window->draw(*win);
			InputName(); 
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

void mainGame_Brick::InputName()
{
	std::string nm;
	cout << "Player Name: ";
	getline(cin, nm);
	fstream f;
	int currentNum;
	f.open("Highscores.txt", ios::in);
	f >> currentNum;
	f.close();
	currentNum = currentNum + 1;
	f.close();
	f.open("Highscores.txt", ios::in | ios::out);
	f << currentNum;
	f.close();
	fstream fout;
	fout.open("Highscores.txt", fstream::app);
	fout << nm << ":" << point->GetDiem() << endl;
	fout.close();
}

void mainGame_Brick::LoadBrick()
{
	for (int i = 1; i < 6; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			Vector2f brickSize;
			brickSize.x = 90;
			brickSize.y = 30;
			Brick_BrickGame* b = new Brick_BrickGame;
			b->setShieldNumber(3);
			b->setPosition(i * 200, j * 200);
			b->setOrigin(brickSize / 2.f);
			b->TaoTexture();
			brick.push_back(b);
		}
	}

}
