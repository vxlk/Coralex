#include "rotationSprite.h"
#include "gameData.h"
#include "imageFactory.h"
#include <iostream>

Vector2f makeVelocity(int vx, int vy) {
  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();

  return Vector2f(newvx, newvy);
}

void RotationSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

RotationSprite::RotationSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(makeVelocity(
                    Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
                                ) 
           ),
  images( ImageFactory::getInstance().getImages(name) ),
  rotationAmount(0.0),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

void RotationSprite::draw() const { 
  images[currentFrame]->drawRotation(getX(), getY(), getScale(), rotationAmount );
}

void RotationSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
  
  //updateRotation(RotationDirections::RIGHT);

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
  }
  if ( getX() + getScaledWidth() > worldWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
  //  advanceFrame(ticks);
  }  

}

void RotationSprite::updateNoMove(Uint32 ticks) { 
  advanceFrame(ticks);
  
  setPosition(getPosition());

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() + getScaledHeight() > worldHeight) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() + getScaledWidth() > worldWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
  //  advanceFrame(ticks);
  }  

}
