#include "codeEditor.h"
#include "../gameData.h"

CodeEditor::CodeEditor() {
	gInputTextTexture.loadFromRenderedText(contents.c_str(), textColor);
	//Enable text input
	SDL_StartTextInput();

	gFont = TTF_OpenFont("..//Coralex/src/fonts/arial.tff", 28);
}

void CodeEditor::eventHandler(const SDL_Event& e)
{
		
	//Special key input
	if (e.type == SDL_KEYDOWN)
	{
		//Handle backspace
		if (e.key.keysym.sym == SDLK_BACKSPACE && contents.length() > 0)
		{
			//lop off character
			contents.pop_back();
			hasChange = true;
		}
		//Handle copy
		else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
		{
			SDL_SetClipboardText(contents.c_str());
		}
		//Handle paste
		else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
		{
			contents = SDL_GetClipboardText();
			hasChange = true;
		}
	}

	//Special text input event
	else if (e.type == SDL_TEXTINPUT)
	{
		//Not copy or pasting
		if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
		{
			//Append character
			contents += e.text.text;
			hasChange = true;
		}
	}

	if (this->hasChange)
		render();
}

void CodeEditor::render()
{
	//Text is not empty
	if (contents != "")
	{
		//Render new text
		gInputTextTexture.loadFromRenderedText(contents.c_str(), textColor);
	}
	//Text is empty
	else
	{
		//Render space texture
		gInputTextTexture.loadFromRenderedText(" ", textColor);
	}

	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	//Render text textures
	gPromptTextTexture.render((Gamedata::getInstance().getXmlInt("width") - gPromptTextTexture.getWidth()) / 2, 0);
	gInputTextTexture.render((Gamedata::getInstance().getXmlInt("width") - gInputTextTexture.getWidth()) / 2, gPromptTextTexture.getHeight());

	//Update screen
	SDL_RenderPresent(gRenderer);

	//Disable text input
	SDL_StopTextInput();
	SDL_StopTextInput();
}