#include <iostream>
#include "../include/SDL/SDL.h"
#include "imageFactory.h"

//this does not need to be a singleton
class RenderContext{
public:
  static RenderContext& getInstance();
  ~RenderContext();
  SDL_Window* getWindow() const { return window; }
  SDL_Renderer* getRenderer() const { return renderer; }
  RenderContext();

  RenderContext(const RenderContext&) = delete;
  RenderContext& operator=(const RenderContext&) = delete;
private:
  
  SDL_Window* window;
  SDL_Renderer* renderer;

  //ImageFactory* factory;

  SDL_Window* initWindow();
  SDL_Renderer* initRenderer();
};
