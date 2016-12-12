#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <cstdio>
#include <vector>
#include <string>

#include <btBulletDynamicsCommon.h>

#include "graphics_headers.h"
#include "object.h"

using namespace std;

class PhysicsWorld 
{
  public:
    PhysicsWorld();
    ~PhysicsWorld();

    bool Initialize();

    void Update(unsigned int dt);

    // for adding specific shapes
    btRigidBody* AddFloor(short colGroup, short colMask, Object* object);
    btRigidBody* AddSimpleSphere(btVector3 position, btScalar radius, btScalar mass, short colGroup, short colMask, Object* object);
    btRigidBody* AddSimpleCylinder(btVector3 position, btVector3 halfwayVectors, btScalar mass, short colGroup, short colMask, Object* object);
    // AddSimpleRectangle()

    // for adding complex shapes
    btRigidBody* AddComplexShape(btVector3 position, btScalar mass, short colGroup, short colMask, Object* object);



    vector<Object*> objectList;


  private:

    // world variables, needed to create the Bullet environment
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;
    btDiscreteDynamicsWorld *dynamicsWorld;

    // I think this is supposed to hold one copy of each unique type of object (a sphere, cube, plane, etc)
    btAlignedObjectArray<btCollisionShape*> collisionShapes;


};

#endif
