#include "mainGame_Custom.h"
#include "Menu.h"
void mainGame_Custom::KhoiTao(RenderWindow* window)
{
	window->setFramerateLimit(120);
	background.loadFromFile("Graphics/sprites/InGameBackground.png");
	select.x = 1;
	select.y = 5;
	Vector2f size;
	size.x = 90;
	size.y = 30;
	LuaChon.setSize(size);
	LuaChon.setOutlineThickness(5);
	LuaChon.setOutlineColor(Color::Cyan);
	LuaChon.setFillColor(Color::Transparent);
	LuaChon.setPosition(select.x * 90, select.y * 30);
	this->paused = false;
	this->enterKey = false;
	this->endGame = false;
	quitGame = false;
	tex_ID = 0;
	tam = new Brick_BrickGame;
	//Chủ đề
	tiltle1.setCharacterSize(75);
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font3.ttf");
	tiltle1.setFont(*font);
	tiltle1.setFillColor(Color::Yellow);
	tiltle1.setString("Left/Right: Move\nUp/Down: Change brick");
	tiltle1.setPosition(100, 600);
	tiltle2.setCharacterSize(75);
	tiltle2.setFont(*font);
	tiltle2.setFillColor(Color::Yellow);
	tiltle2.setString("Enter: Set brick\nEcs: Save and Quit");
	tiltle2.setPosition(800, 600);
}

void mainGame_Custom::CapNhat(RenderWindow* window)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		fstream f;
		f.open("BrickLevel/level6.txt", ios::out);
		for (int i = 0; i < brick.size(); i++)
		{
			f << brick[i]->getPosition().x << " " << brick[i]->getPosition().y << " " << brick[i]->getShieldNumber() << " " << brick[i]->getBrickColor() << endl;
		}
		coreState.SetTrangThai(new Menu());
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Left)&&!leftKey)
	{
		if (select.x > 1)
		{
			select.x--;
		}
		else
		{
			select.x = 12;
			select.y--;
			if (select.y == 4)
			{
				select.y = 16;
			}
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right)&&!rightKey)
	{
		if (select.x < 12)
		{
			select.x++;
		}
		else
		{
			select.x = 1;
			select.y++;
			if (select.y == 17)
			{
				select.y = 5;
			}
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !upKey)
	{
		if (tex_ID > 1)
		{
			tex_ID--;
		}
		else
		{
			tex_ID = 19;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down) && !downKey)
	{
		if (tex_ID < 19)
		{
			tex_ID++;
		}
		else
		{
			tex_ID = 0;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Enter) && !enterKey)
	{
		if (tex_ID != 0)
		{
			brick.push_back(tam);
			tex_ID = 0;
			tam = new Brick_BrickGame;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace) && !backKey)
	{
		brick.erase(brick.begin() + brick.size() -  1);
	}
	this->leftKey = Keyboard::isKeyPressed(Keyboard::Key::Left);
	this->rightKey = Keyboard::isKeyPressed(Keyboard::Key::Right);
	this->upKey = Keyboard::isKeyPressed(Keyboard::Key::Up);
	this->downKey = Keyboard::isKeyPressed(Keyboard::Key::Down);
	this->enterKey = Keyboard::isKeyPressed(Keyboard::Key::Enter);
	this->backKey = Keyboard::isKeyPressed(Keyboard::Key::BackSpace);
	LuaChon.setOrigin(90.f / 2.f, 30.f / 2.f);
	LuaChon.setPosition(select.x * 90, select.y * 30);
}

void mainGame_Custom::Xuat(RenderWindow* window)
{
	//vẽ background
	Sprite sp(background);
	window->draw(sp);
	window->draw(tiltle1);
	window->draw(tiltle2);
	for (int i = 0; i < brick.size(); i++)
	{
		window->draw(*brick[i]);
	}
	window->draw(LuaChon);
	//Vẽ lữa chọn tạm thời
	if (tex_ID != 0)
	{
		tam->setPosition(select.x * 90, select.y * 30);
		if (tex_ID == 19)
		{
			tam->setShieldNumber(4);
			tam->setBrickColor('m');
		}
		else
		{
			tam->setShieldNumber(((tex_ID - 1) % 3) + 1);
			if (tex_ID==1 || tex_ID==2 || tex_ID==3)
			{
				tam->setBrickColor('b');
			}
			if (tex_ID == 4 || tex_ID == 5 || tex_ID == 6)
			{
				tam->setBrickColor('g');
			}
			if (tex_ID == 7 || tex_ID == 8 || tex_ID == 9)
			{
				tam->setBrickColor('o');
			}
			if (tex_ID == 10 || tex_ID == 11 || tex_ID == 12)
			{
				tam->setBrickColor('r');
			}
			if (tex_ID == 13 || tex_ID == 14 || tex_ID == 15)
			{
				tam->setBrickColor('v');
			}
			if (tex_ID == 16 || tex_ID == 17 || tex_ID == 18)
			{
				tam->setBrickColor('y');
			}
		}
		Vector2f brickSize;
		brickSize.x = 90;
		brickSize.y = 30;
		tam->setOrigin(brickSize / 2.f);
		tam->TaoTexture();
	}
	window->draw(*tam);
	quitGame = false;
}

void mainGame_Custom::Destroy(RenderWindow* window)
{
	mainGame_Brick::Destroy(window);
}
