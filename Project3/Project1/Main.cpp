#include "stdafx.h"
#include "Scenes/Scene.h"

int main()
{
	const int screen_size = 80;

	Time::Create();

	Screen * screen = new Screen(screen_size);
	Scene * scene = new Scene(screen);
	scene->Initialize();
	
	while (true)
	{
		int c = -1;
		//	_getche : echo
		if (_kbhit())
		{
			c = _getch();	//	blocking ÇÔ¼ö
		}

		//	Update
		{
			Time::Get()->Update();
			scene->Update(c);
		}

		//	Clear
		screen->Clear();
		//	Render
		{
			scene->Render();
		}
		screen->Render();

		Sleep(66);
	}

	delete screen;
	delete scene;
	Time::Delete();

	return 0;
}