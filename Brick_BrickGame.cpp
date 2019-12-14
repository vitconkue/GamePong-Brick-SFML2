#include "Brick_BrickGame.h"


Brick_BrickGame::Brick_BrickGame()
{
	buffer = new SoundBuffer();
	sound = new Sound();
	buffer->loadFromFile("Sounds/Brick.wav");
	sound->setBuffer(*buffer);
}

void Brick_BrickGame::setShieldNumber(int number)
{
	Shield = number;
}

int Brick_BrickGame::getShieldNumber()
{
	return Shield;
}

void Brick_BrickGame::CapNhat(Ball_BrickGame*& m_ball, DiemSo*& point)
{
	Vector2f brickPos = this->getPosition();
	Vector2f ballPos = m_ball->getPosition();
	Vector2f brickSize(getGlobalBounds().width, getGlobalBounds().height);
	Vector2f ballSize(m_ball->getGlobalBounds().width, m_ball->getGlobalBounds().height);
	if (KiemTraVaCham(m_ball))
	{
		sound->play();
		if (m_ball->speed.x > 0 && m_ball->speed.y < 0)
		{
			if (ballPos.x > brickPos.x - brickSize.x / 2 + ballSize.x / 2)
			{
				m_ball->speed.y *= -1;
			}
			else if(ballPos.y < brickPos.y + brickSize.y / 2 - ballSize.y / 2)
			{
				m_ball->speed.x *= -1;
			}
			else
			{
				m_ball->speed.x *= -1;
				m_ball->speed.y *= -1;
			}
		}
		else if (m_ball->speed.x > 0 && m_ball->speed.y > 0)
		{
			if (ballPos.x > brickPos.x - brickSize.x / 2 + ballSize.x / 2)
			{
				m_ball->speed.y *= -1;
			}
			else if (ballPos.y > brickPos.y - brickSize.y / 2 + ballSize.y / 2)
			{
				m_ball->speed.x *= -1;
			}
			else
			{
				m_ball->speed.x *= -1;
				m_ball->speed.y *= -1;
			}
		}
		else if (m_ball->speed.x < 0 && m_ball->speed.y < 0)
		{
			if (ballPos.x < brickPos.x + brickSize.x / 2 - ballSize.x/2)
			{
				m_ball->speed.y *= -1;
			}
			else if(ballPos.y < brickPos.y + brickSize.y / 2 - ballSize.y / 2)
			{
				m_ball->speed.x *= -1;
			}
			else
			{
				m_ball->speed.x *= -1;
				m_ball->speed.y *= -1;
			}
		}
		else if (m_ball->speed.x < 0 && m_ball->speed.y > 0)
		{
			if (ballPos.x < brickPos.x + brickSize.x / 2  - ballSize.x/2)
			{
				m_ball->speed.y *= -1;
			}
			else if(ballPos.y > brickPos.y - brickSize.y / 2 + ballSize.y / 2)
			{
				m_ball->speed.x *= -1;
			}
			else
			{
				m_ball->speed.x *= -1;
				m_ball->speed.y *= -1;
			}
		}
		if (Shield < 4) // Shield = 4 là gạch vật cản, không thể phá
		{
			Shield--;
			if (Shield == 0)
			{
				point->TangThem(100); // nếu phá được gạch + 100 điểm
			}
			else
			{
				point->TangThem(50); // chạm nhưng không phá được gạch + 50 điểm
			}
		}
		if (Shield != 5)
		{
			TaoTexture();
		}
	}
}

void Brick_BrickGame::CapNhat_Findway(Ball_BrickGame*& m_ball, DiemSo*& point)
{
	Vector2f brickPos = this->getPosition();
	Vector2f ballPos = m_ball->getPosition();
	Vector2f brickSize(getGlobalBounds().width, getGlobalBounds().height);
	Vector2f ballSize(m_ball->getGlobalBounds().width, m_ball->getGlobalBounds().height);
	Vector2f saveballPos = ballPos;
	if (KiemTraVaCham(m_ball))
	{
		m_ball->speed.y *= -1;
		m_ball->move(m_ball->speed);
		if (KiemTraVaCham(m_ball))
		{
			m_ball->setPosition(saveballPos);
			m_ball->speed.x *= -1;
			m_ball->speed.y *= -1;
		}
		else
		{
			m_ball->setPosition(saveballPos);
		}
		if (Shield != 4) // Shield = 4 là gạch vật cản, không thể phá
		{
			Shield--;
			if (Shield == 0)
			{
				point->TangThem(100); // nếu phá được gạch + 100 điểm
			}
			else
			{
				point->TangThem(50); // chạm nhưng không phá được gạch + 50 điểm
			}
		}
	}
}

void Brick_BrickGame::TaoTexture()
{
	// tuỳ vào trạng thái hiện tại của gạch mà lấy texture phù hợp để vẽ lên màn hình
	if (Shield == 4)
	{
		Load("MaxBrick.png"); // vật cản
	}
	else if (Shield == 3)
	{
		switch (BrickColor)
		{
		case 'b':
		{
			Load("BlueBrick3.png");
			break;
		}
		case 'g':
		{
			Load("GreenBrick3.png");
			break;
		}
		case 'o':
		{
			Load("OrangeBrick3.png");
			break;
		}
		case 'r':
		{
			Load("RedBrick3.png");
			break;
		}
		case 'v':
		{
			Load("VioletBrick3.png");
			break;
		}
		case 'y':
		{
			Load("YellowBrick3.png");
			break;
		}
		}
	}
	else if (Shield == 2)
	{
		switch (BrickColor)
		{
		case 'b':
		{
			Load("BlueBrick2.png");
			break;
		}
		case 'g':
		{
			Load("GreenBrick2.png");
			break;
		}
		case 'o':
		{
			Load("OrangeBrick2.png");
			break;
		}
		case 'r':
		{
			Load("RedBrick2.png");
			break;
		}
		case 'v':
		{
			Load("VioletBrick2.png");
			break;
		}
		case 'y':
		{
			Load("YellowBrick2.png");
			break;
		}
		}
	}
	else if (Shield == 1)
	{
		switch (BrickColor)
		{
		case 'b':
		{
			Load("BlueBrick1.png");
			break;
		}
		case 'g':
		{
			Load("GreenBrick1.png");
			break;
		}
		case 'o':
		{
			Load("OrangeBrick1.png");
			break;
		}
		case 'r':
		{
			Load("RedBrick1.png");
			break;
		}
		case 'v':
		{
			Load("VioletBrick1.png");
			break;
		}
		case 'y':
		{
			Load("YellowBrick1.png");
			break;
		}
		}
	}
}

char Brick_BrickGame::getBrickColor()
{
	return BrickColor;
}

void Brick_BrickGame::setBrickColor(char a)
{
	BrickColor = a;
}

Brick_BrickGame::~Brick_BrickGame()
{
	delete this->buffer;
	delete this->sound;
}