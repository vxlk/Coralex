#include "playerSprite.h"
#include "gameData.h"
#include "collisionStrategy.h"
#include "smartSprite.h"

PlayerSprite::PlayerSprite( const std::string& name) :
  bulletName( Gamedata::getInstance().getXmlStr(name + "/bullet") ),
  bulletPool(bulletName),
  bullets(),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName + "/speedX") ),
  bulletInterval( Gamedata::getInstance().getXmlInt(bulletName + "/interval") ),
  timeSinceLastFrame(0),
  observers(),
  sprite(name),
  collision(false),
  initialVelocity(sprite.getVelocity()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

void PlayerSprite::stop() { 
  sprite.setVelocity( Vector2f(0, 0) );
}


void PlayerSprite::detach( SmartSprite* o ) {
  
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
  
}

bool PlayerSprite::shoot()
{
//std::cout << timeSinceLastFrame <<  " " << bulletInterval << "\n";
  if ( timeSinceLastFrame < bulletInterval ) return false;
  float deltaX = getScaledWidth();
  float deltaY = getScaledHeight()/2;
  // I need to add some minSpeed to velocity:
  Bullet bullet = bulletPool.getFromPool(); 
  bullet.setPosition( sprite.getPosition() +Vector2f(deltaX, deltaY) );
  bullet.setVelocity( sprite.getVelocity() + Vector2f(minSpeed, 0) );
  bullets.push_back( bullet );
  timeSinceLastFrame = 0;
  return true;
}

bool PlayerSprite::checkForBulletCollision(const Drawable& npc, CollisionStrategy* col)
{
  /*
  auto itBullet = bullets.begin();
  

  while (itBullet != bullets.end())
  {
    if ( col->executeBullet(*itBullet, npc) )

           return true;
  }

  return false;
*/
  for(unsigned long int i = 0; i < bullets.size(); ++i)
    if ( col->executeBullet(bullets[i], npc) )
    {
      bullets[i].collided();
      return true;
    }
  return false;
}

void PlayerSprite::right() { 
  if ( sprite.getX() < worldWidth-getScaledWidth()) {
    sprite.setVelocityX(initialVelocity[0]);
  }
} 
void PlayerSprite::left()  { 
  if ( sprite.getX() > 0) {
    sprite.setVelocityX(-initialVelocity[0]);
  }
} 
void PlayerSprite::up()    { 
  if ( sprite.getY() > 0) {
    sprite.setVelocityY( -initialVelocity[1] );
  }
} 
void PlayerSprite::down()  { 
  if ( sprite.getY() < worldHeight-getScaledHeight()) {
    sprite.setVelocityY( initialVelocity[1] );
  }
}

void PlayerSprite::update(Uint32 ticks) {
  timeSinceLastFrame++;
  sprite.update(ticks);
  stop();


  //bullet
  //for (Bullet& bullet : bullets)
  for (long unsigned int i = 0; i < bullets.size(); ++i)
  {
    bullets[i].update(ticks);
    if (bullets[i].goneTooFar() || bullets[i].hasCollision())
    {
      //if (bullets[i].hasCollision()) std::cout << "has collision\n";
      bullets[i].reset();
      bulletPool.addBack(bullets[i]);
      bullets.erase(bullets.begin() + i);
    }
  }
  //ai
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    int offset = rand()%5;
    offset = offset*(rand()%2?-1:1);
    const Vector2f off(offset, offset);
    (*ptr)->setPlayerPos( getPosition()+off );
    ++ptr;
  }
}

void PlayerSprite::rotateLeft()
{
    this->sprite.updateRotation(RotationDirections::LEFT);
}

void PlayerSprite::rotateRight()
{
    this->sprite.updateRotation(RotationDirections::RIGHT);
}
