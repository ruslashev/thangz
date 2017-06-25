// Physics in 3D Example
// Copyright (c) Glenn Fiedler 2004
// http://www.gaffer.org/articles

#include "Mathematics.h"
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

using namespace Mathematics;

#include <vector>
#include "Unix.h"
#include "OpenGL.h"
#include "Cube.h"

int main()
{
  const int width = 800;
  const int height = 600;

  screen s("Physics in 3D", width, height);

  Cube cube;

  initializeOpenGL();

  double t = 0, dt = 0.01;
  double current_time = s.get_time_in_seconds(), accumulator = 0;
  while (s.running) {
    double real_time = s.get_time_in_seconds()
      , elapsed = real_time - current_time;
    current_time = real_time;
    accumulator += elapsed;
    while (accumulator >= dt) {
      SDL_Event sdl_event;
      while (SDL_PollEvent(&sdl_event) != 0)
        if (sdl_event.type == SDL_QUIT)
          s.running = false;
      cube.update(t, dt);
      t += dt;
      accumulator -= dt;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cube.render();
    SDL_GL_SwapWindow(s._window);
  }


  return 0;
}
