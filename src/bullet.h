#ifndef BULLET_H
#define BULLET_H
#include <iostream>
#include "sprite.h"
#include "gameData.h"
#include "rotationSprite.h"

class Bullet : public Sprite {
public:
  explicit Bullet(const string& name) :
    Sprite(name), 
    distance(0), 
    maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")), 
    tooFar(false),
    collision(false)
  { }

  //Bullet& operator=(const Bullet&) = default;
  virtual void update(Uint32 ticks);
  bool goneTooFar() const noexcept { return tooFar; }
  inline bool hasCollision() const noexcept { return collision; }
  inline void collided() {this->collision = true;}
  void reset() {
    tooFar = false;
    distance = 0;
    collision = false;
  }

private:
  float distance;
  float maxDistance;
  bool tooFar;
  bool collision;
};
#endif