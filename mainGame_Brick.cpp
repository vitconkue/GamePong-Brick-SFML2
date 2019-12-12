#include "mainGame_Brick.h"

// Khởi tạo ban đầu
void mainGame_Brick::KhoiTao(RenderWindow* window)
{
	window->setFramerateLimit(120);
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font2.ttf");
	player = new ThanhNguoiChoi_Brick;
	point = new DiemSo(*font, 64U);
	ball = new Ball_BrickGame(point, player); 
	ball->reset(window); 
	this->pausedText = new Text("Paused. Press P to continue.\nPress Esc to exit.\nPress S to Save, Press L to Load.", *font, 64U);
	this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
	this->pausedText->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	//Chữ khi thắng
	this->win = new Text("Win!\nPress A to play again!\nPress Esc to exit!", *font, 64U);
	this->win->setOrigin(this->win->getGlobalBounds().width / 2, this->win->getGlobalBounds().height / 2);
	this->win->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	//Chữ khi thua
	this->lose = new Text("Lose!\nPress A to paly again!\nPress Esc to exit!", *font, 64U);
	this->lose->setOrigin(this->lose->getGlobalBounds().width / 2, this->lose->getGlobalBounds().height / 2);
	this->lose->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	this->paused = false;
	this->enterKey = false;
	this->endGame = false;
	Effect = 1;
	LoadBrick("BrickLevel/level1.txt");
	for (int i = 1; i <= 6; i++)
	{
		Heart_BrickGame* newHeart; 
		newHeart = new Heart_BrickGame(); 
		newHeart->setPosition((float)(i-1) * 40, 80); 
		hearts.push_back(newHeart);
	}
	background.loadFromFile("Graphics/sprites/InGameBackground.png");
}
// cập nhật tất cả yếu tố liên quan trò chơi
void mainGame_Brick::CapNhat(RenderWindow* window)
{
	if (paused)
	{
		int choose = PauseGame(window);
	if (choose==2)
		{
			SaveGame("Save/1.txt");
			paused = false;
		}
		if (choose==3)
		{
			KhoiTao(window);
			LoadGame("Save/1.txt");
			paused = false;
		}
	}
	else if (ball->getLive() == 0) // hết mạng => thua, kết thúc game
	{
		endGame = true;
	}
	else if (brick.empty()) endGame = true;  // hết gạch=> thắng, kết thúc game
	else {
		// cập nhật các yếu tố liên quan bóng
		ball->CapNhat(window, point, player, hearts);
		// cập nhật các yếu tố liên quan thanh trượt
		player->CapNhat(window);
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
			prize[i]->CapNhat(player,point,ball); 
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
		if (Keyboard::isKeyPressed(Keyboard::Key::P) && !enterKey) 
			paused = true;
		enterKey = Keyboard::isKeyPressed(Keyboard::Key::P);
		// Nếu nhấn space thì reset vị trí bắt đầu game ( để dự phòng)
		if (Keyboard::isKeyPressed(Keyboard::Key::Space))
			ball->reset(window); 
	}
	this->enterKey = Keyboard::isKeyPressed(Keyboard::Key::P);
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

// Xuất ra màn hình 
void mainGame_Brick::Xuat(RenderWindow* window)
{
	//vẽ background
	Sprite sp(background);
	window->draw(sp);
	// vẽ tất cả các thành phần game
	window->draw(*ball); 
	window->draw(*player); 
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
			window->draw(*lose);
			if (Keyboard::isKeyPressed(Keyboard::Key::A)) // nhấn A => chơi lại
			{
				InputName(window);
				coreState.SetTrangThai(new mainGame_Brick());
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) //Nhân Escape => thoát ra menu
			{
				InputName(window);
				coreState.SetTrangThai(new Menu());
			}
		}
		else // trường hợp thắng
		{
			window->draw(*win);
			if (Keyboard::isKeyPressed(Keyboard::Key::A))
			{
				InputName(window);
				coreState.SetTrangThai(new mainGame_Brick());
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				InputName(window);
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
// Hàm nhập tên để lưu file khi đã kết thúc game
void mainGame_Brick::InputName(RenderWindow* window)
{
	string playerName=""; 
	string temp = "Enter Yourname: ";
	Text playerNameText("", *font, 30U);
	playerNameText.setString(temp);
	playerNameText.setCharacterSize(70);
	playerNameText.setPosition(0, 300);
	window->clear();
	window->draw(playerNameText);
	window->display();
	int kt = 0;
	while (kt==0)
	{
		Event event; 
		while (window->pollEvent(event))
		{
			if (event.type == Event::TextEntered)
			{
				if (event.key.code == 8&&playerName.size()!=0)
				{
					playerName.pop_back();
					playerNameText.setString(temp + playerName);
					playerNameText.setCharacterSize(100);
					playerNameText.setPosition(0, 300);
					window->clear();
					window->draw(playerNameText);
					window->display();
					std::cout << playerName << endl;
				}
				else if (event.key.code == 13)
				{
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
					fout << playerName << ":" << point->GetDiem() << endl;
					fout.close();
					window->clear();
					kt = 1;
					break;
				}
				else
				{
					playerName += event.key.code;
					playerNameText.setString(temp + playerName);
					playerNameText.setCharacterSize(100);
					playerNameText.setPosition(0, 300);
					window->clear();
					window->draw(playerNameText);
					window->display();
					std::cout << playerName << endl;
				}
			}
		}
		
	}
	
}
// Load gạch từ file
void mainGame_Brick::LoadBrick(string filename)
{
	fstream f;
	f.open(filename, ios::in);
	while (!f.eof())
	{
		Vector2f BrickPos;
		int Sheild;
		char Color;
		f >> BrickPos.x >> BrickPos.y >> Sheild >> Color;
		Vector2f brickSize;
		brickSize.x = 90;
		brickSize.y = 30;
		Brick_BrickGame* b = new Brick_BrickGame;
		if (Color == 'm')
		{
			b->setShieldNumber(4);
		}
		else
		{
			b->setShieldNumber(Sheild);
		}
		b->setPosition(BrickPos);
		b->setOrigin(brickSize / 2.f);
		b->setBrickColor(Color);
		b->TaoTexture();
		brick.push_back(b);
	}
	brick.pop_back();
}

//Hàm lưu game
void mainGame_Brick::SaveGame(string filename)
{
	fstream f;
	f.open(filename, ios::out);
	//Lưu gạch
	f << brick.size() <<endl;
	for (int i = 0; i < brick.size(); i++)
	{
		f << brick[i]->getPosition().x<<" "<<brick[i]->getPosition().y<<" "<<brick[i]->getShieldNumber()<<" "<<brick[i]->getBrickColor();
		f << endl;
	}
	//Lưu vật phẩm
	f << prize.size()<<endl;
	for (int i = 0; i < prize.size(); i++)
	{
		f << prize[i]->getPosition().x << " " << prize[i]->getPosition().y << " " << prize[i]->getType();
		f << endl;
	}
	//Lưu thanh trượt
	f << player->getPosition().x << " " << player->getPosition().y << " " << player->getScale().x << " " << player->getScale().y << endl;
	//Lưu bóng
	f << ball->getPosition().x << " " << ball->getPosition().y << endl;
	//Lưu điểm
	f << point->GetDiem() <<endl;
	//Lưu số mạng còn lại
	f << ball->getLive();
	f.close();
}

//Hàm load game
void mainGame_Brick::LoadGame(string filename)
{
	fstream f;
	f.open(filename, ios::in);
	int brickNumber;
	int prizeNumber;
	f >> brickNumber;
	vector<Brick_BrickGame*> newBrick;
	for (int i = 0; i < brickNumber; i++)
	{
		Vector2f BrickPos;
		int Sheild;
		char Color;
		f >> BrickPos.x >> BrickPos.y >> Sheild >> Color;
		Vector2f brickSize;
		brickSize.x = 90;
		brickSize.y = 30;
		Brick_BrickGame* b = new Brick_BrickGame;
		if (Color == 'm')
		{
			b->setShieldNumber(4);
		}
		else
		{
			b->setShieldNumber(Sheild);
		}
		b->setPosition(BrickPos);
		b->setOrigin(brickSize / 2.f);
		b->setBrickColor(Color);
		b->TaoTexture();
		newBrick.push_back(b);
	}
	brick = newBrick;
	f >> prizeNumber;
	vector<Brick_Prize*> newPrize;
	for (int i = 0; i < prizeNumber; i++)
	{
		Brick_Prize* p = new Brick_Prize;
		Vector2f prizePos;
		int kieu;
		f >> prizePos.x >> prizePos.y >> kieu;
		p->setPosition(prizePos);
		p->setType(kieu);
		p->TaoTexture();
		newPrize.push_back(p);
	}
	prize = newPrize;
	Vector2f playerPos;
	Vector2f playerScale;
	f >> playerPos.x >> playerPos.y >> playerScale.x >> playerScale.y;
	player->setPosition(playerPos);
	player->setScale(playerScale);
	Vector2f ballPos;
	f >> ballPos.x >> ballPos.y;
	ball->setPosition(ballPos);
	int diem;
	f >> diem;
	point->setDiem(diem);
	int heartNumber;
	f >> heartNumber;
	ball->setLive(heartNumber);
	vector<Heart_BrickGame*> newHearts;
	for (int i = 1; i <= heartNumber; i++)
	{
		Heart_BrickGame* newHeart;
		newHeart = new Heart_BrickGame();
		newHeart->setPosition((float)(i - 1) * 40, 100);
		newHearts.push_back(newHeart);
	}
	hearts = newHearts;
	f.close();
}

//Pause game
int mainGame_Brick::PauseGame(RenderWindow* window)
{
	mainGame_Brick newGame = *this;
	Texture tex;
	tex.loadFromFile("Graphics/sprites/MenuBack.png");
	Texture t[8];
	t[0].loadFromFile("Graphics/Button/Play1.png");
	t[1].loadFromFile("Graphics/Button/Play2.png");
	t[2].loadFromFile("Graphics/Button/MainMenu1.png");
	t[3].loadFromFile("Graphics/Button/MainMenu2.png");
	t[4].loadFromFile("Graphics/Button/Save1.png");
	t[5].loadFromFile("Graphics/Button/Save2.png");
	t[6].loadFromFile("Graphics/Button/Load1.png");
	t[7].loadFromFile("Graphics/Button/Load2.png");
	Sprite sprite[4];
	for (int i = 0; i < 4; i++)
	{
		sprite[i].setTexture(t[i * 2]);
	}
	sprite[0].setPosition(350, 450);
	sprite[1].setPosition(475, 450);
	sprite[2].setPosition(625, 450);
	sprite[3].setPosition(750, 450);
	sprite[0].setTexture(t[1]);
	int luachon = 0;
	while (true)
	{
		window->clear();
		newGame.Xuat(window);
		Sprite sp(tex);
		sp.setPosition(300, 250);
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
				{
					if (luachon == 0)
					{
						sprite[luachon].setTexture(t[luachon * 2]);
						luachon = 3;
						sprite[luachon].setTexture(t[luachon * 2 + 1]);
					}
					else
					{
						sprite[luachon].setTexture(t[luachon * 2]);
						luachon--;
						sprite[luachon].setTexture(t[luachon * 2 + 1]);
					}
					break;
				}
				case sf::Keyboard::Right:
				{
					if (luachon == 3)
					{
						sprite[luachon].setTexture(t[luachon * 2]);
						luachon = 0;
						sprite[luachon].setTexture(t[luachon * 2 + 1]);
					}
					else
					{
						sprite[luachon].setTexture(t[luachon * 2]);
						luachon++;
						sprite[luachon].setTexture(t[luachon * 2 + 1]);
					}
					break;
				}
				case sf::Keyboard::Enter:
				{
					paused = false;
					window->clear();
					return luachon;
				}
				}

				break;

				break;

			}
		}

		window->draw(sp);
		for (int i = 0; i < 4; i++)
		{
			window->draw(sprite[i]);
		}
		window->display();
	}
	
	
}
