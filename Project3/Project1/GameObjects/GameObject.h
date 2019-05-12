#pragma once
class GameObject
{
public:
	GameObject(int pos, const char * face, Screen* screen);
	~GameObject();

	virtual void Draw();

protected:
	Screen * GetScreen() { return screen; }

public:
	int GetPosition() { return pos; }
	void SetPosition(int pos) { this->pos = pos; }

	int GetScreenSize() { return screen->ScreenSize(); }

	int GetFaceSize() { return (int)strlen(face); }
	const char * GetFace() { return face; }
	void SetFace(const char * face) { this->face = face; }

	void SetActive(bool val) { isActive = val; }
	bool GetActive() { return isActive; }

private:
	int pos;
	const char * face;

	Screen* screen;

	bool isActive;

protected:
	char faceL[20];
	char faceR[20];
	char life[20];
};

