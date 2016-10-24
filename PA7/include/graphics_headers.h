/**
 * @file graphics_headers.h
 *
 * @brief Definition file for graphics_headers class
 * 
 * @author Cactus Coolers
 * 
 * @details Specifies all methods and variables for graphics_headers class
 *
 * @version 1.00
 *
 * @Note Made changes to the vertex struct in order to accomodate uv coordinates
 */

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

    Vertex(glm::vec3 v, glm::vec2 c): vertex(v), uv(c) {}
};

/*
 * We may end up not using this enum, but I've included it here
 * in case we would like to zoom in on a planet, or do something
 * like that
 */
enum System
{
    SOLAR_SYSTEM,
    MERCURY_SYSTEM,
    VENUS_SYSTEM,
    EARTH_SYSTEM,
    MARS_SYSTEM,
    JUPITER_SYSTEM,
    SATURN_SYSTEM,
    URANUS_SYSTEM,
    NEPTUNE_SYSTEM,
    PLUTO_SYSTEM
};


#endif /* GRAPHICS_HEADERS_H */
