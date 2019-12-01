#define NOMINMAX
#include <Windows.h>
#include "TrangThaiGame.h"
#include "Menu.h"
#include <iostream>
using namespace std;
TrangThaiGame coreState;
bool quitGame = false;

int main()
{
	cout << "----------- PING PONG GAME --------------\n";
	cout << "-Huong dan cach choi:\n-Khi hien cua so game, dieu khien mui ten len xuong va bam Enter de chon!\n-2 nguoi choi se dieu khien thanh truot\nlen xuong bang cac phim W,S va mui ten len, xuong\nNguoi choi nao dat 5 diem truoc se chien thang!\n-Bam P de tam dung tro choi.\n";
	cout << "1. Bat dau choi - 0. Thoat\nNhap lua chon: ";
	int luachon;
	cin >> luachon;
	switch (luachon)
	{
	case 1:
	{
		RenderWindow window(VideoMode(1000, 600), "PingPong");
		coreState.SetWindow(&window);
		coreState.SetTrangThai(new Menu());
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

			window.clear(Color::Black);

			coreState.CapNhat();
			coreState.Xuat();

			window.display();

			if (quitGame)
			{
				window.close();
			}
			Sleep(5);
		}
	}
	case 0:
		break;
	}
	system("pause");
	return 0;
}
