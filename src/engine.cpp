#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
//#include "multisprite.h"
#include "rotationSprite.h"
#include "twoWayMultiSprite.h"
#include "gameData.h"
#include "engine.h"
#include "frameGenerator.h"
#include "playerSprite.h"
#include <sstream>
#include "hud.h"
#include "collisionStrategy.h"


Engine::~Engine() { 
  for(unsigned long int i = 0; i < drawables.size(); ++i)
    delete drawables[i];
  drawables.clear();

  delete playerTank;
  delete playerSniper;

  for ( unsigned long int i = 0; i < strategies.size(); ++i )
    delete strategies[i];

  delete sounds;
  delete menuEngine;
  
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  menuEngine(new MenuEngine),
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc.getRenderer() ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  viewport( Viewport::getInstance() ),
  
  drawables ({ 
             }),
  playerTank(new PlayerSprite("TankPlayer")),
  playerSniper(new PlayerSprite("SniperPlayer")),
  sounds(new SDLSound),
  strategies(),
  currentSprite(0),
  makeVideo( false )
{
  //scale player
  playerTank->setScale(.75);
  playerSniper->setScale(.75);
  drawables.reserve(2);

  drawables.emplace_back( new SmartSprite("Tank", playerTank->getPosition(), 100, 100) );
  drawables.emplace_back( new SmartSprite("Sniper", playerSniper->getPosition(), 100, 100) );
  Viewport::getInstance().setObjectToTrack(drawables[0]);
  for(unsigned long int i = 0; i < drawables.size(); ++i)
  {
    //scale ai
    drawables[i]->setScale(.75);
    //attach ai
    playerTank->attach(drawables[i]);
    playerSniper->attach(drawables[i]);
  }

  strategies.push_back( new RectangularCollisionStrategy );


  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const { 
  world.draw();
  io.writeText("Press 'm' for menu", 30, 60);


  for(unsigned long int i = 0; i < drawables.size(); ++i)
  {
    drawables[i]->draw();
  }

  //render player
  playerTank->draw();
  playerSniper->draw();

  viewport.drawName();
  
  if ( drawables.size() == 0 ) {
    io.writeText("Press P to Restart the game", 250, 200);
    clock.pause();
  }
  if (hudIsShown)
    HUD::draw();
  HUD::drawPool(this->playerSniper->getBulletPool());
  SDL_RenderPresent(renderer);

  
}

void Engine::drawFPS(const int &x, const int &y, const SDL_Color& c) const
{
  std::stringstream ss;
  ss << this->clock.getFps();
  this->io.writeText(ss.str(), x, y, c);
}

void Engine::drawName(const int& x, const int& y, const SDL_Color& c) const
{
  this->io.writeText(this->name, x, y, c);
}

void Engine::drawHUD()
{
  std::cout << "in draw\n";
  
  SDL_Color c = 
  {
    (unsigned char)90,(unsigned char)160,(unsigned char)100,(unsigned char)255
  };
  this->io.writeText(this->name, 50, 50, c);
  std::stringstream ss;
  ss << this->clock.getFps();
  this->io.writeText(ss.str(), 50, 70, c);
}

void Engine::checkForCollisions() {
  /*
  auto it = drawables.begin();
  
    if ( strategies[0]->execute(*playerTank, **it) ||
         strategies[0]->execute(*playerSniper, **it)) {
      //SmartSprite* doa = *it;
    */
  
      //player->detach(doa);
      //delete doa;
      //it = drawables.erase(it);
    

  //check against both npcs
  for (unsigned long int i = 0; i < drawables.size(); ++i)
  {
    strategies[0]->execute(*playerTank, *drawables[i]);
    strategies[0]->execute(*playerSniper, *drawables[i]);
    if (playerSniper->checkForBulletCollision(*drawables[i], strategies[0]))
    {
      drawables[i]->setToExplode();
    }
    if (drawables[i]->spriteIsDead())
      drawables.erase(drawables.begin() + i);
  }

/*
  if (playerSniper->checkForBulletCollision(**it, strategies[0])) 
    (**it).setToExplode(); //explode
  ++it;
  if (playerSniper->checkForBulletCollision(**it, strategies[0])) 
    (**it).setToExplode(); //explode
*/
}

void Engine::update(Uint32 ticks) {
  //star->update(ticks);
  //spinningStar->update(ticks);
  this->checkForCollisions();
  for(unsigned long int i = 0; i < drawables.size(); ++i)
    drawables[i]->update(ticks);

  playerTank->update(ticks);
  playerSniper->update(ticks);

  world.update();
  viewport.update(); // always update viewport last

  Gamedata cache; //should read new file
  if (cache == Gamedata::getInstance())
	  std::cout << "match\n";
  else std::cout << "mismatch";
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % 2;
  /*
  if ( currentSprite ) {
    Viewport::getInstance().setObjectToTrack(spinningStar);
  }
  else {
    Viewport::getInstance().setObjectToTrack(star);
  }
  */
  //Viewport::getInstance().setObjectToTrack(drawables[0]);
}

bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate = SDL_GetKeyboardState(NULL);
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        
        //menu
        if (keystate[SDL_SCANCODE_F1])
        {
          hudIsShown = !hudIsShown;
        }

        //non-player codes
        if (keystate[SDL_SCANCODE_ESCAPE]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
           clock.unpause();
          return true;
        }
         if ( keystate[SDL_SCANCODE_M] ) {
           clock.pause();
           menuEngine->play();
           clock.unpause();
         }
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      //player codes tank
        if (keystate[SDL_SCANCODE_D]) {
          playerTank->left();
        }
        if (keystate[SDL_SCANCODE_A]) {
          playerTank->right();
        }
        if (keystate[SDL_SCANCODE_S]) {
          playerTank->up();
        }
        if (keystate[SDL_SCANCODE_W]) {
          playerTank->down();
        }
        if (keystate[SDL_SCANCODE_E]) {
          playerTank->rotateLeft();
        }
        if (keystate[SDL_SCANCODE_Q]) {
          playerTank->rotateRight();
        }

        //player codes sniper
        if (keystate[SDL_SCANCODE_F]) {
          playerSniper->left();
        }
        if (keystate[SDL_SCANCODE_H]) {
          playerSniper->right();
        }
        if (keystate[SDL_SCANCODE_T]) {
          playerSniper->up();
        }
        if (keystate[SDL_SCANCODE_G]) {
          playerSniper->down();
        }
        if (keystate[SDL_SCANCODE_Y]) {
          playerSniper->rotateLeft();
        }
        if (keystate[SDL_SCANCODE_R]) {
          playerSniper->rotateRight();
        }
        //shoot
        if (keystate[SDL_SCANCODE_X]) {
	        if (playerSniper->shoot())
            (*sounds)[static_cast<int>(Sounds::EXPLOSION)];
        }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
  return false;
}
