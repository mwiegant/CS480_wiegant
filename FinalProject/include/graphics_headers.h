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

#define BIT(x) (1<<(x))
enum collisiontypes {
    COL_NOTHING = 0,              // Collide with no other objects
    COL_CATAPULT_ARM = BIT(0),    // Collide with the catapult arm
    COL_CATAPULT_BODY = BIT(1),   // Collide with the catapult body
    COL_CATAPULT_WHEEL = BIT(2),  // Collide with the catapult wheels
    COL_NON_CATAPULT = BIT(3),    // Collide with non catapult objects
    COL_FLOOR = BIT(4)            // Collide with the floor
};


/*
int floorCollidesWith = COL_CATAPULT_ARM | COL_CATAPULT_BODY |
                        COL_CATAPULT_WHEEL | COL_NON_CATAPULT;
int catapultArmCollidesWith = COL_NOTHING;
int catapultBodyCollidesWith = COL_NON_CATAPULT | COL_FLOOR;
int catapultWheelCollidesWith = COL_FLOOR;
int catapultProjectile = COL_CATAPULT_ARM | COL_NON_CATAPULT | COL_FLOOR;
int nonCatapultObject = COL_CATAPULT_BODY | COL_NON_CATAPULT | COL_FLOOR;
*/


#endif /* GRAPHICS_HEADERS_H */
