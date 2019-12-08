#include "Brick_Prize.h"

Brick_Prize::Brick_Prize()
{
	srand(time(0)); 
	int k = rand(); 
	k = k % 4;
	type = k + 1; 
	cout << "Type: " << type << endl; 
	VanToc.x = 0.f; 
	VanToc.y = 1.5f;
	touched_player = false; 
	touched_floor = false;
}

void Brick_Prize::CapNhat(ThanhNguoiChoi_Brick*& player, DiemSo*& point, Ball_BrickGame*& _ball)
{
	VatThe::CapNhat();
	if (KiemTraVaCham(player))
	{
		touched_player = true;
		switch (type)
		{
		case 1:
			point->setDiem(point->GetDiem() * 2);
			break; 
		case 2: 
			point->setDiem(point->GetDiem() / 2); 
			break; 
		case 3: 
			player->setScale(player->getScale().x * 2, 1.0); 
			_ball->setPlayer(player); 
			break; 
		case 4: 
			player->setScale(player->getScale().x / 2, 1.0);
			_ball->setPlayer(player);
			break; 
		}
	}
	if (getPosition().y > player->getPosition().y + 20)
	{
		touched_floor = true; 
	}

}

void Brick_Prize::TaoTexture()
{
	switch (type)
	{
	case 1: 
		Load("object2.png");
		break; 
	case 2: 
		Load("object12.png");
		break; 
	case 3 : 
		Load("objectIncreaseLength.png");
		break; 
	case 4 : 
		Load("objectDecreaseLength.png"); 
		break; 
	}
}


