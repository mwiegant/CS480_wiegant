#ifndef GRAPHICS_HEADERS_H
#define GRAPHICS_HEADERS_H

#include <iostream>

#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

#if defined(__APPLE__) || defined(MACOSX)
  #include <OpenGL/gl3.h>
  #include <OpenGL/GLU.h>
#else //linux as default
  #include <GL/glew.h>
  //#include <GL/glu.h>
#endif

// GLM for matricies
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#define INVALID_UNIFORM_LOCATION 0x7fffffff

struct Vertex
{
  public:

    glm::vec3 vertex;
    glm::vec2 uv;
    glm::vec3 normal;

    Vertex(glm::vec3 v, glm::vec2 c, glm::vec3 n): vertex(v), uv(c), normal(n) {}

    //Vertex(glm::vec3 v, glm::vec2 c): vertex(v), uv(c) {}
};

enum game_state
{
  GAME_STATE_READY,
  GAME_STATE_PLAYING,
  GAME_STATE_GAME_OVER
};


#endif /* GRAPHICS_HEADERS_H */