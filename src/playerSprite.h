#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H
//#include "rotationSprite.h"
#include <list>
#include "smartSprite.h"
#include "bullet.h"
#include "pool.h"

class SmartSprite;
class CollisionStrategy;

//composition
class PlayerSprite
{
public:
  PlayerSprite(const std::string&);
  PlayerSprite(const PlayerSprite&) = delete;
  PlayerSprite& operator=(const PlayerSprite&) = delete;

  void update(Uint32 ticks);
  
  inline void setScale(float scale) { this->sprite.setScale(scale); }

  void draw() const 
  { 
     sprite.draw(); 
     for (const Bullet& bullet :  bullets)
     	bullet.draw();
  }
  const RotationSprite* getPlayer() const { return &sprite; }

  const std::string& getName() const { return sprite.getName(); }
  int getX() const { return sprite.getX(); }
  int getY() const { return sprite.getY(); }
  const Image* getImage() const { 
    return sprite.getImage();
  }
  int getScaledWidth()  const { 
    return sprite.getScaledWidth();
  } 
  int getScaledHeight()  const { 
    return sprite.getScaledHeight();
  } 
  const SDL_Surface* getSurface() const { 
    return sprite.getSurface();
  }


  void collided() { collision = true; }
  void missed() { collision = false; }

  //ai
  void attach( SmartSprite* o ) { observers.push_back(o); } 
  void detach( SmartSprite* o );

  //bullet
  inline Pool<Bullet> getBulletPool() const noexcept { return this->bulletPool; }
  inline std::vector<Bullet> getBulletList() const noexcept { return this->bullets; }
  
  bool shoot();
  bool checkForBulletCollision(const Drawable&, CollisionStrategy*);

  Vector2f getPosition() { return this->sprite.getPosition(); }

  void right();
  void left();
  void up();
  void down();
  void stop();
  void rotateRight();
  void rotateLeft();

private:

  //bullet code
  std::string bulletName;
  Pool<Bullet> bulletPool;
  std::vector<Bullet> bullets;
  float minSpeed;
  float bulletInterval;
  float timeSinceLastFrame;
  //----------
  std::list<SmartSprite*> observers;
  RotationSprite sprite;
  bool collision;
  Vector2f initialVelocity;
  int worldWidth;
  int worldHeight;
};
#endif
