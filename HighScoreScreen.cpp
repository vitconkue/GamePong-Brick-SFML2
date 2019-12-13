#include "HighScoreScreen.h"
#include "Menu.h"

void HighScoreScreen::KhoiTao(RenderWindow* window)
{
	// Load font
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font2.ttf");
	title = new Text("HIGHSCORES", *font, 90U); 
	title->setOrigin(title->getGlobalBounds().width / 2, title->getGlobalBounds().height / 2); 
	title->setPosition(window->getSize().x / 2, 20); 
	fstream fin; 
	fin.open("Highscores.txt", std::ios::in);  // mở file để đọc
	int num; // số người chơi mà chương trình đã lưu
	fin >> num; 
	fin.get(); 
	string nm; // tên
	int d; // điểm
	// đọc toàn bộ người chơi và điểm của họ
	for(int i=0 ; i< num;i++) 
	{
		getline(fin, nm, ':'); 
		fin >> d; 
		fin.get();
		Text* tmpName = new Text(nm, *font, 50U);
		names.push_back(tmpName); 
		DiemSo* tmpPoint = new DiemSo(*font, 50U); 
		tmpPoint->setDiem(d); 
		highscores.push_back(tmpPoint);
	}
	fin.close();
	//sắp xếp lại hai vecto người chơi và điểm theo thứ tự tăng dần
	Sort(); 
	int len = highscores.size(); 
	// chỉ hiện tối đa 5 người chơi điểm cao nhất lên màn hình
	for (int i = 0; i < len && i < 5; i++)
	{
		// đặt vị trí in ra màn hình
		names[i]->setOrigin(names[i]->getGlobalBounds().width / 2, names[i]->getGlobalBounds().height / 2); 
		names[i]->setPosition(window->getSize().x/3, (i + 1) * window->getSize().y / 6);
		highscores[i]->setOrigin(highscores[i]->getGlobalBounds().width / 2, highscores[i]->getGlobalBounds().height / 2);
		highscores[i]->setPosition(window->getSize().x *2/3, (i + 1) * window->getSize().y / 6);   
	}
	background.loadFromFile("Graphics/sprites/backgroundHighscore.png");
}

void HighScoreScreen::CapNhat(RenderWindow* window)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape)) // nếu bấm Escape thì thoát ra menu 
	{
		coreState.SetTrangThai(new Menu()); 
	}
	for (int i = 0; i < highscores.size() && i < 5;i++)
	{
		highscores[i]->CapNhat(); 
	}
}
//xuất ra màn hình
void HighScoreScreen::Xuat(RenderWindow* window)
{
	Sprite sp(background); 
	window->draw(sp); 
	title->setFillColor(Color::Black); 
	window->draw(*title); 
	for (int i = 0; i < highscores.size() && i < 5; i++)
	{
		names[i]->setFillColor(Color::Red);
		window->draw(*names[i]); 
		highscores[i]->setFillColor(Color::Blue);
		window->draw(*highscores[i]); 
	}
}
// hàm huỷ
void HighScoreScreen::Destroy(RenderWindow* window)
{
	delete title; 
}

void HighScoreScreen::Sort()
{
	// interchange sort
	int len = highscores.size(); 
	for (int i = 0; i < len-1; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (highscores[i]->GetDiem() < highscores[j]->GetDiem())
			{
				// swap điểm
				DiemSo* tmp1 = highscores[i];
				highscores[i] = highscores[j];
				highscores[j] = tmp1; 
				// swap tên 
				Text* tmp2 = names[i];
				names[i] = names[j]; 
				names[j] = tmp2; 
			}
	    }
	}
}
