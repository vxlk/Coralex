#pragma once

#include "SDL.h"
#include "component.h"
#include "customTexture.h"
#include <string>

class CodeEditor : Component
{
public:
	
	CodeEditor() noexcept {}
	CodeEditor(SDL_Renderer *renderer, SDL_Window *win) noexcept : gRenderer(renderer), gWindow(win) {}

	virtual ~CodeEditor() noexcept
	{
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
		gRenderer = NULL;

		SDL_Quit();
	}

	void eventHandler(const SDL_Event& event);

private:

	void render();

	bool hasChange = false;
	std::string contents;
	SDL_Event e;

	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 0xFF };

	LTexture gPromptTextTexture;
	LTexture gInputTextTexture;

	//The window we'll be rendering to
	SDL_Window *gWindow = nullptr;

	//The window renderer
	SDL_Renderer *gRenderer = nullptr;

	TTF_Font* gFont = nullptr;
};

