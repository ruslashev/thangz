#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <queue>
#include <string>

class screen {
  SDL_GLContext _gl_context;
  std::string _title;
public:
  SDL_Window *_window;
  int window_width, window_height;
  bool running;
  screen(const std::string &n_title, int n_window_width, int n_window_height);
  ~screen();
  double get_time_in_seconds();
};

screen::screen(const std::string &n_title, int n_window_width
    , int n_window_height)
  : _title(n_title)
  , window_width(n_window_width)
  , window_height(n_window_height) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED
      , SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_OPENGL);

  _gl_context = SDL_GL_CreateContext(_window);

  if (SDL_GL_SetSwapInterval(0) == -1)
    printf("failed to set vsync: %s", SDL_GetError());

  GLenum err = glewInit();
  assert(err == GLEW_OK);

  assert(GLEW_VERSION_2_1);

  running = true;
}

screen::~screen() {
  SDL_GL_DeleteContext(_gl_context);
  SDL_Quit();
}

inline double screen::get_time_in_seconds() {
  return SDL_GetTicks() / 1000.;
}

