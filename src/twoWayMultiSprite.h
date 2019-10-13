#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

/*
INVARIANTS:
Image A must be the same size as Image B
*/
class TwoWayMultiSprite : public Drawable
{
public:
    TwoWayMultiSprite(const std::string&, const std::string&);
    TwoWayMultiSprite(const TwoWayMultiSprite&) = delete;
    TwoWayMultiSprite& operator=(const TwoWayMultiSprite&) = delete;
    virtual void draw() const override;
    virtual void update(Uint32 ticks) override;
    Vector2f makeVelocity(int vx, int vy);
    virtual int getScaledWidth()  const override 
    { 
    return getScale()*getImageVector()[currentFrame]->getWidth(); 
    } 
    virtual int getScaledHeight()  const override 
    { 
    return getScale()*getImageVector()[currentFrame]->getHeight(); 
    } 

    virtual const Image* getImage() const override { return getImageVector()[currentFrame]; }
    virtual const SDL_Surface* getSurface() const override 
    { 
    return getImageVector()[currentFrame]->getSurface();
    }

    const std::vector<Image*>& getImageVector() const
    {
        if (isForward) return imagesForward;
        else return imagesBackward;
    }

protected:
    std::vector<Image *> imagesForward;
    std::vector<Image *> imagesBackward;

    bool isForward;
    int rotationAmount;
    unsigned currentFrame;
    unsigned numberOfFrames;
    unsigned frameInterval;
    float timeSinceLastFrame;
    int worldWidth;
    int worldHeight;

    void advanceFrame(Uint32 ticks);
};

#endif