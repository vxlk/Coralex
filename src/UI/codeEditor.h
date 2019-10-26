#pragma once
#include "component.h"
#include "customTexture.h"
#include <string>
#include <memory>

class RenderContext;

namespace ui {

class CodeEditor : Component
{
public:
	
	CodeEditor() noexcept;
	
	virtual ~CodeEditor() noexcept
	{
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

	std::unique_ptr<RenderContext> textEditorContext;

};

}//namespace ui