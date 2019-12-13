#include "Brick_Prize.h"


// constructor tạo vật phẩm ngẫu nhiên
Brick_Prize::Brick_Prize()
{
	type = randomNumber(1, 5); // lấy số random 5 loại => mỗi loại sẽ có tỉ lệ 20% sinh ra khi vật phẩm mới sinh ra
	switch (type)
	{
	case 1 : 
		cout << "Prize x2 score created. " << endl; 
		break;
	case 2 : 
		cout << "Prize /2 score created. " << endl; 
		break; 
	case 3: 
		cout << "Prize x2 paddle length created. " << endl; 
		break; 
	case 4: 
		cout << "Prize /2 paddle length created. " << endl; 
		break; 
	case 5: 
		cout << "Prize increase lives created. " << endl; 
		break;
	}
	if (type == 5) // cho tim rơi xuống nhanh hơn
	{
		speed.x = 0.f; 
		speed.y = 1.6f;
	}
	else
	{
		speed.x = 0.f;
		speed.y = 1.3f;
	}
	// ban đầu tạo ra ở vị trí của viên gạch bị phá nên chưa chạm người chơi/sàn
	touched_player = false; 
	touched_floor = false;
}
// constructor truyền loại vật phẩm mong muốn. 
Brick_Prize::Brick_Prize(int _type)
{
	type = _type; 
	speed.x = 0.f; 
	if (type != 5)
	{
		speed.y = 1.3; 
	}
	else
	{
		speed.y = 1.6; 
	}
	touched_player = false;
	touched_floor = false;
}

void Brick_Prize::CapNhat(ThanhNguoiChoi_Brick*& player, DiemSo*& point, Ball_BrickGame*& _ball)
{
	VatThe::CapNhat();
	if (KiemTraVaCham(player))
	{
		touched_player = true; // chuyển đổi thành đã va chạm
		switch (type)
		{
		case 1: // tăng điểm
			point->setDiem(point->GetDiem() * 2);
			break; 
		case 2: // giảm điểm
			point->setDiem(point->GetDiem() / 2); 
			break; 
		case 3: // tăng chiều dài thanh
			if (player->getScale().x <= 2.f) // giới hạn không cho thanh to vượt mức
			{
				player->setScale(player->getScale().x * 2, 1.0); // tăng chiều dài hoành độ 2 lần
				//_ball->setPlayer(player);
			}
			break; 
		case 4: // giảm chiều dài thanh
			if(player->getScale().x >= 0.5f)  // giới hạn không cho thanh nhỏ vượt mức
			player->setScale(player->getScale().x / 2, 1.0); // giảm chiều dài hoành độ 2 lần
			//_ball->setPlayer(player);
			break; 
		case 5:
			if (_ball->getLive() < 6) // tối đa 6 mạng
			{
				_ball->increaseLive(); // tăng số mạng hiện có
			}
			break; 
		}
	}
	if (getPosition().y > player->getPosition().y + 20)
	{
		touched_floor = true; // đã chạm sàn (vượt qua người chơi) 
	}

}

void Brick_Prize::CapNhat(Thanh_Bot_Brick*& botPlayer, DiemSo*& point, Ball_BrickGame*& _ball)
{
	VatThe::CapNhat();
	if (KiemTraVaCham(botPlayer))
	{
		touched_player = true; // chuyển đổi thành đã va chạm
		switch (type)
		{
		case 1: // tăng điểm
			point->setDiem(point->GetDiem() * 2);
			break;
		case 2: // giảm điểm
			point->setDiem(point->GetDiem() / 2);
			break;
		case 3: // tăng chiều dài thanh
			if (botPlayer->getScale().x <= 2.f) // giới hạn không cho thanh to vượt mức
			{
				botPlayer->setScale(botPlayer->getScale().x * 2, 1.0); // tăng chiều dài hoành độ 2 lần
				//_ball->setPlayer(player);
			}
			break;
		case 4: // giảm chiều dài thanh
			if (botPlayer->getScale().x >= 0.5f)  // giới hạn không cho thanh nhỏ vượt mức
				botPlayer->setScale(botPlayer->getScale().x / 2, 1.0); // giảm chiều dài hoành độ 2 lần
				//_ball->setPlayer(player);
			break;
		case 5:
			if (_ball->getLive() < 6) // tối đa 6 mạng
			{
				_ball->increaseLive(); // tăng số mạng hiện có
			}
			break;
		}
	}
	if (getPosition().y > botPlayer->getPosition().y + 20)
	{
		touched_floor = true; // đã chạm sàn (vượt qua người chơi) 
	}
}

void Brick_Prize::TaoTexture() // load hình ảnh vào, tuỳ vào loại
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
	case 5: 
		Load("Heart.png"); 
		break; 
	}
}


