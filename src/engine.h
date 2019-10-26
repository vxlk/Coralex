#include <vector>
#include "../include/SDL/SDL.h"
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "smartSprite.h"
#include "sound.h"
#include "menuEngine.h"
#include "UI/codeEditor.h"

class PlayerSprite; //forward declare
class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  bool play();
  void switchSprite();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

private:

	MenuEngine* menuEngine;
	const RenderContext& rc; //* if its a singleton why the fuck does engine have one lmao
	const IoMod& io;
	Clock& clock;
  
	SDL_Renderer * const renderer; //this is def not needed
	World world;
	Viewport& viewport;

	std::vector<SmartSprite*> drawables;

	PlayerSprite* playerTank;
	PlayerSprite* playerSniper;
  
	SDLSound* sounds;
	std::vector<CollisionStrategy*> strategies;
  
	std::unique_ptr<ui::CodeEditor> editor;

	int currentSprite;

	bool makeVideo;

	void draw() const;
	void update(Uint32);

	bool hudIsShown = false;

	void drawFPS(const int &x, const int &y, const SDL_Color& c) const;
	void drawName(const int& x, const int& y, const SDL_Color& c) const;
	void drawHUD();

	void printScales() const;
	void checkForCollisions();

	const std::string name = "Tyler Small";
};
