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

void Brick_Prize::CapNhat(ThanhNguoiChoi_Brick*& player, DiemSo*& point)
{
	VatThe::CapNhat();
	if (KiemTraVaCham(player))
	{
		touched_player = true;
		switch (type)
		{
		case 1:
			point->setDiem(point->GetDiem() * 2);
		case 2: 
			point->setDiem(point->GetDiem() / 2); 
		case 3: 
			player->setScale(2.0, 1.0); 
		case 4: 
			player->setScale(0.5, 1.0);
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
	case 2: 
		Load("object12.png");
	case 3 : 
		Load("objectIncreaseLength.png");
	case 4 : 
		Load("objectDecreaseLength.png"); 
	}
}


