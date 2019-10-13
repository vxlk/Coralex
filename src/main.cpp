// Brian Malloy        Data-Driven Object oriented Game Construction
#include "engine.h"

//ImageFactory*  ImageFactory::instance = NULL; neither are needed
//RenderContext* RenderContext::instance = NULL;

int main(int, char*[]) {
  bool keepPlaying = true;
   try {
     while ( keepPlaying ) {
       Engine* engine = new Engine;
       keepPlaying = engine->play();
       delete engine;
       engine = nullptr; //avoid double free
     }
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
