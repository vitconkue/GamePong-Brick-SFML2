#include "mainGame.h"
#include "Menu.h"
using namespace sf;
//Hàm khởi tạo cửa sổ game khi chơi
void mainGame::KhoiTao(RenderWindow* window)
{
	//điểm số
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");
	this->diem1 = new DiemSo(*font, 64U);
	this->diem2 = new DiemSo(*font, 64U);
	//Chữ khi tạm dừng
	this->pausedText = new Text("Tam dung. Nhan P de tiep tuc.\nNhan Esc de thoat.", *font, 64U);
	this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
	this->pausedText->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	//Chữ khi người 1 thắng
	this->win1 = new Text("Nguoi choi 1 thang!\nNhan Enter de choi lai!\nNhan Esc de thoat!", *font, 64U);
	this->win1->setOrigin(this->win1->getGlobalBounds().width / 2, this->win1->getGlobalBounds().height / 2);
	this->win1->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	//Chữ khi người 2 thắng
	this->win2 = new Text("Nguoi choi 2 thang!\nNhan Enter de choi lai!\nNhan Esc de thoat!", *font, 64U);
	this->win2->setOrigin(this->win2->getGlobalBounds().width / 2, this->win2->getGlobalBounds().height / 2);
	this->win2->setPosition(window->getSize().x / 2, window->getSize().y / 2);

	this->diem2->setPosition(800, 0);
	//Khởi tạo các biến 
	this->player1 = new ThanhNguoiChoi(0);
	this->player2 = new ThanhNguoiChoi(1);
	this->bong = new Bong(this->diem1, this->diem2, this->player1, this->player2);

	this->bong->Reset(window);

	this->paused = false;
	this->enterKey = false;
	this->endgame = false;
}
//Hàm cập nhật
void mainGame::CapNhat(RenderWindow* window)
{
	//Bấm P để dừng
	if (this->paused)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::P) && !this->enterKey)
		{
			this->paused = false;
		}
		//Bấm esc để trở lại menu
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			coreState.SetTrangThai(new Menu());
		}
	}
	//Xử lý nếu điểm ai tới 5 trước thì biến dừng sẽ trả về true
	else if (this->diem1->GetDiem() == 5 || this->diem2->GetDiem() == 5)
	{
		this->endgame = true;
	}
	else //liên tục cập nhật các yếu tố có trong trò chơi
	{
		this->bong->CapNhat(window);
		this->player1->CapNhat();
		this->player2->CapNhat();
		this->diem1->CapNhat();
		this->diem2->CapNhat();
		if (Keyboard::isKeyPressed(sf::Keyboard::Key::P) && !this->enterKey)
		{
			this->paused = true;
		}
	}

	this->enterKey = Keyboard::isKeyPressed(Keyboard::Key::P);
}
//Hàm Xuất ra cửa sổ game
void mainGame::Xuat(RenderWindow* window)
{
	//Vẽ các vật thể
	window->draw(*this->bong);
	window->draw(*this->player1);
	window->draw(*this->player2);
	window->draw(*this->diem1);
	window->draw(*this->diem2);
	//Vẽ đường ngăn cách 2 bên.
	sf::CircleShape diem(1);
	diem.setOrigin(0, 0);
	for (int i = 0; i < 600; i++)
	{
		diem.setPosition(501, i);
		window->draw(diem);
	}
	//Nếu game tạm dừng thì sẽ hiện câu lệnh pausedText
	if (this->paused)
	{
		window->draw(*this->pausedText);
	}
	//Nếu khi có người chơi chiến thắng sẽ in ra ai chiến thắng
	if (this->endgame)
	{
		//Người chơi 1 thắng
		if (this->diem1->GetDiem() == 5)
		{
			window->draw(*this->win1);
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
			{
				coreState.SetTrangThai(new mainGame());
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				coreState.SetTrangThai(new Menu());
			}
		}
		else //Người chơi 2 thắng
		{
			window->draw(*this->win2);
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
			{
				coreState.SetTrangThai(new mainGame());
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				coreState.SetTrangThai(new Menu());
			}
		}
	}
}
void mainGame::Destroy(sf::RenderWindow* window)
{
	delete this->player1;
	delete this->player2;
	delete this->bong;
	delete this->diem1;
	delete this->diem2;
	delete this->font;
}
