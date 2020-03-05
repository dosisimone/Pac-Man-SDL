#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "assert.h"
#include "pacman.h"
#include "drawer.h"
#include <iostream>
#include "dousi96/GameController.h"

int main(int argc, char **argv)
{
	/* initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		assert(0 && "Failed to initialize video!");
		exit(-1);
	}
	
	//create the window
	SDL_Window* window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//check if the window is created
	if(window == nullptr)
	{
		assert(0 && "Failed to create window!");
		exit(-1);
	}

	// imports the dll to support JPG and PNG import
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 3) 
	{
		assert(0 && "Failed to import the dlls to support JPG and PNG import!");
		exit(-1);
	}

	// initialized the TTF engine
	if (TTF_Init() == -1)
	{
		assert(0 && "Failed to create ttf!");
		exit(-1);
	}

	//create drawer
	Drawer* drawer = Drawer::Create(window, renderer);
	drawer->SetPixelPerUnit(44, 44);
	//create game controller
	GameController* controller = new GameController(drawer);
	//create pacman
	//Pacman* pacman = Pacman::Create(drawer);
	controller->Start();
	// events polling
	SDL_Event event;
	float lastFrameTime = (float)SDL_GetTicks() * 0.001f;
	while (SDL_PollEvent(&event) >= 0)
	{
		float currentFrameTime = (float)SDL_GetTicks() * 0.001f;
		float deltaTime = currentFrameTime - lastFrameTime;		

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		if (!controller->Update(deltaTime))
		{
			break;
		}

		controller->Draw();

		lastFrameTime = currentFrameTime;

		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}

	delete controller;
	delete drawer;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit( );

	return 0;
}

