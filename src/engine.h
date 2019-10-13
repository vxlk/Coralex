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
  const RenderContext& rc; //*
  const IoMod& io;
  Clock& clock;
  
  SDL_Renderer * const renderer;
  World world;
  Viewport& viewport;

  std::vector<SmartSprite*> drawables;

  PlayerSprite* playerTank;
  PlayerSprite* playerSniper;
  
  SDLSound* sounds;
  std::vector<CollisionStrategy*> strategies;
  
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
