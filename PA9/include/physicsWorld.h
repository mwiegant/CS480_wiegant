#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <vector>
#include <string>
#include <btBulletDynamicsCommon.h>
#include "object.h"
#include "graphics_headers.h"
using namespace std;
class PhysicsWorld 
{
  public:
    PhysicsWorld();
    ~PhysicsWorld();
    bool Initialize();
    bool addRigidBody();
    void Update(unsigned int dt);
    vector<Object *> masterList;

  private:
    //world variables
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;
    btDiscreteDynamicsWorld *dynamicsWorld;

    //rigid bodies
    btRigidBody* groundRigidBody;
    btRigidBody* fallRigidBody;

    //objects
    Object *ground;
    Object *ball;
};

#endif
