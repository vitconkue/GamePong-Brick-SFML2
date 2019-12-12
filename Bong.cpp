#include "Bong.h"
//Hàm khởi tạo 
Bong::Bong(DiemSo* d1, DiemSo* d2, Thanh* p1, Thanh* p2)
{
	this->Load("ball.png");
	this->diem1 = d1;
	this->diem2 = d2;
	this->player1 = p1;
	this->player2 = p2;
	this->buffer = new SoundBuffer();
	this->buffer->loadFromFile("Sounds/bounce.wav");
	this->sound = new Sound(*this->buffer);
}
//Hàm cập nhật 
void Bong::CapNhat(RenderWindow* window)
{
	//Hàm kiểm tra va chạm bóng với thanh thứ nhất
	if (this->KiemTraVaCham(this->player1))
	{
		this->speed.x *= -1.1; //Vận tốc theo x sẽ tăng thêm 10%
		//Xử lý theo tính chất của va chạm vật lý 
		if (this->speed.y > 0)
		{
			if (this->player1->speed.y > 0)
			{
				this->speed.y = this->speed.y * 1.1; //Vận tốc theo y cũng sẽ tăng thêm 10%
			}
			else if (this->player1->speed.y < 0)
			{
				this->speed.y = this->speed.y * -1.1;
			}
		}
		else if (this->speed.y < 0)
		{
			if (this->player1->speed.y > 0)
			{
				this->speed.y = this->speed.y * -1.1;
			}
			else if (this->player1->speed.y < 0)
			{
				this->speed.y = this->speed.y * 1.1;
			}
		}
		this->sound->play();
	}
	//Hàm kiểm tra va chạm bóng với thanh thứ hai
	if (this->KiemTraVaCham(this->player2))
	{
		this->speed.x *= -1.1;//Vận tốc theo x sẽ tăng thêm 10%
		//Xử lý theo tính chất của va chạm vật lý 
		if (this->speed.y > 0)
		{
			if (this->player2->speed.y > 0)
			{
				this->speed.y = this->speed.y * 1.1;//Vận tốc theo y cũng sẽ tăng thêm 10%
			}
			else if (this->player2->speed.y < 0)
			{
				this->speed.y = this->speed.y * -1.1;
			}
		}
		else if (this->speed.y < 0)
		{
			if (this->player2->speed.y > 0)
			{
				this->speed.y = this->speed.y * -1.1;
			}
			else if (this->player2->speed.y < 0)
			{
				this->speed.y = this->speed.y * 1.1;
			}
		}
		this->sound->play();
	}
	//Xử lý va chạm của bóng với 2 bên thành cửa sổ game
	if (this->getPosition().y < 0 || this->getPosition().y + this->getGlobalBounds().height > window->getSize().y)
	{
		this->speed.y *= -1; //nó sẽ đập ngược lại theo tính chất vật lý
		this->sound->play();
	}
	//Xử lý nếu bóng vượt ngoài thanh thứ 1 khi tới thì sẽ tính điểm cho người thứ 2
	if (this->getPosition().x < this->player1->getGlobalBounds().width - 50)
	{
		this->diem2->TangDan();
		this->Reset(window);
	}
	//Ngược lại, Xử lý nếu bóng vượt ngoài thanh thứ 2 khi tới thì sẽ tính điểm cho người thứ 1
	if (this->getPosition().x + this->getGlobalBounds().width > window->getSize().x - this->player2->getGlobalBounds().width + 50)
	{
		this->diem1->TangDan();
		this->Reset(window);
	}
	VatThe::CapNhat();
}
//Hàm reset khi mỗi khi tăng điểm
void Bong::Reset(sf::RenderWindow* window)
{
	this->speed.x = ((rand() % 2) == 0) ? 1.2 : -1.2; //Random hướng của bóng theo x với vận tốc 1.2f
	this->speed.y = ((rand() % 2) == 0) ? 1.2 : -1.2; //Random hướng của bóng theo y với vận tốc 1.2f
	this->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	this->player1->setPosition(0, window->getSize().y / 2 - this->player1->getGlobalBounds().height / 2);
	this->player2->setPosition(window->getSize().x - this->player2->getGlobalBounds().width, window->getSize().y / 2 - this->player2->getGlobalBounds().height / 2);
}

Bong::~Bong()
{
	delete this->sound;
	delete this->buffer;
}