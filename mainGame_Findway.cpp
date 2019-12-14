#include "mainGame_Findway.h"
#include "Menu.h"
void mainGame_Findway::KhoiTao(RenderWindow* window)
{
	//set font
	window->setFramerateLimit(120);
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font3.ttf");
	player = new ThanhNguoiChoi_Brick;
	player->setPosition(window->getSize().x / 2, window->getSize().y - 20);
	player->setScale(1.0, 1.0);
	point = new DiemSo(*font, 64U);
	ball = new Ball_BrickGame(point);
	ball->reset(window, player);
	Vector2f s;
	s.x = 0;
	s.y = 0;
	ball->setSpeed(s);
	Effect = 1;
	background.loadFromFile("Graphics/sprites/InGameBackground.png");
	angle = 1;
	ballMove = false;
	//Set win Brick
	winBrick = new Brick_BrickGame;
	winBrick->setBrickColor('x');
	winBrick->Load("RedBrick3.png");
	Vector2f brickSize;
	brickSize.x = 90;
	brickSize.y = 30;
	winBrick->setOrigin(brickSize / 2.f);
	winBrick->setPosition(240, 650);
	//Set win text
	win = new Text("You win\nPress Space to Replay\nPress Ecs to Quit", *this->font, 110U);
	win->setPosition(400, 200);
	win->setFillColor(Color::Yellow);
	win->setCharacterSize(100);
	LoadWay();
	endgame = false;
}

void mainGame_Findway::CapNhat(RenderWindow* window)
{
	//Cập nhat góc
	if (Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		AngleDown(angle);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		AngleUp(angle);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Enter)&&!enterKey)
	{
		Vector2f newSpeed = TaoGoc(angle);
		newSpeed.x /= 50;
		newSpeed.y /= 50;
		ball->setSpeed(newSpeed);
		ballMove = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		coreState.SetTrangThai(new Menu());
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Space))
	{
		KhoiTao(window);
	}
	//Kiểm tra điều kiện thắng
	if (winBrick->KiemTraVaCham(ball))
	{
		endgame = true;
		ballMove = false;
	}
	//Cập nhật hướng
	if (!ballMove)
	{
		Vector2f huong = TaoGoc(angle);
		ball->setPosition(600 + huong.x, 840 + huong.y);
	}
	//Cập nhật brick;
	for (int i = 0; i < brick.size(); i++)
	{
		brick[i]->CapNhat(ball, point);
	}
	//Cập nhật bóng
	// kiểm tra va chạm với thanh
	sf::Vector2u playerSize = Vector2u(player->getGlobalBounds().width, player->getGlobalBounds().height);
	if (ball->getPosition().x >= player->getPosition().x - playerSize.x / 2 - 5 &&
		ball->getPosition().x <= player->getPosition().x + playerSize.x / 2 + 5)
	{
		if (ball->getPosition().y >= player->getPosition().y - playerSize.y / 2)
		{
			KhoiTao(window);
		}
	}
	// chạm tường trên
	if (ball->getPosition().y < 0)
	{
		ball->speed.y *= -1;
	}
	// chạm tường dưới
	if (ball->getPosition().y > player->getPosition().y - player->getGlobalBounds().height / 2 + 2)
	{
		KhoiTao(window);
	}
	// chạm tường trái phải
	if (ball->getPosition().x < 0 || ball->getPosition().x + ball->getGlobalBounds().width >= window->getSize().x)
	{
		ball->speed.x *= -1;
	}
	ball->move(ball->getSpeed()); // di chuyển theo vector vận tốc hiện thời
	//Cập nhật hiệu ứng thanh người chơi
	// biến Effect liên tục thay đổi, mỗi lần thay đổi lại load một texture khác
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
	else if (Effect >= 20 && Effect <= 40)
	{
		player->Load("BPaddle2.png");
		Effect++;
	}
	else if (Effect > 40)
	{
		player->Load("BPaddle3.png");
		Effect = 1;
	}
	this->enterKey= Keyboard::isKeyPressed(Keyboard::Key::Enter);
	quitGame = false;
}

void mainGame_Findway::Xuat(RenderWindow* window)
{
	//vẽ background
	Sprite sp(background);
	window->draw(sp);
	// vẽ tất cả các thành phần game
	window->draw(*ball);
	window->draw(*player);
	window->draw(*point);
	for (int i = 0; i < brick.size(); i++)
	{
		window->draw(*brick[i]);
	}
	window->draw(*winBrick);
	if (endgame)
	{
		window->draw(*win);
	}
	// xử lí thắng thua
	if (endGame)
	{
		if (ball->getLive() == 0) // trường hợp thua
		{
			int choose = EndGame(window);
			if (choose == 0)
			{
				InputName(window);
				coreState.SetTrangThai(new mainGame_Brick());
			}
			else if (choose == 1)
			{
				InputName(window);
				coreState.SetTrangThai(new Menu());
			}
		}
		else // trường hợp thắng
		{
			int choose = EndGame(window);
			if (choose == 0)
			{
				InputName(window);
				mainGame_Brick* maingame = new mainGame_Brick();
				coreState.SetTrangThai(maingame);
			}
			else if (choose == 1)
			{
				InputName(window);
				coreState.SetTrangThai(new Menu());
			}
		}
	}
	quitGame = false;
}

void mainGame_Findway::Destroy(RenderWindow* window)
{
	mainGame_Brick::Destroy(window);
}

Vector2f mainGame_Findway::TaoGoc(int angle)
{

	Vector2f speed;
	double curSpeed = 100;
	double P = double(angle) / (40);
	speed.y = -sqrt((curSpeed * curSpeed) / (P * P + 1));
	speed.x = speed.y * P;
	return speed;
}

void mainGame_Findway::AngleUp(int& angle)
{
	if (angle == 160)
	{
		return;
	}
	else if (angle == -1)
	{
		angle = 1;
		return;
	}
	else
	{
		angle++;
	}
}

void mainGame_Findway::AngleDown(int& angle)
{
	if (angle == -160)
	{
		return;
	}
	if (angle == 1)
	{
		angle = -1;
		return;
	}
	else
	{
		angle--;
	}
}

void mainGame_Findway::LoadWay()
{
	brick.clear();
	Brick_BrickGame* b = new Brick_BrickGame;
	Vector2f brickSize;
	brickSize.x = 30;
	brickSize.y = 540;
	b->Load("Findway/1.png");
	b->setPosition(150, 400);
	b->setShieldNumber(5);
	b->setBrickColor('x');
	b->setOrigin(brickSize / 2.f);
	brick.push_back(b);
	Brick_BrickGame* c = new Brick_BrickGame;
	c->Load("Findway/2.png");
	brickSize.x = 30;
	brickSize.y = 360;
	c->setPosition(330, 490);
	c->setShieldNumber(5);
	c->setBrickColor('x');
	c->setOrigin(brickSize / 2.f);
	brick.push_back(c);
	Brick_BrickGame* d = new Brick_BrickGame;
	d->Load("Findway/3.png");
	brickSize.x = 450;
	brickSize.y = 30;
	d->setPosition(540, 295);
	d->setShieldNumber(5);
	d->setBrickColor('x');
	d->setOrigin(brickSize / 2.f);
	brick.push_back(d);
	Brick_BrickGame* e = new Brick_BrickGame;
	e->Load("Findway/2.png");
	brickSize.x = 30;
	brickSize.y = 360;
	e->setShieldNumber(5);
	e->setBrickColor('x');
	e->setOrigin(brickSize / 2.f);
	e->setPosition(750, 490);
	brick.push_back(e);
	Brick_BrickGame* f = new Brick_BrickGame;
	f->Load("Findway/4.png");
	brickSize.x = 810;
	brickSize.y = 30;
	f->setShieldNumber(5);
	f->setBrickColor('x');
	f->setOrigin(brickSize / 2.f);
	f->setPosition(540, 115);
	brick.push_back(f);
	Brick_BrickGame* g = new Brick_BrickGame;
	g->Load("Findway/1.png");
	brickSize.x = 30;
	brickSize.y = 540;
	g->setPosition(930, 400);
	g->setShieldNumber(5);
	g->setBrickColor('x');
	g->setOrigin(brickSize / 2.f);
	brick.push_back(g);
	Brick_BrickGame* h = new Brick_BrickGame;
	h->Load("Findway/2.png");
	brickSize.x = 30;
	brickSize.y = 360;
	h->setPosition(330, 850);
	h->setShieldNumber(5);
	h->setBrickColor('x');
	h->setOrigin(brickSize / 2.f);
	brick.push_back(h);
}
