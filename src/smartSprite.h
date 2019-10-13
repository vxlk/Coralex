#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <string>
#include "rotationSprite.h"
#include "explodingSprite.h"

class SmartSprite : public RotationSprite{
public:
  SmartSprite(const std::string&, const Vector2f& pos, int w, int h);
  SmartSprite(const SmartSprite&) = delete;
  SmartSprite& operator=(const SmartSprite& rhs) = delete;
  virtual ~SmartSprite() { } 
  
  bool spriteIsDead() const { return this->isDead; } 
  virtual void update(Uint32 ticks);
  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  virtual void draw() const override
  {
    if (!needsToExplode)
      RotationSprite::draw(); 
    else this->explosion.draw();
  }

  void setToExplode();
  bool doneExploding() { if (explosion.chunkCount() == 0) return true; return false;}
private:
  bool isDead;
  ExplodingSprite explosion;
  enum MODE {NORMAL, EVADE};
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  MODE currentMode;
  float safeDistance;
  std::string spriteName;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();

  bool needsToExplode;
};
#endif
