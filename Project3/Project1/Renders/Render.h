#pragma once

class Screen
{
public:
	Screen(int size) : size(size), screen1(new char[size + 1]), screen2(new char[size + 1])
	{

	}
	~Screen()
	{
		delete[] screen1;
		delete[] screen2;
	}

	void Draw1(int pos, const char * face)
	{
		if (pos < 0 || pos >= size) return;
		strncpy(&screen1[pos], face, strlen(face));
	}
	void Draw2(int pos, const char * face)
	{
		if (pos < 0 || pos >= size) return;
		strncpy(&screen2[pos], face, strlen(face));
	}

	void Render()
	{
		printf("%s\n", screen1);
		printf("%s\n", screen2);
	}
	void Clear()
	{
		memset(screen1, ' ', size);
		screen1[size] = '\0';

		memset(screen2, ' ', size);
		screen2[size] = '\0';

		system("cls");
	}

	int ScreenSize() { return size; }
private:
	int size;
	char * screen1;
	char * screen2;
};