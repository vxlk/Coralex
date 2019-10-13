#ifndef IMAGE__H
#define IMAGE__H

#include <iostream>
#include <string>
#include "../include/SDL/SDL.h"

class Image {
public:
  Image(SDL_Surface*);
  Image(const Image&);
  Image& operator=(const Image&);

  void regenerateTexture();
  void draw(int x, int y) const;
  void draw(int x, int y, float scale) const;
  void draw(int sx, int sy, int dx, int dy) const;
  void drawRotation(int sx, int sy, float scale, double rotation) const;

  inline int getWidth()  const { return surface->w; }
  inline int getHeight() const { return surface->h; }
  SDL_Surface* getSurface() const { return surface; }
  Image* crop(SDL_Rect)const;
private:
  SDL_Renderer * renderer;
  SDL_Surface * surface;
  SDL_Texture * texture;
  SDL_Rect view;
  Image();
};

#endif
