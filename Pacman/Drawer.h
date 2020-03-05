#ifndef DRAWER_H
#define DRAWER_H

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
class Vector2f;

class Drawer
{
private:
	int pixelPerUnitX = 1;
	int pixelPerUnitY = 1;

public:
	static Drawer* Create(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	~Drawer(void);

	void SetPixelPerUnit(const int ppuX, const int ppuY);
	void Draw(const char* anImage, const Vector2f& pos, bool flipX = false, bool flipY = false, float angle = 0.f);
	void DrawText(const char* aText, const char* aFontFile, int aX, int aY);

private:
	Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	bool Init();
	
	SDL_Window* myWindow;
	SDL_Renderer* myRenderer;
	SDL_Surface* world;
};

#endif // DRAWER_H