#include "twoWayMultiSprite.h"
#include "gameData.h"
#include "imageFactory.h"
#include <iostream>

Vector2f TwoWayMultiSprite::makeVelocity(int vx, int vy) {
  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();

  return Vector2f(newvx, newvy);
}

void TwoWayMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

TwoWayMultiSprite::TwoWayMultiSprite( const std::string& forward, const std::string& backward ) :
  Drawable(forward, 
           Vector2f(Gamedata::getInstance().getXmlInt(forward+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(forward+"/startLoc/y")), 
           Vector2f(makeVelocity(
                    Gamedata::getInstance().getXmlInt(forward+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(forward+"/speedY"))
                                ) 
           ),
  imagesForward( ImageFactory::getInstance().getImages(forward) ),
  imagesBackward( ImageFactory::getInstance().getImages(backward)),
  isForward(true),
  rotationAmount(0.0),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(forward+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(forward+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

void TwoWayMultiSprite::draw() const { 
  getImageVector()[currentFrame]->drawRotation(getX(), getY(), getScale(), rotationAmount );
}

void TwoWayMultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() + getScaledHeight() > worldHeight) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
    isForward = true;
  }
  if ( getX() + getScaledWidth() > worldWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
    isForward = false;
  }  

}
