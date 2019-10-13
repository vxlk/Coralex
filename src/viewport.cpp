#include <sstream>
#include "viewport.h"
#include "ioMod.h"
#include "clock.h"
#include "renderContext.h"

Viewport& Viewport::getInstance() {
  static Viewport viewport;
  return viewport;
}

Viewport::Viewport() : 
  gdata(Gamedata::getInstance()),
  viewPos(0, 0),
  msgPos(
    Vector2f( gdata.getXmlInt("view/loc/x"), gdata.getXmlInt("view/loc/y") )
  ),
  worldWidth(gdata.getXmlInt("world/width")),
  worldHeight(gdata.getXmlInt("world/height")),
  viewWidth(gdata.getXmlInt("view/width")), 
  viewHeight(gdata.getXmlInt("view/height")),
  objWidth(0), objHeight(0),
  objectToTrack(NULL)
{}

void Viewport::setObjectToTrack(const Drawable *obj) { 
  objectToTrack = obj; 
  objWidth = objectToTrack->getScaledWidth();
  objHeight = objectToTrack->getScaledHeight();
}

void Viewport::draw() const {
 // IoMod::getInstance().
   // writeText("Tracking: "+objectToTrack->getName(), msgPos[0], msgPos[1]);
  SDL_Rect back;
  back.x = 50;
  back.y = 50;
  back.h = 500;
  back.w = 250;

  SDL_SetRenderDrawColor(IoMod::getInstance().getRenderer(), 255, 255, 255, 255);
  SDL_RenderFillRect(IoMod::getInstance().getRenderer(), &back);

  SDL_Color c = 
  {
    (unsigned char)gdata.getXmlInt("ui/red"),
    (unsigned char)gdata.getXmlInt("ui/green"),
    (unsigned char)gdata.getXmlInt("ui/blue"),
    (unsigned char)gdata.getXmlInt("ui/alpha")
  };

  IoMod::getInstance().writeText("Game Title", 50, 50, c);
  std::stringstream ss;
  ss << Clock::getInstance().getFps();
  IoMod::getInstance().writeText("FPS: " + ss.str(), 50, 80, c);
  /*
  IoMod::getInstance().writeText("W to move tank up", 50, 110, c);
  IoMod::getInstance().writeText("S to move tank back", 50, 140, c);
  IoMod::getInstance().writeText("A to move tank left", 50, 170, c);
  IoMod::getInstance().writeText("D to move tank right", 50, 200, c);
  IoMod::getInstance().writeText("T to move sniper up", 50, 230, c);
  IoMod::getInstance().writeText("G to move sniper down", 50, 260, c);
  IoMod::getInstance().writeText("F to move sniper left", 50, 290, c);
  IoMod::getInstance().writeText("H to move sniper left", 50, 320, c);
  IoMod::getInstance().writeText("Q to rotate tank left", 50, 350, c);
  IoMod::getInstance().writeText("E to rotate tank right", 50, 380, c);
  IoMod::getInstance().writeText("R to rotate sniper right", 50, 410, c);
  IoMod::getInstance().writeText("Y to rotate sniper left", 50, 440, c);
  */

  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/w"), 50, 110, c);
  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/s"), 50, 140, c);
  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/a"), 50, 170, c);
  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/d"), 50, 200, c);
  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/t"), 50, 230, c);
  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/g"), 50, 260, c);
  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/f"), 50, 290, c);
  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/h"), 50, 320, c);
  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/q"), 50, 350, c);
  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/e"), 50, 380, c);
  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/r"), 50, 410, c);
  IoMod::getInstance().writeText(gdata.getXmlStr("HUD/y"), 50, 440, c);
  IoMod::getInstance().writeText("Press X to shoot", 50, 470, c);
  IoMod::getInstance().writeText("Kill enemies", 50, 500, c);


  
}

void Viewport::drawPool(int index, int size) const
{
    SDL_Color c = 
    {
      (unsigned char)gdata.getXmlInt("ui/red"),
      (unsigned char)gdata.getXmlInt("ui/green"),
      (unsigned char)gdata.getXmlInt("ui/blue"),
      (unsigned char)gdata.getXmlInt("ui/alpha")
    };
    
    IoMod::getInstance().writeText("Objects In Pool" + std::to_string(index), 400, 400, c);
    IoMod::getInstance().writeText("Pool Size" + std::to_string(size), 425, 425, c);
}

void Viewport::drawName() const
{
  SDL_Color c = 
  {
    (unsigned char)gdata.getXmlInt("ui/red"),
    (unsigned char)gdata.getXmlInt("ui/green"),
    (unsigned char)gdata.getXmlInt("ui/blue"),
    (unsigned char)gdata.getXmlInt("ui/alpha")
  };
  IoMod::getInstance().writeText(gdata.getXmlStr("ui/name"), 50, 850, c);
}

void Viewport::update() {
  const float x = objectToTrack->getX();
  const float y = objectToTrack->getY();

  viewPos[0] = (x + objWidth/2) - viewWidth/2;
  viewPos[1] = (y + objHeight/2) - viewHeight/2;
  if (viewPos[0] < 0) viewPos[0] = 0;
  if (viewPos[1] < 0) viewPos[1] = 0;
  if (viewPos[0] > (worldWidth - viewWidth)) {
    viewPos[0] = worldWidth-viewWidth;
  }
  if (viewPos[1] > (worldHeight - viewHeight)) {
    viewPos[1] = worldHeight-viewHeight;
  }
}
