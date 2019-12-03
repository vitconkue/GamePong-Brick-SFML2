#include "Brick_BrickGame.h"


Brick_BrickGame::Brick_BrickGame()
{
	
}

void Brick_BrickGame::setShieldNumber(int number)
{
	Shield = number;
}

int Brick_BrickGame::getShieldNumber()
{
	return Shield;
}

void Brick_BrickGame::CapNhat(Ball_BrickGame*& m_ball)
{
	Vector2f brickPos = this->getPosition();
	Vector2f ballPos = m_ball->getPosition();
	Vector2f brickSize(getGlobalBounds().width, getGlobalBounds().height);
	if (KiemTraVaCham(m_ball))
	{
		int top = abs(ballPos.y - brickPos.y - brickSize.y/2);
		int bot = abs(ballPos.y - brickPos.y + brickSize.y/2);
		int left = abs(ballPos.x - brickPos.x - brickSize.x / 2);
		int right = abs(ballPos.x - brickPos.x + brickSize.x / 2);
		int min = top;
		if (bot < min)
		{
			min = bot;
		}
		if (left < min)
		{
			min = left;
		}
		if (right < min)
		{
			min = right;
		}
		if (min == top || min == bot)
		{
			m_ball->VanToc.y *= -1;
		}
		if (min == left || min == right)
		{
			m_ball->VanToc.x *= -1;
		}
		Shield--;
		TaoTexture();
	}
}

void Brick_BrickGame::TaoTexture()
{
	if (Shield == 3)
	{
		Load("BlueBrick3.png");
	}
	else if (Shield == 2)
	{
		Load("BlueBrick2.png");
	}
	else if (Shield == 1)
	{
		Load("BlueBrick1.png");
	}
}