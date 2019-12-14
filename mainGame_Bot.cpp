#include "mainGame_Bot.h"
#include "Menu.h"
void mainGame_Bot::KhoiTao(RenderWindow* window)
{
	mainGame_Brick::KhoiTao(window);
	botPlayer = new Thanh_Bot_Brick(); 
	botPlayer->setPosition(window->getSize().x / 2, window->getSize().y - 20);
	botPlayer->setScale(1.0, 1.0);
}

void mainGame_Bot::CapNhat(RenderWindow* window)
{
	if (paused)
	{
		int choose = PauseGame(window);
		if (choose == 1)
		{
			coreState.SetTrangThai(new Menu());
			return;
		}
		if (choose == 2)
		{
			SaveGame("Save/1.txt");
			paused = false;
		}
		if (choose == 3)
		{
			//KhoiTao(window);
			LoadGame("Save/1.txt");
			paused = false;
		}
	}
	else if (ball->getLive() == 0) // hết mạng => thua, kết thúc game
	{
		endGame = true;
	}
	else if (checkCleanAllBrick()) endGame = true;  // hết gạch có thể phá=> thắng, kết thúc game
	else {
		// cập nhật các yếu tố liên quan bóng
		ball->CapNhat(window, point, botPlayer, hearts);
		// cập nhật các yếu tố liên quan thanh trượt
		botPlayer->CapNhat(window,ball);
		//Cập nhật gạch
		for (int i = 0; i < brick.size(); i++)
		{
			brick[i]->CapNhat(ball, point);
		}
		for (int i = 0; i < brick.size(); i++)
		{

			if (brick[i]->getShieldNumber() == 0) // đã phá được gạch
			{
				int p_factor = randomNumber(1, 2); // tạo random 2 số 1 hoặc 2
				if (p_factor == 1) // chọn 1 số làm điều kiện tạo mới vật phẩm => tỉ lệ 50% tạo ra vật phẩm
				{
					// tạo vật phẩm mới, cho vào vector
					Brick_Prize* newPrize = new Brick_Prize;
					newPrize->TaoTexture();
					newPrize->setPosition(brick[i]->getPosition()); // vị trí ban đầu ở vị trí gạch bị vỡ
					prize.push_back(newPrize);
				}
				brick.erase(brick.begin() + i); // xoá gạch đã phá
			}
		}
		// Cập nhật vật thể
		   // Cập nhật từng vật thể
		for (int i = 0; i < prize.size(); i++)
		{
			prize[i]->CapNhat(botPlayer, point, ball);
		}
		// xoá vật thể 
		for (int i = 0; i < prize.size(); i++)
		{
			if (prize[i]->getTouchedPlayer() || prize[i]->getTouchedFloor())
			{
				prize.erase(prize.begin() + i);
			}
		}
		// cập nhật điểm
		point->CapNhat();
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape) && !enterKey)
		{
			paused = true;
		}
	}
	this->enterKey = Keyboard::isKeyPressed(Keyboard::Key::Enter);
	//Cập nhật hiệu ứng thanh người chơi
	// biến Effect liên tục thay đổi, mỗi lần thay đổi lại load một texture khác
	Effect++;
	if (Effect == 61)
	{
		Effect == 1;
	}
	if (Effect < 20)
	{
		botPlayer->Load("BPaddle1.png");
		Effect++;
	}
	else if (Effect >= 20 && Effect <= 40)
	{
		botPlayer->Load("BPaddle2.png");
		Effect++;
	}
	else if (Effect > 40)
	{
		botPlayer->Load("BPaddle3.png");
		Effect = 1;
	}
}

void mainGame_Bot::Xuat(RenderWindow* window)
{
	//vẽ background
	Sprite sp(background);
	window->draw(sp);
	// vẽ tất cả các thành phần game
	window->draw(*ball);
	window->draw(*botPlayer);
	window->draw(*point);
	for (int i = 0; i < ball->getLive(); i++)
	{
		window->draw(*hearts[i]);
	}
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
}



void mainGame_Bot::Destroy(RenderWindow* window)
{
	mainGame_Brick::Destroy(window);
	delete botPlayer;
}
