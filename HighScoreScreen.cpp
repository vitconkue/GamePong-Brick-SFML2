#include "HighScoreScreen.h"
#include "Menu.h"

void HighScoreScreen::KhoiTao(RenderWindow* window)
{
	// Load font
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font2.ttf");
	introduce = new Text("HIGHSCORES", *font, 90U); 
	introduce->setOrigin(introduce->getGlobalBounds().width / 2, introduce->getGlobalBounds().height / 2); 
	introduce->setPosition(window->getSize().x / 2, 20); 
	fstream fin; 
	fin.open("Highscores.txt", std::ios::in); 
	int num; 
	fin >> num; 
	fin.get(); 
	string nm; int d; 
	for(int i=0 ; i< num;i++)
	{
		getline(fin, nm, ':'); 
		fin >> d; 
		fin.get();
		Text* tmpName = new Text(nm, *font, 40U);
		names.push_back(tmpName); 
		DiemSo* tmpPoint = new DiemSo(*font, 40U); 
		tmpPoint->setDiem(d); 
		highscores.push_back(tmpPoint);
	}
	fin.close();
	Sort();
	int len = highscores.size(); 
	for (int i = 0; i < len && i < 5; i++)
	{
		names[i]->setOrigin(names[i]->getGlobalBounds().width / 2, names[i]->getGlobalBounds().height / 2); 
		names[i]->setPosition(window->getSize().x/3, (i + 1) * window->getSize().y / 6);
		highscores[i]->setOrigin(highscores[i]->getGlobalBounds().width / 2, highscores[i]->getGlobalBounds().height / 2);
		highscores[i]->setPosition(window->getSize().x *2/3, (i + 1) * window->getSize().y / 6);   
	}
}

void HighScoreScreen::CapNhat(RenderWindow* window)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		coreState.SetTrangThai(new Menu()); 
	}
	for (int i = 0; i < highscores.size() && i < 5;i++)
	{
		highscores[i]->CapNhat(); 
	}
}

void HighScoreScreen::Xuat(RenderWindow* window)
{
	window->draw(*introduce); 
	for (int i = 0; i < highscores.size() && i < 5; i++)
	{
		names[i]->setFillColor(Color::White);
		window->draw(*names[i]); 
		highscores[i]->setFillColor(Color::Green);
		window->draw(*highscores[i]); 
	}
}

void HighScoreScreen::Destroy(RenderWindow* window)
{
	delete introduce; 
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
				// swap diem
				DiemSo* tmp1 = highscores[i];
				highscores[i] = highscores[j];
				highscores[j] = tmp1; 
				// swap ten 
				Text* tmp2 = names[i];
				names[i] = names[j]; 
				names[j] = tmp2; 
			}
	    }
	}
}
