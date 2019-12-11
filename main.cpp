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
	RenderWindow window(VideoMode(1200, 900), "PingPong");
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
			//Sleep(5);
	}
	system("pause");
	return 0;
}
