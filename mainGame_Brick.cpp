#include "mainGame_Brick.h"
#include "Menu.h"
// Khởi tạo ban đầu
void mainGame_Brick::KhoiTao(RenderWindow* window)
{
	window->setFramerateLimit(120);
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font2.ttf");
	player = new ThanhNguoiChoi_Brick;
	player->setPosition(window->getSize().x / 2, window->getSize().y - 20);
	player->setScale(1.0, 1.0);
	point = new DiemSo(*font, 64U);
	ball = new Ball_BrickGame(point); 
	ball->reset(window, player); 
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
	//Load âm thanh
	moveBuffer = new SoundBuffer();
	selectBuffer = new SoundBuffer();
	gameBuffer = new SoundBuffer();
	gameSound = new Sound();
	mainsound = new Sound();
	moveBuffer->loadFromFile("Sounds/Move.wav");
	selectBuffer->loadFromFile("Sounds/Select.wav");
	gameBuffer->loadFromFile("Sounds/Ingame.ogg");
	//Chon level khi khoi tao
	string level = Level(window);
	string filename = "BrickLevel/level";
	filename += level;
	filename += ".txt";
	LoadBrick(filename);
	for (int i = 1; i <= 6; i++)
	{
		Heart_BrickGame* newHeart; 
		newHeart = new Heart_BrickGame(); 
		newHeart->setPosition((float)(i-1) * 40, 80); 
		hearts.push_back(newHeart);
	}
	background.loadFromFile("Graphics/sprites/InGameBackground.png");
	//Nhạc nền
	gameSound->setBuffer(*gameBuffer);
	gameSound->play();
}
// cập nhật tất cả yếu tố liên quan trò chơi
void mainGame_Brick::CapNhat(RenderWindow* window)
{
	if (paused)
	{
		gameSound->pause();
		int choose = PauseGame(window);
		if (choose == 1)
		{
			gameSound->stop();
			coreState.SetTrangThai(new Menu());
			return;
		}
		if (choose==2)
		{
			gameSound->play();
			SaveGame("Save/1.txt");
			paused = false;
		}
		if (choose==3)
		{
			gameSound->play();
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
			int choose = EndGame(window);
			if(choose == 0)
			{
				InputName(window);
				gameSound->stop();
				coreState.SetTrangThai(new mainGame_Brick());
			}
			else if (choose == 1)
			{
				InputName(window);
				gameSound->stop();
				coreState.SetTrangThai(new Menu());
			}
		}
		else // trường hợp thắng
		{
			int choose = EndGame(window);
			if (choose == 0)
			{
				InputName(window);
				gameSound->stop();
				mainGame_Brick* maingame = new mainGame_Brick();
				coreState.SetTrangThai(maingame);
			}
			else if (choose == 1)
			{
				InputName(window);
				gameSound->stop();
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
	delete moveBuffer;
	delete selectBuffer;
	delete gameBuffer;
	delete gameSound;
	delete mainsound;
}
// Hàm nhập tên để lưu file khi đã kết thúc game
void mainGame_Brick::InputName(RenderWindow* window)
{
	Texture tex;
	tex.loadFromFile("Graphics/sprites/EnterName.png");
	Sprite background(tex);
	string playerName=""; 
	Text playerNameText("", *font, 30U);
	playerNameText.setFillColor(Color::Black);
	playerNameText.setCharacterSize(50);
	playerNameText.setPosition(350, 385);
	window->clear();
	window->draw(background);
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
					playerNameText.setString(playerName);
					window->clear();
					window->draw(background);
					window->draw(playerNameText);
					window->display();
					std::cout << playerName << endl;
					mainsound->setBuffer(*moveBuffer);
					mainsound->play();
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
					mainsound->setBuffer(*selectBuffer);
					mainsound->play();
					break;
				}
				else
				{
					playerName += event.key.code;
					playerNameText.setString(playerName);
					window->clear();
					window->draw(background);
					window->draw(playerNameText);
					window->display();
					std::cout << playerName << endl;
					mainsound->setBuffer(*moveBuffer);
					mainsound->play();
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
	Text tiltle;
	tiltle.setString("PAUSE");
	Font f;
	f.loadFromFile("Graphics/font2.ttf");
	tiltle.setFont(f);
	tiltle.setFillColor(Color::Yellow);
	tiltle.setOutlineThickness(5);
	tiltle.setOutlineColor(Color::Black);
	tiltle.setPosition(475, 300);
	tiltle.setCharacterSize(100);
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
					mainsound->setBuffer(*moveBuffer);
					mainsound->play();
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
					mainsound->setBuffer(*moveBuffer);
					mainsound->play();
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
					mainsound->setBuffer(*selectBuffer);
					mainsound->play();
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
		window->draw(tiltle);
		for (int i = 0; i < 4; i++)
		{
			window->draw(sprite[i]);
		}
		window->display();
	}
	
	
}

//Menu endgame
int mainGame_Brick::EndGame(RenderWindow* window)
{
	endGame = false;
	Text tiltle;
	tiltle.setString("ENDGAME");
	Font f;
	f.loadFromFile("Graphics/font2.ttf");
	tiltle.setFont(f);
	tiltle.setFillColor(Color::Yellow);
	tiltle.setOutlineThickness(5);
	tiltle.setOutlineColor(Color::Black);
	tiltle.setPosition(425, 300);
	tiltle.setCharacterSize(100);
	mainGame_Brick newGame = *this;
	Texture tex;
	tex.loadFromFile("Graphics/sprites/MenuBack.png");
	Texture t[4];
	t[0].loadFromFile("Graphics/Button/Replay1.png");
	t[1].loadFromFile("Graphics/Button/Replay2.png");
	t[2].loadFromFile("Graphics/Button/MainMenu1.png");
	t[3].loadFromFile("Graphics/Button/MainMenu2.png");
	Sprite sprite[2];
	for (int i = 0; i < 2; i++)
	{
		sprite[i].setTexture(t[i * 2]);
	}
	sprite[0].setPosition(450, 450);
	sprite[1].setPosition(650, 450);
	sprite[0].setTexture(t[1]);
	int luachon = 0;
	while (true)
	{
		window->clear();
		endGame = false;
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
					mainsound->setBuffer(*moveBuffer);
					mainsound->play();
					if (luachon == 0)
					{
						sprite[luachon].setTexture(t[luachon * 2]);
						luachon = 1;
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
					mainsound->setBuffer(*moveBuffer);
					mainsound->play();
					if (luachon == 1)
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
					mainsound->setBuffer(*selectBuffer);
					mainsound->play();
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
		window->draw(tiltle);
		for (int i = 0; i < 2; i++)
		{
			window->draw(sprite[i]);
		}
		window->display();
	}

}

string mainGame_Brick::Level(RenderWindow* window)
{
	Text tiltle;
	tiltle.setString("CHOOSE LEVEL");
	Font f;
	f.loadFromFile("Graphics/font2.ttf");
	tiltle.setFont(f);
	tiltle.setFillColor(Color::Yellow);
	tiltle.setOutlineThickness(5);
	tiltle.setOutlineColor(Color::Blue);
	tiltle.setPosition(325, 300);
	tiltle.setCharacterSize(100);
	//Doi tuong so
	Text level;
	level.setFont(f);
	level.setFillColor(Color::Yellow);
	level.setOutlineThickness(5);
	level.setOutlineColor(Color::Blue);
	level.setPosition(570, 435);
	level.setCharacterSize(100);
	mainGame_Brick newGame = *this;
	Texture tex;
	tex.loadFromFile("Graphics/sprites/MainMenuBackground.png");
	Texture t[4];
	t[0].loadFromFile("Graphics/Button/Down1.png");
	t[1].loadFromFile("Graphics/Button/Down2.png");
	t[2].loadFromFile("Graphics/Button/Up1.png");
	t[3].loadFromFile("Graphics/Button/Up2.png");
	Sprite sprite[2];
	for (int i = 0; i < 2; i++)
	{
		sprite[i].setTexture(t[i * 2]);
	}
	sprite[0].setPosition(400, 450);
	sprite[1].setPosition(700, 450);
	int kt = 0;
	int luachon = 1;
	while (true)
	{
		kt = 0;
		window->clear();
		for (int i = 0; i < 2; i++)
		{
			sprite[i].setTexture(t[i * 2]);
		}
		Sprite sp(tex);
		sf::Event event;
		while (window->pollEvent(event))
		{
			kt = 0;
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
				{
					if (luachon > 1)
					{
						sprite[0].setTexture(t[1]);
						luachon--;
						kt = 1;
					}
					mainsound->setBuffer(*moveBuffer);
					mainsound->play();
					break;
				}
				case sf::Keyboard::Right:
				{
					if (luachon < 6)
					{
						sprite[1].setTexture(t[3]);
						luachon++;
						kt = 1;
					}
					mainsound->setBuffer(*moveBuffer);
					mainsound->play();
					break;
				}
				case sf::Keyboard::Space:
				{
					mainsound->setBuffer(*selectBuffer);
					mainsound->play();
					window->clear();
					return toString(luachon);
				}
				}

				break;

				break;

			}
		}
		if (luachon == 6)
		{
			level.setString("C");
		}
		else
		{
			level.setString(toString(luachon));
		}
		window->draw(sp);
		window->draw(tiltle);
		window->draw(level);
		for (int i = 0; i < 2; i++)
		{
			window->draw(sprite[i]);
		}
		window->display();
		if (kt == 1)
		{
			Sleep(100);
		}
	}
}

bool mainGame_Brick::checkCleanAllBrick()
{
	int len = brick.size(); 
	for (int i = 0; i < len; i++)
	{
		if (brick[i]->getShieldNumber() != 4) return false; 
	}
	return true; 
}

//Chuyen so tu int sang string
string mainGame_Brick::toString(int a)
{
	// chuyển đổi số thành chuỗi để in ra màn hình
	string str = "";
	if (a == 0)
	{
		str = "0";
	}
	while (a != 0)
	{
		str += char(a % 10 + 48);
		a /= 10;
	}
	for (int i = 0; i < str.length() / 2; i++)
	{
		swap(str[i], str[str.length() - i - 1]);
	}
	return str;
}