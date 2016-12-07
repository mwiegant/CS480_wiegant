#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <vector>
#include <string>

#include <cstdio>

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

    // for adding specific shapes
    bool AddPinball(btVector3 position, btScalar radius, btScalar mass, const char* modelPath, const char* texturePath);
    bool AddPaddle(btVector3 position, const char* paddleIdentifier, btScalar mass, const char* modelPath, const char* texturePath);

    // for adding generic shapes
    bool AddTriMeshShape(btVector3 position, btScalar mass, const char* modelPath, const char* texturePath);
    bool AddCylinder(btVector3 position, btVector3 halfwayVectors, btScalar mass, const char* modelPath, const char* texturePath);

    bool MovePinball(btVector3 position);
    bool setPinballVelocity(btVector3 velocity);

    void Update(unsigned int dt);
    vector<Object*> objectList;

    // todo - build functionality to move the paddles

  private:

    // world variables, needed to create the Bullet environment
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;
    btDiscreteDynamicsWorld *dynamicsWorld;

    // I think this is supposed to hold one copy of each unique type of object (a sphere, cube, plane, etc)
    btAlignedObjectArray<btCollisionShape*> collisionShapes;


    // rigid bodies
    btRigidBody* pinballBody;

    btRigidBody* leftPaddle;
    btRigidBody* rightPaddle;

};

#endif